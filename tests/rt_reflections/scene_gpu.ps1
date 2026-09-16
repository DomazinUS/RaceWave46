[CmdletBinding()]
param(
    [string]$BuildToolsRoot = '',
    [string]$BuildDirectory = '',
    [string]$OutputDirectory = ''
)
$ErrorActionPreference = 'Stop'
. (Join-Path $PSScriptRoot '..\..\tools\windows-build-environment.ps1')
$BuildToolsRoot = Initialize-Wr64BuildEnvironment -BuildToolsRoot $BuildToolsRoot
$sourceRoot = [IO.Path]::GetFullPath((Join-Path $PSScriptRoot '..\..'))
if (-not $BuildDirectory) { $BuildDirectory = Join-Path $sourceRoot 'build' }
if (-not $OutputDirectory) { $OutputDirectory = Join-Path $sourceRoot 'build\test-output\rt-scene-gpu' }
$OutputDirectory = [IO.Path]::GetFullPath($OutputDirectory)
$plumeLibrary = Join-Path $BuildDirectory 'rt64\src\contrib\plume\plume.lib'
if (-not (Test-Path -LiteralPath $plumeLibrary)) { throw 'Build the project Plume library first.' }
$vcVersion = (Get-Content -LiteralPath (Join-Path $BuildToolsRoot 'VC\Auxiliary\Build\Microsoft.VCToolsVersion.default.txt') -Raw).Trim()
$vcDirectory = Join-Path $BuildToolsRoot "VC\Tools\MSVC\$vcVersion"
$sdkRoot = Join-Path ${env:ProgramFiles(x86)} 'Windows Kits\10'
$sdkVersion = Get-ChildItem -LiteralPath (Join-Path $sdkRoot 'Include') -Directory |
    Where-Object { Test-Path -LiteralPath (Join-Path $_.FullName 'um\d3d12.h') } |
    Sort-Object Name -Descending | Select-Object -First 1 -ExpandProperty Name
if (-not $sdkVersion) { throw 'A Windows SDK with D3D12 headers is required.' }
$savedInclude = $env:INCLUDE
$savedLib = $env:LIB
$savedPath = $env:PATH
New-Item -ItemType Directory -Path $OutputDirectory -Force | Out-Null
Push-Location -LiteralPath $OutputDirectory
try {
    $env:INCLUDE = "$vcDirectory\include;$sdkRoot\Include\$sdkVersion\ucrt;$sdkRoot\Include\$sdkVersion\shared;$sdkRoot\Include\$sdkVersion\um"
    $env:LIB = "$vcDirectory\lib\x64;$sdkRoot\Lib\$sdkVersion\ucrt\x64;$sdkRoot\Lib\$sdkVersion\um\x64"
    $env:PATH = "$vcDirectory\bin\Hostx64\x64;$env:PATH"
    $rt64Source = Join-Path $sourceRoot 'lib\rt64\src'
    $dxc = Join-Path $BuildDirectory '_deps\wr64-dxc-toolset\dxc.exe'
    $shader = Join-Path $OutputDirectory 'scene_gpu.dxil'
    & $dxc -T cs_6_5 -E CSMain -WX -Fo $shader (Join-Path $PSScriptRoot 'scene_gpu.hlsl')
    if ($LASTEXITCODE -ne 0) { throw 'Scene GPU probe shader compilation failed.' }
    & (Join-Path $vcDirectory 'bin\Hostx64\x64\cl.exe') /nologo /std:c++17 /EHsc /O2 /MD /DNDEBUG /DNOMINMAX `
        "/I$rt64Source" "/I$rt64Source\contrib\plume" "/I$rt64Source\contrib\plume\contrib\D3D12MemoryAllocator\include" `
        (Join-Path $PSScriptRoot 'scene_gpu.cpp') (Join-Path $rt64Source 'render\rt64_wr64_rt_scene.cpp') `
        (Join-Path $rt64Source 'render\rt64_render_worker.cpp') "/Fe$OutputDirectory\scene_gpu.exe" `
        /link $plumeLibrary d3d12.lib dxgi.lib dxguid.lib user32.lib
    if ($LASTEXITCODE -ne 0) { throw 'Scene GPU probe compilation failed.' }
    & (Join-Path $OutputDirectory 'scene_gpu.exe') $shader
    if ($LASTEXITCODE -eq 77) { Write-Output 'GPU probe skipped: hardware requirements are unavailable.' }
    elseif ($LASTEXITCODE -ne 0) { throw 'Scene GPU probe failed.' }
}
finally {
    Pop-Location
    $env:INCLUDE = $savedInclude
    $env:LIB = $savedLib
    $env:PATH = $savedPath
}
