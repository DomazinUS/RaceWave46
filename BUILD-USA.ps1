[CmdletBinding()]
param(
    [string]$BuildToolsRoot = '',
    [string]$BuildDirectory = '',
    [ValidateRange(1, 64)][int]$Jobs = 8,
    [string]$VulkanDxc = '',
    [string]$DirectXDxcDirectory = '',
    [switch]$ConfigureOnly
)
$ErrorActionPreference = 'Stop'
. (Join-Path $PSScriptRoot 'tools\windows-build-environment.ps1')
$BuildToolsRoot = Initialize-Wr64BuildEnvironment -BuildToolsRoot $BuildToolsRoot
if (-not $BuildDirectory) { $BuildDirectory = Join-Path $PSScriptRoot 'build' }
$BuildDirectory = [IO.Path]::GetFullPath($BuildDirectory)
$arguments = @('-S', $PSScriptRoot, '-B', $BuildDirectory, '-G', 'Ninja',
    '-DCMAKE_BUILD_TYPE=Release', '-DWR64_ENABLE_RT64=ON', '-DWR64_ENABLE_FRONTEND=ON',
    '-DWR64_ENABLE_DIAGNOSTICS=OFF')
if ($VulkanDxc) {
    $VulkanDxc = (Resolve-Path -LiteralPath $VulkanDxc -ErrorAction Stop).Path
    $arguments += "-DRT64_WR64_VULKAN_DXC=$VulkanDxc"
}
if ($DirectXDxcDirectory) {
    $DirectXDxcDirectory = (Resolve-Path -LiteralPath $DirectXDxcDirectory -ErrorAction Stop).Path
    $arguments += "-DWR64_DXC_TOOLCHAIN_DIRECTORY=$DirectXDxcDirectory"
}
& cmake.exe @arguments
if ($LASTEXITCODE -ne 0) { throw 'Release configuration failed.' }
if (-not $ConfigureOnly) {
    & cmake.exe --build $BuildDirectory --target WaveRace64Recompiled --parallel $Jobs
    if ($LASTEXITCODE -ne 0) { throw 'Release build failed.' }
    Write-Output "Built: $(Join-Path $BuildDirectory 'WaveRace64Recompiled.exe')"
}
