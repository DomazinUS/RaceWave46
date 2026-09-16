[CmdletBinding()]
param(
    [string]$BuildToolsRoot = '',
    [string]$BuildDirectory = '',
    [string]$OutputDirectory = '',
    [Parameter(Mandatory)][string]$VulkanLayerPath,
    [switch]$CompileOnly
)
$ErrorActionPreference = 'Stop'
. (Join-Path $PSScriptRoot '..\..\tools\windows-build-environment.ps1')
$BuildToolsRoot = Initialize-Wr64BuildEnvironment -BuildToolsRoot $BuildToolsRoot
$sourceRoot = [IO.Path]::GetFullPath((Join-Path $PSScriptRoot '..\..'))
if (-not $BuildDirectory) { $BuildDirectory = Join-Path $sourceRoot 'build' }
if (-not $OutputDirectory) { $OutputDirectory = Join-Path $sourceRoot 'build\test-output\common-compute' }
$BuildDirectory = [IO.Path]::GetFullPath($BuildDirectory)
$OutputDirectory = [IO.Path]::GetFullPath($OutputDirectory)
$VulkanLayerPath = [IO.Path]::GetFullPath($VulkanLayerPath)
if (-not (Test-Path -LiteralPath (Join-Path $VulkanLayerPath 'VkLayer_khronos_validation.json'))) { throw 'VulkanLayerPath must contain the validation manifest.' }
$vcVersion = (Get-Content -LiteralPath (Join-Path $BuildToolsRoot 'VC\Auxiliary\Build\Microsoft.VCToolsVersion.default.txt') -Raw).Trim()
$vcDirectory = Join-Path $BuildToolsRoot "VC\Tools\MSVC\$vcVersion"
$sdkRoot = Join-Path ${env:ProgramFiles(x86)} 'Windows Kits\10'
$sdkVersion = Get-ChildItem -LiteralPath (Join-Path $sdkRoot 'Include') -Directory |
    Where-Object { Test-Path -LiteralPath (Join-Path $_.FullName 'um\d3d12.h') } |
    Sort-Object Name -Descending | Select-Object -First 1 -ExpandProperty Name
if (-not $sdkVersion) { throw 'Windows SDK missing.' }
$names = @('INCLUDE', 'LIB', 'PATH', 'VK_INSTANCE_LAYERS', 'VK_LAYER_PATH', 'VK_LAYER_VALIDATE_SYNC', 'PLUME_VULKAN_VALIDATION')
$saved = @{}
foreach ($name in $names) { $saved[$name] = [Environment]::GetEnvironmentVariable($name, 'Process') }
New-Item -ItemType Directory -Path $OutputDirectory -Force | Out-Null
Push-Location -LiteralPath $OutputDirectory
try {
    $env:INCLUDE = "$vcDirectory\include;$sdkRoot\Include\$sdkVersion\ucrt;$sdkRoot\Include\$sdkVersion\shared;$sdkRoot\Include\$sdkVersion\um"
    $env:LIB = "$vcDirectory\lib\x64;$sdkRoot\Lib\$sdkVersion\ucrt\x64;$sdkRoot\Lib\$sdkVersion\um\x64"
    $rt = Join-Path $sourceRoot 'lib\rt64\src'
    $env:PATH = "$vcDirectory\bin\Hostx64\x64;$BuildDirectory\_deps\wr64-dxc-toolset;$env:PATH"
    $paths = @($rt, "$rt\contrib", "$rt\contrib\plume", "$rt\contrib\hlslpp\include", "$rt\contrib\dxc\inc",
        "$rt\contrib\plume\contrib\volk", "$rt\contrib\plume\contrib\Vulkan-Headers\include",
        "$rt\contrib\plume\contrib\VulkanMemoryAllocator\include", "$BuildDirectory\src\shaders")
    $includes = @($paths | ForEach-Object { "/I$_" })
    & (Join-Path $vcDirectory 'bin\Hostx64\x64\cl.exe') /nologo /std:c++17 /EHsc /O2 /MD /DNDEBUG /DNOMINMAX /DHLSL_CPU `
        @includes (Join-Path $PSScriptRoot 'common_compute.cpp') "/Fe$OutputDirectory\common_compute.exe" `
        /link /OPT:REF "$BuildDirectory\rt64\rt64.lib" "$BuildDirectory\rt64\src\contrib\plume\plume.lib" `
        "$rt\contrib\dxc\lib\x64\dxcompiler.lib" d3d12.lib dxgi.lib dxguid.lib user32.lib
    if ($LASTEXITCODE -ne 0) { throw 'Common compute fixture compilation failed.' }
    if (-not $CompileOnly) {
        $env:VK_LAYER_PATH = $VulkanLayerPath
        $env:VK_INSTANCE_LAYERS = 'VK_LAYER_KHRONOS_validation'
        $env:VK_LAYER_VALIDATE_SYNC = '1'
        $env:PLUME_VULKAN_VALIDATION = '1'
        & (Join-Path $OutputDirectory 'common_compute.exe')
        if ($LASTEXITCODE -ne 0) { throw "Common compute fixture failed: $LASTEXITCODE" }
    }
}
finally {
    Pop-Location
    foreach ($name in $names) { [Environment]::SetEnvironmentVariable($name, $saved[$name], 'Process') }
}
