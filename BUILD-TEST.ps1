[CmdletBinding()]
param(
    [Parameter(Mandatory=$true)][ValidatePattern('^[A-Za-z0-9_]+$')][string]$Suite,
    [string]$BuildToolsRoot = '',
    [string]$BuildDirectory = '',
    [string]$Python = '',
    [string]$UsaRom = '',
    [ValidateRange(1, 64)][int]$Jobs = 4,
    [string[]]$CmakeOptions = @()
)
$ErrorActionPreference = 'Stop'
. (Join-Path $PSScriptRoot 'tools\windows-build-environment.ps1')
$BuildToolsRoot = Initialize-Wr64BuildEnvironment -BuildToolsRoot $BuildToolsRoot
$Python = Resolve-Wr64Python -Python $Python
$testSource = Join-Path $PSScriptRoot "tests\$Suite"
if (-not (Test-Path -LiteralPath (Join-Path $testSource 'CMakeLists.txt'))) { throw "No CMake test suite named $Suite." }
if (-not $BuildDirectory) { $BuildDirectory = Join-Path $PSScriptRoot "build\tests\$Suite" }
$arguments = @('-S', $testSource, '-B', $BuildDirectory, '-G', 'Ninja',
    '-DCMAKE_BUILD_TYPE=Release', "-DPython3_EXECUTABLE=$Python") + $CmakeOptions
if (-not $UsaRom -and $env:WR64_TEST_ROM) { $UsaRom = $env:WR64_TEST_ROM }
if ($UsaRom) {
    $UsaRom = (Resolve-Path -LiteralPath $UsaRom -ErrorAction Stop).Path
    & $Python (Join-Path $PSScriptRoot 'tools\verify_rom.py') $UsaRom
    if ($LASTEXITCODE -ne 0) { throw 'The test ROM must be an unmodified USA Rev 1 ROM.' }
    $arguments += @("-DWR64_TEST_ROM=$UsaRom", "-DWR64_GHOST_NATIVE_ROM=$UsaRom", "-DWR64_SHUTTER_NATIVE_ROM=$UsaRom")
}
& cmake.exe @arguments
if ($LASTEXITCODE -ne 0) { throw "$Suite configuration failed." }
& cmake.exe --build $BuildDirectory --parallel $Jobs
if ($LASTEXITCODE -ne 0) { throw "$Suite build failed." }
& ctest.exe --test-dir $BuildDirectory --output-on-failure
if ($LASTEXITCODE -ne 0) { throw "$Suite tests failed." }
