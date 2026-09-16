[CmdletBinding()]
param(
    [string]$BuildToolsRoot = '',
    [string]$BuildDirectory = '',
    [ValidateRange(1, 64)][int]$Jobs = 4,
    [string]$UsaRom = '',
    [string]$Python = ''
)
$ErrorActionPreference = 'Stop'
if (-not $BuildDirectory) { $BuildDirectory = Join-Path $PSScriptRoot 'build\tests\controller_parity' }
& (Join-Path $PSScriptRoot 'BUILD-TEST.ps1') -Suite controller_parity `
    -BuildToolsRoot $BuildToolsRoot -BuildDirectory $BuildDirectory -Jobs $Jobs `
    -UsaRom $UsaRom -Python $Python -CmakeOptions '-DWR64_TEST_SDL_INTEGRATION=ON'
