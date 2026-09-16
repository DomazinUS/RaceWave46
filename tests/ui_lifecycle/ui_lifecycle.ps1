[CmdletBinding()]
param(
    [string]$BuildToolsRoot = '',
    [string]$BuildDirectory = '',
    [string]$OutputDirectory = '',
    [string]$VulkanLayerPath = '',
    [switch]$CompileOnly
)
$ErrorActionPreference = 'Stop'
. (Join-Path $PSScriptRoot '..\..\tools\windows-build-environment.ps1')
$BuildToolsRoot = Initialize-Wr64BuildEnvironment -BuildToolsRoot $BuildToolsRoot
$sourceRoot = [IO.Path]::GetFullPath((Join-Path $PSScriptRoot '..\..'))
if (-not $BuildDirectory) { $BuildDirectory = Join-Path $sourceRoot 'build' }
if (-not $OutputDirectory) { $OutputDirectory = Join-Path $sourceRoot 'build\test-output\ui-lifecycle' }
$BuildDirectory = [IO.Path]::GetFullPath($BuildDirectory)
$OutputDirectory = [IO.Path]::GetFullPath($OutputDirectory)
if ($VulkanLayerPath) {
    $VulkanLayerPath = [IO.Path]::GetFullPath($VulkanLayerPath)
    if (-not (Test-Path -LiteralPath (Join-Path $VulkanLayerPath 'VkLayer_khronos_validation.json'))) { throw 'VulkanLayerPath must contain the Khronos validation manifest.' }
}
$vcVersion = (Get-Content -LiteralPath (Join-Path $BuildToolsRoot 'VC\Auxiliary\Build\Microsoft.VCToolsVersion.default.txt') -Raw).Trim()
$vcDirectory = Join-Path $BuildToolsRoot "VC\Tools\MSVC\$vcVersion"
$sdkRoot = Join-Path ${env:ProgramFiles(x86)} 'Windows Kits\10'
$sdkVersion = Get-ChildItem -LiteralPath (Join-Path $sdkRoot 'Include') -Directory |
    Where-Object { Test-Path -LiteralPath (Join-Path $_.FullName 'um\d3d12.h') } |
    Sort-Object Name -Descending | Select-Object -First 1 -ExpandProperty Name
if (-not $sdkVersion) { throw 'A Windows SDK with D3D12 headers is required.' }
$savedEnvironment = @{}
foreach ($name in @('INCLUDE', 'LIB', 'PATH', 'VK_INSTANCE_LAYERS', 'VK_LAYER_PATH', 'VK_LAYER_VALIDATE_SYNC', 'PLUME_VULKAN_VALIDATION')) {
    $savedEnvironment[$name] = [Environment]::GetEnvironmentVariable($name, 'Process')
}
New-Item -ItemType Directory -Path $OutputDirectory -Force | Out-Null
Push-Location -LiteralPath $OutputDirectory
try {
    $env:INCLUDE = "$vcDirectory\include;$sdkRoot\Include\$sdkVersion\ucrt;$sdkRoot\Include\$sdkVersion\shared;$sdkRoot\Include\$sdkVersion\um"
    $env:LIB = "$vcDirectory\lib\x64;$sdkRoot\Lib\$sdkVersion\ucrt\x64;$sdkRoot\Lib\$sdkVersion\um\x64"
    $env:PATH = "$vcDirectory\bin\Hostx64\x64;$BuildDirectory\_deps\wr64-dxc-toolset;$env:PATH"
    $ui = Join-Path $sourceRoot 'lib\RecompFrontend\recompui'
    $rt = Join-Path $sourceRoot 'lib\rt64\src'
    $modern = Join-Path $sourceRoot 'lib\N64ModernRuntime'
    $paths = @("$ui\include", "$ui\include\recompui", "$ui\src", "$ui\src\renderer", "$ui\lib\RmlUi\Include",
        "$ui\..\recompinput\include", "$ui\..\lib\GamepadMotionHelpers", "$ui\..\lib\SlotMap", "$ui\lib\lunasvg\include",
        $rt, "$rt\render", "$rt\rhi", "$rt\contrib", "$rt\contrib\hlslpp\include", "$rt\contrib\dxc\inc",
        "$rt\contrib\plume", "$rt\contrib\plume\contrib\D3D12MemoryAllocator\include", "$rt\contrib\plume\contrib\volk",
        "$rt\contrib\plume\contrib\Vulkan-Headers\include", "$rt\contrib\plume\contrib\VulkanMemoryAllocator\include",
        "$rt\contrib\mupen64plus-win32-deps\SDL2-2.26.3\include", "$rt\contrib\imgui",
        "$modern\librecomp\include", "$modern\N64Recomp\include", "$modern\ultramodern\include", "$modern\thirdparty",
        "$modern\thirdparty\concurrentqueue", "$modern\thirdparty\miniz", "$BuildDirectory\shaders")
    $includes = @($paths | ForEach-Object { "/I$_" })
    $libraries = @(
        "$BuildDirectory\lib\RecompFrontend\recompui\recompui.lib",
        "$BuildDirectory\rt64\rt64.lib", "$BuildDirectory\rt64\src\contrib\plume\plume.lib",
        "$BuildDirectory\rt64\src\contrib\re-spirv\re-spirv.lib", "$BuildDirectory\rt64\src\contrib\zstd\build\cmake\lib\zstd_static.lib",
        "$rt\contrib\dxc\lib\x64\dxcompiler.lib", "$BuildDirectory\lib\RecompFrontend\recompui\lib\RmlUi\Source\Core\rmlui.lib",
        "$ui\lib\freetype-windows-binaries\release static\vs2015-2022\win64\freetype.lib",
        "$BuildDirectory\lib\RecompFrontend\recompui\lib\lunasvg\lunasvg.lib",
        "$BuildDirectory\lib\RecompFrontend\recompui\lib\lunasvg\plutovg\plutovg.lib")
    & (Join-Path $vcDirectory 'bin\Hostx64\x64\cl.exe') /nologo /std:c++20 /EHsc /O2 /MD /DNDEBUG /DNOMINMAX /DHLSL_CPU `
        /DRMLUI_STATIC_LIB /DLUNASVG_BUILD_STATIC /D_DISABLE_CONSTEXPR_MUTEX_CONSTRUCTOR @includes `
        (Join-Path $PSScriptRoot 'ui_lifecycle.cpp') "$ui\src\renderer\ui_renderer.cpp" "/Fe$OutputDirectory\ui_lifecycle.exe" `
        /link /OPT:REF @libraries d3d12.lib dxgi.lib dxguid.lib user32.lib
    if ($LASTEXITCODE -ne 0) { throw 'Headless UI lifecycle fixture compilation failed.' }
    if (-not $CompileOnly) {
        $arguments = @((Join-Path $sourceRoot 'assets\LatoLatin-Regular.ttf'))
        if ($VulkanLayerPath) {
            $env:VK_LAYER_PATH = $VulkanLayerPath
            $env:VK_INSTANCE_LAYERS = 'VK_LAYER_KHRONOS_validation'
            $env:VK_LAYER_VALIDATE_SYNC = '1'
            $env:PLUME_VULKAN_VALIDATION = '1'
            $arguments += '--validation'
        }
        & (Join-Path $OutputDirectory 'ui_lifecycle.exe') @arguments
        if ($LASTEXITCODE -ne 0) { throw "Headless UI lifecycle fixture failed: $LASTEXITCODE" }
    }
}
finally {
    Pop-Location
    foreach ($name in $savedEnvironment.Keys) { [Environment]::SetEnvironmentVariable($name, $savedEnvironment[$name], 'Process') }
}
