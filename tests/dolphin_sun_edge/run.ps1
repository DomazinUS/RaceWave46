param(
    [string]$BuildToolsRoot = '',
    [string]$Python = ''
)
$ErrorActionPreference = 'Stop'
. (Join-Path $PSScriptRoot '..\..\tools\windows-build-environment.ps1')
$BuildToolsRoot = Initialize-Wr64BuildEnvironment -BuildToolsRoot $BuildToolsRoot
$Python = Resolve-Wr64Python -Python $Python
$testBuild = Join-Path $PSScriptRoot 'build'
$vcvars = Join-Path $BuildToolsRoot 'VC\Auxiliary\Build\vcvars64.bat'
$cmakeDirectory = Join-Path $BuildToolsRoot 'Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin'
$cmake = Join-Path $cmakeDirectory 'cmake.exe'
$ctest = Join-Path $cmakeDirectory 'ctest.exe'
$ninja = Join-Path $BuildToolsRoot 'Common7\IDE\CommonExtensions\Microsoft\CMake\Ninja\ninja.exe'
foreach ($required in @($vcvars, $cmake, $ctest, $ninja, $Python)) {
    if (-not (Test-Path -LiteralPath $required)) { throw "Missing tool: $required" }
}
$environmentLines = & $env:ComSpec /d /s /c "`"call `"$vcvars`" >nul && set`""
if ($LASTEXITCODE -ne 0) { throw 'Visual Studio environment initialization failed.' }
foreach ($line in $environmentLines) {
    if ($line -match '^([^=]+)=(.*)$') {
        Set-Item -LiteralPath "Env:$($Matches[1])" -Value $Matches[2]
    }
}
& $cmake -S $PSScriptRoot -B $testBuild -G Ninja -DCMAKE_BUILD_TYPE=Release "-DCMAKE_MAKE_PROGRAM=$ninja" "-DPython3_EXECUTABLE=$Python"
if ($LASTEXITCODE -ne 0) { throw 'Dolphin sun edge test configuration failed.' }
& $cmake --build $testBuild --parallel 2
if ($LASTEXITCODE -ne 0) { throw 'Dolphin sun edge test build failed.' }
& $ctest --test-dir $testBuild --output-on-failure
if ($LASTEXITCODE -ne 0) { throw 'Dolphin sun edge regression failed.' }
