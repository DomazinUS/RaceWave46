[CmdletBinding()]
param(
    [string]$PackPath = '',
    [Parameter(Mandatory=$true)][string]$DumpDirectory,
    [string]$BuildDirectory = '',
    [string]$OutputDirectory = '',
    [string]$BuildToolsRoot = '',
    [switch]$CpuMatcher,
    [string]$SourcePackDirectory = '',
    [string]$MappingReport = '',
    [string]$DynamicReferencePack = ''
)
$ErrorActionPreference = 'Stop'
. (Join-Path $PSScriptRoot '..\..\tools\windows-build-environment.ps1')
$BuildToolsRoot = Initialize-Wr64BuildEnvironment -BuildToolsRoot $BuildToolsRoot
$sourceRoot = [IO.Path]::GetFullPath((Join-Path $PSScriptRoot '..\..'))
if (-not $CpuMatcher -and -not $PackPath) { throw 'Pass -PackPath for a GPU texture test.' }
if (-not $BuildDirectory) { $BuildDirectory = Join-Path $sourceRoot 'build' }
if (-not $OutputDirectory) { $OutputDirectory = Join-Path $sourceRoot 'build\test-output\hd-texture-gpu-20260912' }
if ($CpuMatcher -and (-not $SourcePackDirectory -or -not $MappingReport)) { throw 'Pass -SourcePackDirectory and -MappingReport for a CPU matcher test.' }
$vcVersion = (Get-Content -LiteralPath (Join-Path $BuildToolsRoot 'VC\Auxiliary\Build\Microsoft.VCToolsVersion.default.txt') -Raw).Trim()
$vcDirectory = Join-Path $BuildToolsRoot "VC\Tools\MSVC\$vcVersion"
$sdkRoot = Join-Path ${env:ProgramFiles(x86)} 'Windows Kits\10'
$sdkVersion = Get-ChildItem -LiteralPath (Join-Path $sdkRoot 'Include') -Directory | Where-Object { Test-Path -LiteralPath (Join-Path $_.FullName 'um\d3d12.h') } | Sort-Object Name -Descending | Select-Object -First 1 -ExpandProperty Name
$savedInclude = $env:INCLUDE; $savedLib = $env:LIB; $savedPath = $env:PATH
New-Item -ItemType Directory -Path $OutputDirectory -Force | Out-Null
Push-Location -LiteralPath $OutputDirectory
try {
    $env:INCLUDE = "$vcDirectory\include;$sdkRoot\Include\$sdkVersion\ucrt;$sdkRoot\Include\$sdkVersion\shared;$sdkRoot\Include\$sdkVersion\um"
    $env:LIB = "$vcDirectory\lib\x64;$sdkRoot\Lib\$sdkVersion\ucrt\x64;$sdkRoot\Lib\$sdkVersion\um\x64"
    $env:PATH = "$vcDirectory\bin\Hostx64\x64;$BuildDirectory\_deps\wr64-dxc-toolset;$env:PATH"
    $rt64Source = Join-Path $sourceRoot 'lib\rt64\src'
    $includes = @($rt64Source, "$rt64Source\contrib", "$rt64Source\contrib\plume", "$rt64Source\contrib\hlslpp\include", "$rt64Source\contrib\plume\contrib\D3D12MemoryAllocator\include", "$rt64Source\contrib\dxc\inc", "$rt64Source\contrib\re-spirv\external\SPIRV-Headers\include", "$rt64Source\contrib\imgui") | ForEach-Object { "/I$_" }
    $libraries = @((Join-Path $BuildDirectory 'rt64\rt64.lib'), (Join-Path $BuildDirectory 'rt64\src\contrib\plume\plume.lib'), (Join-Path $BuildDirectory 'rt64\src\contrib\re-spirv\re-spirv.lib'), (Join-Path $BuildDirectory 'rt64\src\contrib\zstd\build\cmake\lib\zstd_static.lib'), (Join-Path $rt64Source 'contrib\dxc\lib\x64\dxcompiler.lib'))
    $fixture = if ($CpuMatcher) { 'cpu_matcher' } else { 'headless' }
    & (Join-Path $vcDirectory 'bin\Hostx64\x64\cl.exe') /nologo /std:c++17 /EHsc /O2 /MD /DNDEBUG /DNOMINMAX /DHLSL_CPU @includes (Join-Path $PSScriptRoot "$fixture.cpp") "/Fe$OutputDirectory\$fixture.exe" /link /OPT:REF @libraries d3d12.lib dxgi.lib dxguid.lib user32.lib
    if ($LASTEXITCODE -ne 0) { throw 'Headless texture fixture compilation failed.' }
    # This console-only fixture never creates a window or launches the game.
    $arguments = if ($CpuMatcher) { @($SourcePackDirectory, $DumpDirectory, $MappingReport) } else { @($PackPath, $DumpDirectory) }
    if ($DynamicReferencePack -and -not $CpuMatcher) { $arguments += $DynamicReferencePack }
    $resultName = if ($CpuMatcher) { 'cpu-matcher-result.txt' } else { 'result.txt' }
    & (Join-Path $OutputDirectory "$fixture.exe") @arguments | Tee-Object -FilePath (Join-Path $OutputDirectory $resultName)
    if ($LASTEXITCODE -ne 0) { throw "Headless texture fixture failed ($LASTEXITCODE)." }
}
finally {
    Pop-Location
    $env:INCLUDE = $savedInclude; $env:LIB = $savedLib; $env:PATH = $savedPath
}
