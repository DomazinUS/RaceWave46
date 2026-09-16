"""Exercise the real helper with a recording launcher; never start the game."""
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile

root = Path(sys.argv[1])
with tempfile.TemporaryDirectory(prefix="wr64-reflection-launch-") as temporary:
    directory = Path(temporary)
    shutil.copy2(root / "RUN-RT-REFLECTIONS.ps1", directory)
    (directory / "RUN-USA.ps1").write_text(r'''
param([string]$Aspect = '')
@{
    aspect = $Aspect
    api = $env:WR64_GRAPHICS_API
    debug = $env:WR64_RT_REFLECTIONS_DEBUG
    reflections = $env:WR64_RT_REFLECTIONS
    experimental_sky = $env:WR64_RT_SKY_EXPERIMENT
    experimental_shadows = $env:WR64_RT_SHADOW_EXPERIMENT
    experimental_ao = $env:WR64_RT_AO_EXPERIMENT
    experimental_motion_blur = $env:WR64_OBJECT_MOTION_BLUR_EXPERIMENT
} | ConvertTo-Json | Set-Content -LiteralPath (Join-Path $PSScriptRoot 'launch.json')
if ($env:WR64_TEST_LAUNCH_FAIL -eq '1') { throw 'simulated-launch-failure' }
''')
    wrapper = directory / "verify.ps1"
    wrapper.write_text(r'''
param([string]$DebugView, [string]$Expected, [switch]$Fail, [switch]$DefaultAspect,
    [switch]$ExperimentalSky, [switch]$RejectSky, [string]$PriorSky = '77', [switch]$AbsentSky,
    [switch]$ExperimentalShadows, [switch]$RejectShadows, [string]$PriorShadows = '77', [switch]$AbsentShadows,
    [switch]$ExperimentalAO, [switch]$RejectAO, [string]$PriorAO = '77', [switch]$AbsentAO,
    [switch]$ExperimentalMotionBlur, [string]$PriorMotionBlur = '77', [switch]$AbsentMotionBlur)
$ErrorActionPreference = 'Stop'
$env:WR64_GRAPHICS_API = 'vulkan'
$env:WR64_RT_REFLECTIONS_DEBUG = '77'
$env:WR64_EXPERIMENTAL_3D_ASPECT = '16:9'
$env:WR64_RT_REFLECTIONS = '0'
$env:WR64_RT_SKY_EXPERIMENT = if ($AbsentSky) { $null } else { $PriorSky }
$env:WR64_RT_SHADOW_EXPERIMENT = if ($AbsentShadows) { $null } else { $PriorShadows }
$env:WR64_RT_AO_EXPERIMENT = if ($AbsentAO) { $null } else { $PriorAO }
$env:WR64_OBJECT_MOTION_BLUR_EXPERIMENT = if ($AbsentMotionBlur) { $null } else { $PriorMotionBlur }
$env:WR64_TEST_LAUNCH_FAIL = if ($Fail) { '1' } else { '0' }
$caught = $false
$options = @{ DebugView = $DebugView }
if (-not $DefaultAspect) { $options.Aspect = '21:9' }
if ($ExperimentalSky) { $options.ExperimentalSky = $true }
if ($ExperimentalShadows) { $options.ExperimentalShadows = $true }
if ($ExperimentalAO) { $options.ExperimentalAO = $true }
if ($ExperimentalMotionBlur) { $options.ExperimentalMotionBlur = $true }
$launchPath = Join-Path $PSScriptRoot 'launch.json'
if (Test-Path -LiteralPath $launchPath) { Remove-Item -LiteralPath $launchPath }
try { & (Join-Path $PSScriptRoot 'RUN-RT-REFLECTIONS.ps1') @options }
catch {
    if ($RejectSky) {
        if ($_ -notmatch 'require -ExperimentalSky') { throw }
    }
    elseif ($RejectShadows) {
        if ($_ -notmatch 'require -ExperimentalShadows') { throw }
    }
    elseif ($RejectAO) {
        if ($_ -notmatch 'require -ExperimentalAO') { throw }
    }
    elseif (-not $Fail -or $_ -notmatch 'simulated-launch-failure') { throw }
    $caught = $true
}
if ($caught -ne ($Fail.IsPresent -or $RejectSky.IsPresent -or $RejectShadows.IsPresent -or $RejectAO.IsPresent)) {
    throw 'Helper did not propagate the expected failure'
}
if ($env:WR64_GRAPHICS_API -ne 'vulkan' -or $env:WR64_RT_REFLECTIONS_DEBUG -ne '77' -or
    $env:WR64_EXPERIMENTAL_3D_ASPECT -ne '16:9') { throw 'Helper leaked a test override into the caller' }
if ($AbsentSky) {
    if (Test-Path Env:WR64_RT_SKY_EXPERIMENT) { throw 'Helper left an experimental sky override in the caller' }
}
elseif ($env:WR64_RT_SKY_EXPERIMENT -ne $PriorSky) { throw 'Helper did not restore the experimental sky override' }
if ($AbsentShadows) {
    if (Test-Path Env:WR64_RT_SHADOW_EXPERIMENT) { throw 'Helper left an experimental shadow override in the caller' }
}
elseif ($env:WR64_RT_SHADOW_EXPERIMENT -ne $PriorShadows) { throw 'Helper did not restore the experimental shadow override' }
if ($AbsentAO) {
    if (Test-Path Env:WR64_RT_AO_EXPERIMENT) { throw 'Helper left an experimental AO override in the caller' }
}
elseif ($env:WR64_RT_AO_EXPERIMENT -ne $PriorAO) { throw 'Helper did not restore the experimental AO override' }
if ($AbsentMotionBlur) {
    if (Test-Path Env:WR64_OBJECT_MOTION_BLUR_EXPERIMENT) { throw 'Helper left an experimental motion-blur override in the caller' }
}
elseif ($env:WR64_OBJECT_MOTION_BLUR_EXPERIMENT -ne $PriorMotionBlur) { throw 'Helper did not restore the experimental motion-blur override' }
if ($RejectSky -or $RejectShadows -or $RejectAO) {
    if (Test-Path -LiteralPath $launchPath) { throw 'Rejected diagnostics still launched the game' }
    exit 0
}
$launch = Get-Content -LiteralPath $launchPath -Raw | ConvertFrom-Json
$expectedAspect = if ($DefaultAspect) { '' } else { '21:9' }
if ($launch.api -ne 'd3d12' -or $launch.debug -ne $Expected -or $launch.aspect -ne $expectedAspect) {
    throw 'Helper did not forward the selected test API/aspect/debug view'
}
if ($launch.reflections -ne '0') { throw 'Helper overwrote the frontend-owned reflection setting' }
$expectedSky = if ($ExperimentalSky) { '1' } else { '0' }
if ($launch.experimental_sky -ne $expectedSky) { throw 'Helper did not isolate the experimental sky override' }
$expectedShadows = if ($ExperimentalShadows) { '1' } else { '0' }
if ($launch.experimental_shadows -ne $expectedShadows) { throw 'Helper did not isolate the experimental shadow override' }
$expectedAO = if ($ExperimentalAO) { '1' } else { '0' }
if ($launch.experimental_ao -ne $expectedAO) { throw 'Helper did not isolate the experimental AO override' }
$expectedMotionBlur = if ($ExperimentalMotionBlur) { '1' } else { '0' }
if ($launch.experimental_motion_blur -ne $expectedMotionBlur) { throw 'Helper did not isolate the experimental motion-blur override' }
''')
    cases = (
        ("None", "0", ("-DefaultAspect",)),
        ("None", "0", ()),
        ("Normals", "1", ()),
        ("Hits", "2", ()),
        ("SkyCoverage", "3", ("-ExperimentalSky",)),
        ("SkyColor", "4", ("-ExperimentalSky",)),
        ("Hits", "2", ("-Fail",)),
        ("SkyCoverage", "3", ("-RejectSky",)),
        ("SkyColor", "4", ("-RejectSky", "-PriorSky", "1")),
        ("None", "0", ("-PriorSky", "1")),
        ("None", "0", ("-AbsentSky",)),
        ("None", "0", ("-ExperimentalSky", "-DefaultAspect")),
        ("None", "0", ("-ExperimentalSky", "-AbsentSky", "-Fail")),
        ("SkyColor", "4", ("-ExperimentalSky", "-PriorSky", "1", "-Fail")),
        ("SkyCoverage", "3", ("-RejectSky", "-AbsentSky")),
        # Shadow diagnostics require their own explicit switch even when the
        # inherited environment or the independent sky trial is enabled.
        ("Shadows", "5", ("-RejectShadows",)),
        ("Shadows", "5", ("-RejectShadows", "-PriorShadows", "1")),
        ("Shadows", "5", ("-RejectShadows", "-AbsentShadows")),
        ("Shadows", "5", ("-RejectShadows", "-ExperimentalSky")),
        ("SkyColor", "4", ("-RejectSky", "-ExperimentalShadows")),
        ("None", "0", ("-PriorShadows", "1", "-PriorSky", "1")),
        ("None", "0", ("-AbsentShadows", "-AbsentSky")),
        ("None", "0", ("-ExperimentalShadows", "-DefaultAspect")),
        ("Shadows", "5", ("-ExperimentalShadows",)),
        ("Shadows", "5", ("-ExperimentalShadows", "-PriorShadows", "1")),
        ("Shadows", "5", ("-ExperimentalShadows", "-AbsentShadows")),
        ("None", "0", ("-ExperimentalShadows", "-ExperimentalSky")),
        ("SkyColor", "4", ("-ExperimentalShadows", "-ExperimentalSky")),
        ("Shadows", "5", ("-ExperimentalShadows", "-ExperimentalSky")),
        # Failure must restore both independent trial environments, including
        # absence, and must not change the frontend-owned reflection choice.
        ("Shadows", "5", ("-ExperimentalShadows", "-Fail")),
        ("Shadows", "5", ("-ExperimentalShadows", "-AbsentShadows", "-Fail")),
        ("Shadows", "5", ("-ExperimentalShadows", "-ExperimentalSky", "-Fail")),
        ("SkyColor", "4", ("-ExperimentalShadows", "-ExperimentalSky", "-AbsentShadows", "-AbsentSky", "-Fail")),
        # Each new effect is independently opt-in. The diagnostic must not
        # activate AO through an inherited environment or another effect.
        ("AO", "6", ("-RejectAO",)),
        ("AO", "6", ("-RejectAO", "-PriorAO", "1")),
        ("AO", "6", ("-RejectAO", "-AbsentAO")),
        ("AO", "6", ("-RejectAO", "-ExperimentalMotionBlur", "-ExperimentalShadows")),
        ("None", "0", ("-PriorAO", "1", "-PriorMotionBlur", "1")),
        ("None", "0", ("-AbsentAO", "-AbsentMotionBlur")),
        ("None", "0", ("-ExperimentalAO", "-DefaultAspect")),
        ("AO", "6", ("-ExperimentalAO",)),
        ("AO", "6", ("-ExperimentalAO", "-PriorAO", "1")),
        ("AO", "6", ("-ExperimentalAO", "-AbsentAO")),
        ("None", "0", ("-ExperimentalMotionBlur", "-DefaultAspect")),
        ("None", "0", ("-ExperimentalMotionBlur", "-PriorMotionBlur", "1")),
        ("None", "0", ("-ExperimentalMotionBlur", "-AbsentMotionBlur")),
        ("None", "0", ("-ExperimentalAO", "-ExperimentalMotionBlur")),
        ("AO", "6", ("-ExperimentalAO", "-ExperimentalMotionBlur", "-ExperimentalSky", "-ExperimentalShadows")),
        ("AO", "6", ("-ExperimentalAO", "-Fail")),
        ("AO", "6", ("-ExperimentalAO", "-AbsentAO", "-Fail")),
        ("None", "0", ("-ExperimentalMotionBlur", "-Fail")),
        ("None", "0", ("-ExperimentalMotionBlur", "-AbsentMotionBlur", "-Fail")),
        ("AO", "6", ("-ExperimentalAO", "-ExperimentalMotionBlur", "-ExperimentalSky", "-ExperimentalShadows", "-AbsentAO", "-AbsentMotionBlur", "-AbsentSky", "-AbsentShadows", "-Fail")),
    )
    for mode, expected, switches in cases:
        arguments = ["powershell.exe", "-NoProfile", "-NonInteractive", "-ExecutionPolicy", "Bypass",
                     "-File", str(wrapper), "-DebugView", mode, "-Expected", expected]
        arguments.extend(switches)
        subprocess.run(arguments, check=True, creationflags=subprocess.CREATE_NO_WINDOW)
print(f"Passed {len(cases)} real helper launch/rejection/override-restoration cases without opening the game.")
