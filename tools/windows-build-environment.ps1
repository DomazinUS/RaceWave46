function Initialize-Wr64BuildEnvironment {
    param([string]$BuildToolsRoot = '')
    if (-not $BuildToolsRoot -and $env:VSINSTALLDIR) {
        $BuildToolsRoot = $env:VSINSTALLDIR
    }
    if (-not $BuildToolsRoot) {
        $vswhere = Join-Path ${env:ProgramFiles(x86)} 'Microsoft Visual Studio\Installer\vswhere.exe'
        if (Test-Path -LiteralPath $vswhere) {
            $BuildToolsRoot = & $vswhere -latest -products '*' -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath
            if ($LASTEXITCODE -ne 0) { throw 'Visual Studio discovery failed.' }
        }
    }
    if (-not $BuildToolsRoot) {
        throw 'Install Visual Studio 2022 C++ Build Tools and a Windows SDK, or pass -BuildToolsRoot.'
    }
    $BuildToolsRoot = [IO.Path]::GetFullPath($BuildToolsRoot.Trim())
    $vcvars = Join-Path $BuildToolsRoot 'VC\Auxiliary\Build\vcvars64.bat'
    if (-not (Test-Path -LiteralPath $vcvars -PathType Leaf)) { throw "Missing x64 compiler environment: $vcvars" }
    $environmentLines = & $env:ComSpec /d /s /c "`"call `"$vcvars`" >nul && set`""
    if ($LASTEXITCODE -ne 0) { throw 'Visual Studio x64 environment initialization failed.' }
    foreach ($line in $environmentLines) {
        if ($line -match '^([^=]+)=(.*)$') { Set-Item -LiteralPath "Env:$($Matches[1])" -Value $Matches[2] }
    }
    foreach ($relative in @('Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin', 'Common7\IDE\CommonExtensions\Microsoft\CMake\Ninja')) {
        $directory = Join-Path $BuildToolsRoot $relative
        if (Test-Path -LiteralPath $directory -PathType Container) { $env:PATH = "$directory;$env:PATH" }
    }
    foreach ($tool in @('cl.exe', 'cmake.exe', 'ninja.exe', 'ctest.exe')) {
        if (-not (Get-Command $tool -ErrorAction SilentlyContinue)) { throw "Missing $tool. Install C++ CMake tools or add CMake and Ninja to PATH." }
    }
    return $BuildToolsRoot
}

function Resolve-Wr64Python {
    param([string]$Python = '')
    if ($Python) {
        $command = Get-Command $Python -ErrorAction Stop
    } else {
        $command = Get-Command python.exe -ErrorAction SilentlyContinue
        if (-not $command) { $command = Get-Command python3.exe -ErrorAction SilentlyContinue }
    }
    if (-not $command) { throw 'Python 3.11 or newer is required for these tests; add it to PATH or pass -Python.' }
    & $command.Source -c 'import sys; sys.exit(0 if sys.version_info >= (3, 11) else 1)'
    if ($LASTEXITCODE -ne 0) { throw 'Python 3.11 or newer is required.' }
    return $command.Source
}
