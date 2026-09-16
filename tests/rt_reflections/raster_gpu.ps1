[CmdletBinding()]
param(
    [string]$BuildToolsRoot = '',
    [string]$BuildDirectory = '',
    [string]$OutputDirectory = '',
    [string]$LibraryOverride = '',
    [string[]]$ShaderObjectOverride = @(),
    [ValidateSet('D3D12', 'Vulkan')][string]$Backend = 'D3D12',
    [switch]$VulkanValidation,
    [switch]$VulkanErrorContract,
    [switch]$VulkanUploadSync,
    [switch]$VulkanNativeFramebuffer,
    [switch]$VulkanNativeDepthMS,
    [switch]$VulkanRSPProcess,
    [string]$VulkanLayerPath = '',
    [ValidateSet(0, 1, 4)][int]$SampleCount = 0,
    [switch]$BackdropProbe,
    [switch]$NativeSampleLocations,
    [switch]$VulkanMsaaLifecycle,
    [switch]$VulkanRspCompute,
    [switch]$VulkanCombinedSky,
    [ValidateSet('64x64', '1280x720', '2560x1440')][string]$Resolution = '64x64',
    [switch]$SkyTransitionBaseline,
    [switch]$SkyBackdropBaseline,
    [switch]$ReadbackTrace,
    [switch]$QualityOptions,
    [switch]$ExplicitQualityDefaults,
    [switch]$AOExperiment,
    [switch]$PsoTiming,
    [switch]$AsyncCache,
    [switch]$SignatureVariant,
    [switch]$TwoPlayer,
    [switch]$Submission
)
$ErrorActionPreference = 'Stop'
. (Join-Path $PSScriptRoot '..\..\tools\windows-build-environment.ps1')
$BuildToolsRoot = Initialize-Wr64BuildEnvironment -BuildToolsRoot $BuildToolsRoot
$sourceRoot = [IO.Path]::GetFullPath((Join-Path $PSScriptRoot '..\..'))
if (-not $BuildDirectory) { $BuildDirectory = Join-Path $sourceRoot 'build' }
if (-not $OutputDirectory) { $OutputDirectory = Join-Path $sourceRoot 'build\test-output\rt-raster-gpu' }
$OutputDirectory = [IO.Path]::GetFullPath($OutputDirectory)
$rt64Library = Join-Path $BuildDirectory 'rt64\rt64.lib'
if ($LibraryOverride) { $rt64Library = [IO.Path]::GetFullPath($LibraryOverride) }
if ($ShaderObjectOverride) {
    if ($Backend -ne 'Vulkan') { throw 'Private shader object overrides require Backend Vulkan.' }
    $ShaderObjectOverride = @($ShaderObjectOverride | ForEach-Object {
        $overridePath = [IO.Path]::GetFullPath($_)
        if (-not (Test-Path -LiteralPath $overridePath)) { throw 'Private shader object override is missing.' }
        $overridePath
    })
}
if ($PsoTiming -and $AsyncCache) { throw 'Select only one diagnostic probe.' }
if ($Submission -and ($Backend -ne 'D3D12' -or $TwoPlayer -or $PsoTiming -or $AsyncCache)) {
    throw 'Submission is a separate D3D12 native raster regression.'
}
if ($TwoPlayer -and ($Backend -ne 'D3D12' -or $PsoTiming -or $AsyncCache -or $Resolution -ne '64x64')) {
    throw 'TwoPlayer requires the bounded D3D12 raster probe.'
}
if ($Backend -eq 'Vulkan' -and ($PsoTiming -or $AsyncCache -or $AOExperiment)) { throw 'Vulkan selection is supported by the production raster/quality fixtures only.' }
if ($VulkanValidation -and $Backend -ne 'Vulkan') { throw 'VulkanValidation requires Backend Vulkan.' }
if ($VulkanErrorContract -and $Backend -ne 'Vulkan') { throw 'VulkanErrorContract requires Backend Vulkan.' }
if (($VulkanNativeFramebuffer -or $VulkanNativeDepthMS -or $VulkanRSPProcess) -and ($Backend -ne 'Vulkan' -or -not $VulkanValidation -or ([int]$VulkanNativeFramebuffer.IsPresent + [int]$VulkanNativeDepthMS.IsPresent + [int]$VulkanRSPProcess.IsPresent -gt 1) -or $VulkanUploadSync -or $VulkanErrorContract -or $VulkanRspCompute -or $VulkanCombinedSky -or $VulkanMsaaLifecycle -or $SampleCount -or $BackdropProbe -or $QualityOptions -or $ReadbackTrace -or $AOExperiment -or $PsoTiming -or $AsyncCache -or $SkyTransitionBaseline -or $SkyBackdropBaseline -or $SignatureVariant)) {
    throw 'Native framebuffer modes require Vulkan core/sync validation and run separately from other fixture modes.'
}
if ($VulkanUploadSync -and ($Backend -ne 'Vulkan' -or $VulkanErrorContract -or $VulkanRspCompute -or $VulkanCombinedSky -or $VulkanMsaaLifecycle -or $SampleCount -or $BackdropProbe -or $QualityOptions -or $ReadbackTrace -or $AOExperiment -or $PsoTiming -or $AsyncCache -or $SkyTransitionBaseline -or $SkyBackdropBaseline -or $SignatureVariant)) {
    throw 'VulkanUploadSync requires Vulkan and runs separately from other fixture modes.'
}
if ($VulkanMsaaLifecycle -and ($Backend -ne 'Vulkan' -or -not $NativeSampleLocations -or $SampleCount -or $BackdropProbe -or $VulkanErrorContract)) {
    throw 'VulkanMsaaLifecycle requires Vulkan and NativeSampleLocations, with the full sample sequence and fixture suite.'
}
if ($VulkanRspCompute -and ($Backend -ne 'Vulkan' -or -not $NativeSampleLocations -or $VulkanMsaaLifecycle -or $BackdropProbe -or $VulkanErrorContract -or $QualityOptions -or $ReadbackTrace -or $AOExperiment -or $PsoTiming -or $AsyncCache -or $SkyTransitionBaseline -or $SkyBackdropBaseline -or $SignatureVariant)) {
    throw 'VulkanRspCompute requires Vulkan and NativeSampleLocations, separately from lifecycle and other fixture modes.'
}
if ($VulkanCombinedSky -and ($Backend -ne 'Vulkan' -or -not $NativeSampleLocations -or $SampleCount -ne 4 -or $VulkanRspCompute -or $VulkanMsaaLifecycle -or $BackdropProbe -or $VulkanErrorContract -or $ReadbackTrace -or $QualityOptions -or $AOExperiment -or $SkyTransitionBaseline -or $SkyBackdropBaseline -or $SignatureVariant)) {
    throw 'VulkanCombinedSky requires Vulkan, NativeSampleLocations and SampleCount4, separately from other fixture modes.'
}
if ($Resolution -ne '64x64' -and ((-not $VulkanRspCompute -and -not $VulkanCombinedSky) -or $SampleCount -ne 4)) {
    throw 'Large resolutions require a bounded VulkanRspCompute or VulkanCombinedSky diagnostic with SampleCount4.'
}
if ($VulkanLayerPath -and -not $VulkanValidation) { throw 'VulkanLayerPath requires VulkanValidation.' }
if ($VulkanLayerPath) {
    $VulkanLayerPath = [IO.Path]::GetFullPath($VulkanLayerPath)
    if (-not (Test-Path -LiteralPath (Join-Path $VulkanLayerPath 'VkLayer_khronos_validation.json'))) { throw 'VulkanLayerPath must contain the Khronos validation layer manifest.' }
}
if ($AOExperiment -and -not $LibraryOverride) { throw 'Parked AO tests require an explicit research shader library; the production shader contains no AO.' }
if ($ReadbackTrace -and ($AOExperiment -or $QualityOptions -or $SkyTransitionBaseline -or $SkyBackdropBaseline -or $SignatureVariant -or $PsoTiming -or $AsyncCache)) { throw 'ReadbackTrace compares the unmodified production suite; select it alone.' }
if ($QualityOptions -and ($AOExperiment -or $SkyTransitionBaseline -or $SkyBackdropBaseline -or $SignatureVariant -or $PsoTiming -or $AsyncCache)) { throw 'Select QualityOptions separately from other diagnostic modes.' }
if ($ExplicitQualityDefaults -and -not $ReadbackTrace) { throw 'ExplicitQualityDefaults requires ReadbackTrace.' }
$probeName = if ($Submission) { 'raster_submission_gpu' } elseif ($PsoTiming) { 'pso_timing' } elseif ($AsyncCache) { 'async_cache' } else { 'raster_gpu' }
if (-not (Test-Path -LiteralPath $rt64Library)) { throw 'Build the project first; this probe runs its actual embedded water shaders and PSOs.' }
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
$savedVulkanLayers = $env:VK_INSTANCE_LAYERS
$savedVulkanLayerPath = $env:VK_LAYER_PATH
$savedVulkanSyncValidation = $env:VK_LAYER_VALIDATE_SYNC
New-Item -ItemType Directory -Path $OutputDirectory -Force | Out-Null
Push-Location -LiteralPath $OutputDirectory
try {
    $env:INCLUDE = "$vcDirectory\include;$sdkRoot\Include\$sdkVersion\ucrt;$sdkRoot\Include\$sdkVersion\shared;$sdkRoot\Include\$sdkVersion\um"
    $env:LIB = "$vcDirectory\lib\x64;$sdkRoot\Lib\$sdkVersion\ucrt\x64;$sdkRoot\Lib\$sdkVersion\um\x64"
    $env:PATH = "$vcDirectory\bin\Hostx64\x64;$BuildDirectory\_deps\wr64-dxc-toolset;$env:PATH"
    $rt64Source = Join-Path $sourceRoot 'lib\rt64\src'
    $includePaths = @($rt64Source, "$rt64Source\contrib", "$rt64Source\contrib\plume", "$rt64Source\contrib\hlslpp\include",
        "$rt64Source\contrib\plume\contrib\D3D12MemoryAllocator\include", "$rt64Source\contrib\dxc\inc",
        "$rt64Source\contrib\plume\contrib\volk", "$rt64Source\contrib\plume\contrib\Vulkan-Headers\include",
        "$rt64Source\contrib\plume\contrib\VulkanMemoryAllocator\include",
        "$rt64Source\contrib\re-spirv\external\SPIRV-Headers\include", "$rt64Source\contrib\imgui")
    $includeArguments = @($includePaths | ForEach-Object { "/I$_" })
    $libraries = @($rt64Library, (Join-Path $BuildDirectory 'rt64\src\contrib\plume\plume.lib'),
        (Join-Path $BuildDirectory 'rt64\src\contrib\re-spirv\re-spirv.lib'),
        (Join-Path $BuildDirectory 'rt64\src\contrib\zstd\build\cmake\lib\zstd_static.lib'),
        (Join-Path $rt64Source 'contrib\dxc\lib\x64\dxcompiler.lib'))
    if ($ShaderObjectOverride) { $libraries = @($ShaderObjectOverride) + $libraries }
    & (Join-Path $vcDirectory 'bin\Hostx64\x64\cl.exe') /nologo /std:c++17 /EHsc /O2 /MD /DNDEBUG /DNOMINMAX /DHLSL_CPU `
        @includeArguments (Join-Path $PSScriptRoot "$probeName.cpp") "/Fe$OutputDirectory\$probeName.exe" `
        /link /OPT:REF @libraries d3d12.lib dxgi.lib dxguid.lib user32.lib
    if ($LASTEXITCODE -ne 0) { throw 'Production raster GPU probe compilation failed.' }
    $probeArguments = @((Join-Path $OutputDirectory 'raster'))
    if ($Backend -eq 'Vulkan') { $probeArguments += '--vulkan' }
    if ($VulkanErrorContract) { $probeArguments += '--vulkan-error-contract-only' }
    if ($VulkanUploadSync) { $probeArguments += '--vulkan-upload-sync-only' }
    if ($VulkanNativeFramebuffer) { $probeArguments += '--vulkan-native-fb-only' }
    if ($VulkanNativeDepthMS) { $probeArguments += '--vulkan-native-depth-ms-only' }
    if ($VulkanRSPProcess) { $probeArguments += '--vulkan-rsp-process-only' }
    if ($SampleCount) { $probeArguments += "--msaa-$SampleCount-only" }
    if ($BackdropProbe) { $probeArguments += '--backdrop-probe-only' }
    if ($NativeSampleLocations) { $probeArguments += '--native-sample-locations' }
    if ($VulkanMsaaLifecycle) { $probeArguments += '--vulkan-msaa-lifecycle' }
    if ($VulkanRspCompute) { $probeArguments += '--vulkan-rsp-compute' }
    if ($VulkanCombinedSky) { $probeArguments += '--vulkan-combined-sky' }
    if ($Resolution -ne '64x64') { $probeArguments += "--resolution-$Resolution" }
    if ($VulkanValidation) {
        $probeArguments += '--vulkan-validation'
        # Loader opt-in is scoped to this headless process and restored below.
        # The shipped frontend does not enable validation by default.
        $env:VK_INSTANCE_LAYERS = 'VK_LAYER_KHRONOS_validation'
        if ($VulkanLayerPath) { $env:VK_LAYER_PATH = $VulkanLayerPath }
        # Modern layer setting documented by Khronos' synchronization_usage.md.
        # This adds synchronization checks without disabling core validation.
        $env:VK_LAYER_VALIDATE_SYNC = '1'
    }
    if ($SignatureVariant) { $probeArguments += '--signature-variant' }
    if ($TwoPlayer) { $probeArguments += '--two-player-only' }
    if ($SkyTransitionBaseline) { $probeArguments += '--sky-transition-baseline' }
    if ($SkyBackdropBaseline) { $probeArguments += '--sky-backdrop-baseline' }
    if ($ReadbackTrace) { $probeArguments += '--readback-trace' }
    if ($ExplicitQualityDefaults) { $probeArguments += '--explicit-quality-defaults' }
    if ($QualityOptions) { $probeArguments += '--quality-options' }
    if ($AOExperiment) { $probeArguments += '--ao-experiment' }
    & (Join-Path $OutputDirectory "$probeName.exe") @probeArguments
    if ($LASTEXITCODE -eq 77) { Write-Output 'GPU probe skipped: hardware requirements are unavailable.' }
    elseif ($LASTEXITCODE -ne 0) { throw "Production raster GPU probe failed with exit code $LASTEXITCODE." }
}
finally {
    Pop-Location
    $env:INCLUDE = $savedInclude
    $env:LIB = $savedLib
    $env:PATH = $savedPath
    $env:VK_INSTANCE_LAYERS = $savedVulkanLayers
    $env:VK_LAYER_PATH = $savedVulkanLayerPath
    $env:VK_LAYER_VALIDATE_SYNC = $savedVulkanSyncValidation
}
