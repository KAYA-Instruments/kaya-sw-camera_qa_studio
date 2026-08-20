---
title: "Camera QA reference buffer generator"
description: "CLI reference"
permalink: /cli/
---

<style>
.cli-group > summary { cursor: pointer; list-style: none; }
.cli-group > summary::-webkit-details-marker { display: none; }
.cli-group > summary::marker { content: ""; }
.cli-group > summary::before { content: "▶"; display: inline-block; width: 1.25em; transition: transform 120ms ease-in-out; }
.cli-group[open] > summary::before { transform: rotate(90deg); }
</style>

This page lists the CLI options.

Options that start with an uppercase letter after `--` are camera parameters (SFNC-like).  
Options that start with a lowercase letter are additional utility tuning knobs; see each option's description for details.

For the authoritative built-in help, run:
`sar-sw-camera_qa_reference_buffer.exe --help`


## Synopsis

```text
sar-sw-camera_qa_reference_buffer.exe [OPTIONS]
```

## Options

Tip: groups below are collapsible (expand the ones you need).

<!-- AUTOGEN:OPTIONS:BEGIN -->

<details open class="cli-group" markdown="1">
  <summary class="cli-summary">OPTIONS</summary>
<div class="table-scroll">
<table class="cli-table">
  <colgroup>
    <col style="width: 220px;">
    <col style="width: 80px;">
    <col style="width: 220px;">
    <col style="width: 120px;">
    <col style="width: auto;">
  </colgroup>
  <thead>
    <tr>
      <th class="col-option">Option</th>
      <th class="col-required">Required</th>
      <th class="col-type">Type</th>
      <th class="col-default">Default</th>
      <th class="col-desc">Description</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td class="col-option"><code>--help</code></td>
      <td class="col-required">no</td>
      <td class="col-type"><code></code></td>
      <td class="col-default"><code></code></td>
      <td class="col-desc">Print this help message and exit</td>
    </tr>
  </tbody>
</table>
</div>
</details>

<details class="cli-group" markdown="1">
  <summary class="cli-summary">Image format</summary>
<div class="table-scroll">
<table class="cli-table">
  <colgroup>
    <col style="width: 220px;">
    <col style="width: 80px;">
    <col style="width: 220px;">
    <col style="width: 120px;">
    <col style="width: auto;">
  </colgroup>
  <thead>
    <tr>
      <th class="col-option">Option</th>
      <th class="col-required">Required</th>
      <th class="col-type">Type</th>
      <th class="col-default">Default</th>
      <th class="col-desc">Description</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td class="col-option"><code>--Width</code></td>
      <td class="col-required">yes</td>
      <td class="col-type"><code>UINT:POSITIVE</code></td>
      <td class="col-default"><code></code></td>
      <td class="col-desc">Image width in pixels</td>
    </tr>
    <tr>
      <td class="col-option"><code>--Height</code></td>
      <td class="col-required">yes</td>
      <td class="col-type"><code>UINT:POSITIVE</code></td>
      <td class="col-default"><code></code></td>
      <td class="col-desc">Image height in pixels</td>
    </tr>
    <tr>
      <td class="col-option"><code>--PixelFormat</code></td>
      <td class="col-required">yes</td>
      <td class="col-type"><code>TEXT:{Mono8,Mono10,Mono12,Mono14,Mono16,BayerGR8,BayerGR10,BayerGR12,BayerGR14,BayerRG8,BayerRG10,BayerRG12,BayerRG14,BayerGB8,BayerGB10,BayerGB12,BayerGB14,BayerBG8,BayerBG10,BayerBG12,BayerBG14,BayerGR16,BayerRG16,BayerGB16,BayerBG16}</code></td>
      <td class="col-default"><code></code></td>
      <td class="col-desc">PixelFormat: Mono{8,10,12,14,16}, Bayer{GR,RG,GB,BG}{8,10,12,14,16}</td>
    </tr>
    <tr>
      <td class="col-option"><code>--refstride</code></td>
      <td class="col-required">no</td>
      <td class="col-type"><code>UINT</code></td>
      <td class="col-default"><code>0</code></td>
      <td class="col-desc">Line stride in bytes (0 means default for selected I/O mode)</td>
    </tr>
  </tbody>
</table>
</div>
</details>

<details class="cli-group" markdown="1">
  <summary class="cli-summary">Test pattern</summary>
<div class="table-scroll">
<table class="cli-table">
  <colgroup>
    <col style="width: 220px;">
    <col style="width: 80px;">
    <col style="width: 220px;">
    <col style="width: 120px;">
    <col style="width: auto;">
  </colgroup>
  <thead>
    <tr>
      <th class="col-option">Option</th>
      <th class="col-required">Required</th>
      <th class="col-type">Type</th>
      <th class="col-default">Default</th>
      <th class="col-desc">Description</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td class="col-option"><code>--refinput</code></td>
      <td class="col-required">no</td>
      <td class="col-type"><code>TEXT:FILE</code></td>
      <td class="col-default"><code></code></td>
      <td class="col-desc">Input RAW file (required when --TestPattern is UserTestPattern)</td>
    </tr>
    <tr>
      <td class="col-option"><code>--TestPattern</code></td>
      <td class="col-required">yes</td>
      <td class="col-type"><code>TEXT</code></td>
      <td class="col-default"><code></code></td>
      <td class="col-desc">TestPattern: Off|GrayHorizontalRamp|GrayVerticalRamp|GrayDiagonalRamp|GrayDiagonalIntervalRamp|UserTestPattern or numeric code (e.g. 0x202)</td>
    </tr>
    <tr>
      <td class="col-option"><code>--TestPatternInterval</code></td>
      <td class="col-required">no</td>
      <td class="col-type"><code>UINT</code></td>
      <td class="col-default"><code>0</code></td>
      <td class="col-desc">Interval for GrayDiagonalIntervalRamp (required only for that pattern)</td>
    </tr>
    <tr>
      <td class="col-option"><code>--TestPatternValueMin</code></td>
      <td class="col-required">no</td>
      <td class="col-type"><code>UINT:UINT in [0 - 4294967295]</code></td>
      <td class="col-default"><code>0</code></td>
      <td class="col-desc">Test pattern value minimum (applied as: value = min + base * step). When --reftpg-RespectPixelFormat=true, values are interpreted in the PixelFormat domain; when false, in the internal --reftpg-bpp domain.</td>
    </tr>
    <tr>
      <td class="col-option"><code>--TestPatternValueMax</code></td>
      <td class="col-required">no</td>
      <td class="col-type"><code>INT:INT in [-1 - 4294967295]</code></td>
      <td class="col-default"><code>4095</code></td>
      <td class="col-desc">Test pattern value maximum. Use -1 to auto-calculate from --PixelFormat bit depth. When --reftpg-RespectPixelFormat=true, values are interpreted in the PixelFormat domain; when false, in the internal --reftpg-bpp domain.</td>
    </tr>
    <tr>
      <td class="col-option"><code>--TestPatternValueStep</code></td>
      <td class="col-required">no</td>
      <td class="col-type"><code>UINT:UINT in [1 - 4294967295]</code></td>
      <td class="col-default"><code>1</code></td>
      <td class="col-desc">Test pattern value step (applied as: value = min + base * step). When --reftpg-RespectPixelFormat=true, values are interpreted in the PixelFormat domain; when false, in the internal --reftpg-bpp domain.</td>
    </tr>
    <tr>
      <td class="col-option"><code>--reftpg-mode</code></td>
      <td class="col-required">no</td>
      <td class="col-type"><code>TEXT:{spec,developer}</code></td>
      <td class="col-default"><code>spec</code></td>
      <td class="col-desc">TPG mode: spec or developer</td>
    </tr>
    <tr>
      <td class="col-option"><code>--reftpg-fraction</code></td>
      <td class="col-required">no</td>
      <td class="col-type"><code>UINT</code></td>
      <td class="col-default"><code>8</code></td>
      <td class="col-desc">TPG fractional bits (F)</td>
    </tr>
    <tr>
      <td class="col-option"><code>--reftpg-bpp</code></td>
      <td class="col-required">no</td>
      <td class="col-type"><code>UINT:UINT in [1 - 16]</code></td>
      <td class="col-default"><code>12</code></td>
      <td class="col-desc">TPG internal bit depth (independent of PixelFormat)</td>
    </tr>
    <tr>
      <td class="col-option"><code>--reftpg-RespectPixelFormat</code></td>
      <td class="col-required">no</td>
      <td class="col-type"><code>BOOLEAN</code></td>
      <td class="col-default"><code>true</code></td>
      <td class="col-desc">When true, generate the visible test pattern in the output PixelFormat bit depth. Example: for Mono8, the ramp is defined in the 0..255 domain. When false, generate the pattern directly in the internal --reftpg-bpp domain instead. Use false to emulate legacy or buggy firmware that ignores PixelFormat during TPG generation.</td>
    </tr>
    <tr>
      <td class="col-option"><code>--reftpg-ramp</code></td>
      <td class="col-required">no</td>
      <td class="col-type"><code>TEXT:{native,fullscale}</code></td>
      <td class="col-default"><code>native</code></td>
      <td class="col-desc">Ramp progression mode: native or fullscale. native uses x, y, or x+y directly; fullscale normalizes the ramp so it spans the full available range across the image extent.</td>
    </tr>
    <tr>
      <td class="col-option"><code>--reftpg-overflow</code></td>
      <td class="col-required">no</td>
      <td class="col-type"><code>TEXT:{wrap,saturate}</code></td>
      <td class="col-default"><code>wrap</code></td>
      <td class="col-desc">Overflow handling for generated ramp values: wrap or saturate. Example for Mono8 diagonal ramp near overflow: wrap -&gt; ... FC FD FE FF 00 01 02 ..., saturate -&gt; ... FC FD FE FF FF FF FF ... . For fullscale ramps this usually has no visible effect because values are already inside range.</td>
    </tr>
    <tr>
      <td class="col-option"><code>--reftpg-clamp</code></td>
      <td class="col-required">no</td>
      <td class="col-type"><code></code></td>
      <td class="col-default"><code></code></td>
      <td class="col-desc">Clamp intermediate internal-domain values to the --reftpg-bpp range before storing them in the generated frame. This is an additional internal safety clamp; it does not define the visible ramp style and does not replace --reftpg-overflow.</td>
    </tr>
    <tr>
      <td class="col-option"><code>--reftpg-fixedpoint</code></td>
      <td class="col-required">no</td>
      <td class="col-type"><code>TEXT:{truncate,nearest}</code></td>
      <td class="col-default"><code>truncate</code></td>
      <td class="col-desc">Fixed-point rounding mode for FPGA-style arithmetic (truncate|nearest)</td>
    </tr>
  </tbody>
</table>
</div>
</details>

<details class="cli-group" markdown="1">
  <summary class="cli-summary">Defect pixel correction</summary>
<div class="table-scroll">
<table class="cli-table">
  <colgroup>
    <col style="width: 220px;">
    <col style="width: 80px;">
    <col style="width: 220px;">
    <col style="width: 120px;">
    <col style="width: auto;">
  </colgroup>
  <thead>
    <tr>
      <th class="col-option">Option</th>
      <th class="col-required">Required</th>
      <th class="col-type">Type</th>
      <th class="col-default">Default</th>
      <th class="col-desc">Description</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td class="col-option"><code>--DefectPixelCorrectionEnable</code></td>
      <td class="col-required">no</td>
      <td class="col-type"><code>BOOLEAN</code></td>
      <td class="col-default"><code>false</code></td>
      <td class="col-desc">Enable the Defect Pixel correction algorithm</td>
    </tr>
    <tr>
      <td class="col-option"><code>--DefectPixelSelector</code></td>
      <td class="col-required">no</td>
      <td class="col-type"><code>UINT</code></td>
      <td class="col-default"><code></code></td>
      <td class="col-desc">Select defect-pixel slot to configure (0-31). Unlike --BlackLevelSelector/--GainSelector, stays selected across multiple following writes until a different --DefectPixelSelector is given.</td>
    </tr>
    <tr>
      <td class="col-option"><code>--DefectPixelX</code></td>
      <td class="col-required">no</td>
      <td class="col-type"><code>INT</code></td>
      <td class="col-default"><code></code></td>
      <td class="col-desc">Defect pixel X coordinate for the selected slot (sensor-domain; -1 clears the slot)</td>
    </tr>
    <tr>
      <td class="col-option"><code>--DefectPixelY</code></td>
      <td class="col-required">no</td>
      <td class="col-type"><code>INT</code></td>
      <td class="col-default"><code></code></td>
      <td class="col-desc">Defect pixel Y coordinate for the selected slot (sensor-domain; -1 clears the slot)</td>
    </tr>
    <tr>
      <td class="col-option"><code>--DefectPixelRemove</code></td>
      <td class="col-required">no</td>
      <td class="col-type"><code></code></td>
      <td class="col-default"><code></code></td>
      <td class="col-desc">Remove the defect pixel at the selected slot (Command). Accepted for camera-compatibility parity with automated QA scripts that issue the same parameter sequence to a real camera and this utility; has no functional effect here, since nothing persists between runs.</td>
    </tr>
  </tbody>
</table>
</div>

## Defect Pixel Correction: frame-edge behavior

`--DefectPixelCorrectionEnable` corrects a configured pixel by averaging its two same-row neighbors (Mono: &plusmn;1px; Bayer: &plusmn;2px, same Bayer color), per the KAYA GenICam camera manual, section 7.8.1.

That manual does not state what happens when a configured coordinate is close enough to the left/right frame border that one of its two neighbors falls outside the frame. This utility's behavior (as of 2026-08-20): the single in-bounds neighbor is used for **both** terms of the average, rather than using the defect pixel's own (defective) value or rejecting the coordinate. This is informed by general image-sensor-processing literature on border-pixel handling in defect-correction filters, not by a KAYA-specific spec statement.

**This has not been verified against real KAYA/Iron4502 camera hardware.** If you have access to a camera exhibiting an edge-adjacent defect pixel, comparing its corrected output against this utility's output for the same coordinate would confirm or correct this assumption.

</details>

<details class="cli-group" markdown="1">
  <summary class="cli-summary">Black level correction</summary>
<div class="table-scroll">
<table class="cli-table">
  <colgroup>
    <col style="width: 220px;">
    <col style="width: 80px;">
    <col style="width: 220px;">
    <col style="width: 120px;">
    <col style="width: auto;">
  </colgroup>
  <thead>
    <tr>
      <th class="col-option">Option</th>
      <th class="col-required">Required</th>
      <th class="col-type">Type</th>
      <th class="col-default">Default</th>
      <th class="col-desc">Description</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td class="col-option"><code>--BlackLevelSelector</code></td>
      <td class="col-required">no</td>
      <td class="col-type"><code>TEXT:{All,Red,Green,Blue}</code></td>
      <td class="col-default"><code></code></td>
      <td class="col-desc">Select channel for the next --BlackLevel (All|Red|Green|Blue)</td>
    </tr>
    <tr>
      <td class="col-option"><code>--BlackLevel</code></td>
      <td class="col-required">no</td>
      <td class="col-type"><code>UINT:INT in [0 - 65535]</code></td>
      <td class="col-default"><code></code></td>
      <td class="col-desc">Set black level for the channel selected by the immediately preceding --BlackLevelSelector</td>
    </tr>
    <tr>
      <td class="col-option"><code>--refblc-all-added</code></td>
      <td class="col-required">no</td>
      <td class="col-type"><code>BOOLEAN</code></td>
      <td class="col-default"><code>true</code></td>
      <td class="col-desc">When true (default), BlackLevelSelector=All is an independent offset that is ADDED to per-channel black levels (SFNC-style). When false, BlackLevelSelector=All overrides per-channel values and cannot be mixed with them (legacy camera behavior).</td>
    </tr>
  </tbody>
</table>
</div>
</details>

<details class="cli-group" markdown="1">
  <summary class="cli-summary">Digital gain</summary>
<div class="table-scroll">
<table class="cli-table">
  <colgroup>
    <col style="width: 220px;">
    <col style="width: 80px;">
    <col style="width: 220px;">
    <col style="width: 120px;">
    <col style="width: auto;">
  </colgroup>
  <thead>
    <tr>
      <th class="col-option">Option</th>
      <th class="col-required">Required</th>
      <th class="col-type">Type</th>
      <th class="col-default">Default</th>
      <th class="col-desc">Description</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td class="col-option"><code>--GainSelector</code></td>
      <td class="col-required">no</td>
      <td class="col-type"><code>TEXT:{DigitalAll,DigitalRed,DigitalGreen,DigitalBlue}</code></td>
      <td class="col-default"><code></code></td>
      <td class="col-desc">Select channel for the next --Gain (DigitalAll|DigitalRed|DigitalGreen|DigitalBlue)</td>
    </tr>
    <tr>
      <td class="col-option"><code>--Gain</code></td>
      <td class="col-required">no</td>
      <td class="col-type"><code>FLOAT</code></td>
      <td class="col-default"><code></code></td>
      <td class="col-desc">Set gain for the channel selected by the immediately preceding --GainSelector (encoded using current --reftpg-fraction)</td>
    </tr>
  </tbody>
</table>
</div>
</details>

<details class="cli-group" markdown="1">
  <summary class="cli-summary">Auto Compensation ROI</summary>
<div class="table-scroll">
<table class="cli-table">
  <colgroup>
    <col style="width: 220px;">
    <col style="width: 80px;">
    <col style="width: 220px;">
    <col style="width: 120px;">
    <col style="width: auto;">
  </colgroup>
  <thead>
    <tr>
      <th class="col-option">Option</th>
      <th class="col-required">Required</th>
      <th class="col-type">Type</th>
      <th class="col-default">Default</th>
      <th class="col-desc">Description</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td class="col-option"><code>--AutoCompensationRoiOffsetX</code></td>
      <td class="col-required">no</td>
      <td class="col-type"><code>UINT</code></td>
      <td class="col-default"><code>0</code></td>
      <td class="col-desc">OffsetX of the statistics ROI shared by White Balance (sensor-domain; ROI-reuse rationale: https://sar-vision.github.io/sar-sw-camera_qa_studio/cli/#white-balance-statistics-roi-assumption)</td>
    </tr>
    <tr>
      <td class="col-option"><code>--AutoCompensationRoiOffsetY</code></td>
      <td class="col-required">no</td>
      <td class="col-type"><code>UINT</code></td>
      <td class="col-default"><code>0</code></td>
      <td class="col-desc">OffsetY of the statistics ROI shared by White Balance</td>
    </tr>
    <tr>
      <td class="col-option"><code>--AutoCompensationRoiWidth</code></td>
      <td class="col-required">no</td>
      <td class="col-type"><code>UINT</code></td>
      <td class="col-default"><code>0</code></td>
      <td class="col-desc">Width of the statistics ROI shared by White Balance. 0 (default) resolves to the full sensor-domain width minus OffsetX</td>
    </tr>
    <tr>
      <td class="col-option"><code>--AutoCompensationRoiHeight</code></td>
      <td class="col-required">no</td>
      <td class="col-type"><code>UINT</code></td>
      <td class="col-default"><code>0</code></td>
      <td class="col-desc">Height of the statistics ROI shared by White Balance. 0 (default) resolves to the full sensor-domain height minus OffsetY</td>
    </tr>
  </tbody>
</table>
</div>
</details>

<details class="cli-group" markdown="1">
  <summary class="cli-summary">White Balance</summary>
<div class="table-scroll">
<table class="cli-table">
  <colgroup>
    <col style="width: 220px;">
    <col style="width: 80px;">
    <col style="width: 220px;">
    <col style="width: 120px;">
    <col style="width: auto;">
  </colgroup>
  <thead>
    <tr>
      <th class="col-option">Option</th>
      <th class="col-required">Required</th>
      <th class="col-type">Type</th>
      <th class="col-default">Default</th>
      <th class="col-desc">Description</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td class="col-option"><code>--BalanceWhiteAuto</code></td>
      <td class="col-required">no</td>
      <td class="col-type"><code>TEXT:{Off,Once,Continuous,Manual}</code></td>
      <td class="col-default"><code>Off</code></td>
      <td class="col-desc">White balance mode: Off|Once|Continuous|Manual. Once and Continuous are identical in this tool (no multi-frame stream exists to make them differ): both compute gray-world statistics from the current frame and apply the result to that same frame. Manual is treated identically to Off (use --BalanceRatio verbatim).</td>
    </tr>
    <tr>
      <td class="col-option"><code>--BalanceWhiteCalculationMode</code></td>
      <td class="col-required">no</td>
      <td class="col-type"><code>TEXT:{HighestValue,Red,Green,Blue}</code></td>
      <td class="col-default"><code>Green</code></td>
      <td class="col-desc">Reference channel for gray-world normalization: HighestValue|Red|Green|Blue. Not given a default by the KAYA manual; this tool defaults to Green.</td>
    </tr>
    <tr>
      <td class="col-option"><code>--BalanceWhiteThreshold</code></td>
      <td class="col-required">no</td>
      <td class="col-type"><code>INT:INT in [-1 - 4294967295]</code></td>
      <td class="col-default"><code>-1</code></td>
      <td class="col-desc">Pixels above this value are excluded from gray-world statistics (ignores over-saturated pixels). Use -1 (default) to auto-resolve to the current PixelFormat's max value (no exclusion).</td>
    </tr>
    <tr>
      <td class="col-option"><code>--BalanceRatioSelector</code></td>
      <td class="col-required">no</td>
      <td class="col-type"><code>TEXT:{Red,Green,Blue}</code></td>
      <td class="col-default"><code></code></td>
      <td class="col-desc">Select channel for the next --BalanceRatio (Red|Green|Blue)</td>
    </tr>
    <tr>
      <td class="col-option"><code>--BalanceRatio</code></td>
      <td class="col-required">no</td>
      <td class="col-type"><code>FLOAT</code></td>
      <td class="col-default"><code></code></td>
      <td class="col-desc">Set BalanceRatio for the channel selected by the immediately preceding --BalanceRatioSelector (encoded using current --reftpg-fraction). Overwritten by the computed result when --BalanceWhiteAuto is Once or Continuous.</td>
    </tr>
  </tbody>
</table>
</div>
</details>

<details class="cli-group" markdown="1">
  <summary class="cli-summary">Pixel LUT</summary>
<div class="table-scroll">
<table class="cli-table">
  <colgroup>
    <col style="width: 220px;">
    <col style="width: 80px;">
    <col style="width: 220px;">
    <col style="width: 120px;">
    <col style="width: auto;">
  </colgroup>
  <thead>
    <tr>
      <th class="col-option">Option</th>
      <th class="col-required">Required</th>
      <th class="col-type">Type</th>
      <th class="col-default">Default</th>
      <th class="col-desc">Description</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td class="col-option"><code>--LUTSelector</code></td>
      <td class="col-required">no</td>
      <td class="col-type"><code>TEXT:{Red,Green,Blue,All}</code></td>
      <td class="col-default"><code></code></td>
      <td class="col-desc">Select LUT channel (Red|Green|Blue|All). SFNC additionally defines 'Luminance' and 'Device-specific' values, not implemented by this camera and not accepted here. 'All' (write convenience across the 3 per-channel tables) is a KAYA extension, not part of the SFNC enum. Unlike --BlackLevelSelector/--GainSelector, the selector stays active across multiple following LUT writes until a different --LUTSelector is given.</td>
    </tr>
    <tr>
      <td class="col-option"><code>--LUTEnable</code></td>
      <td class="col-required">no</td>
      <td class="col-type"><code>BOOLEAN</code></td>
      <td class="col-default"><code></code></td>
      <td class="col-desc">Activate the LUT selected by the immediately preceding --LUTSelector</td>
    </tr>
    <tr>
      <td class="col-option"><code>--LUTIndex</code></td>
      <td class="col-required">no</td>
      <td class="col-type"><code>UINT ...</code></td>
      <td class="col-default"><code></code></td>
      <td class="col-desc">Table index (offset) of the entry/entries to set in the selected LUT; accepts multiple values, matched pairwise with the following --LUTValue</td>
    </tr>
    <tr>
      <td class="col-option"><code>--LUTValue</code></td>
      <td class="col-required">no</td>
      <td class="col-type"><code>UINT ...</code></td>
      <td class="col-default"><code></code></td>
      <td class="col-desc">Value(s) to store at the entry/entries selected by the immediately preceding --LUTIndex</td>
    </tr>
    <tr>
      <td class="col-option"><code>--LUTValueAll</code></td>
      <td class="col-required">no</td>
      <td class="col-type"><code>TEXT:FILE</code></td>
      <td class="col-default"><code></code></td>
      <td class="col-desc">Load all coefficients of the selected LUT from a raw file (one 16-bit little-endian entry per table index, table size from --reftpg-bpp; only the low --reftpg-bpp bits of each entry are used)</td>
    </tr>
  </tbody>
</table>
</div>
</details>

<details class="cli-group" markdown="1">
  <summary class="cli-summary">Binning</summary>
<div class="table-scroll">
<table class="cli-table">
  <colgroup>
    <col style="width: 220px;">
    <col style="width: 80px;">
    <col style="width: 220px;">
    <col style="width: 120px;">
    <col style="width: auto;">
  </colgroup>
  <thead>
    <tr>
      <th class="col-option">Option</th>
      <th class="col-required">Required</th>
      <th class="col-type">Type</th>
      <th class="col-default">Default</th>
      <th class="col-desc">Description</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td class="col-option"><code>--BinningSelector</code></td>
      <td class="col-required">no</td>
      <td class="col-type"><code>TEXT:{Default,Sensor}</code></td>
      <td class="col-default"><code>Default</code></td>
      <td class="col-desc">GenICam: BinningSelector (Default or Sensor). Utility supports only Default (accepted for QA scripting parity)</td>
    </tr>
    <tr>
      <td class="col-option"><code>--BinningHorizontal</code></td>
      <td class="col-required">no</td>
      <td class="col-type"><code>UINT:UINT in [1 - 2]</code></td>
      <td class="col-default"><code>1</code></td>
      <td class="col-desc">GenICam: BinningHorizontal (1 or 2)</td>
    </tr>
    <tr>
      <td class="col-option"><code>--BinningVertical</code></td>
      <td class="col-required">no</td>
      <td class="col-type"><code>UINT:UINT in [1 - 2]</code></td>
      <td class="col-default"><code>1</code></td>
      <td class="col-desc">GenICam: BinningVertical (1 or 2)</td>
    </tr>
    <tr>
      <td class="col-option"><code>--BinningMode</code></td>
      <td class="col-required">no</td>
      <td class="col-type"><code>TEXT:{average,sum}</code></td>
      <td class="col-default"><code>average</code></td>
      <td class="col-desc">GenICam: BinningMode (average or sum)</td>
    </tr>
  </tbody>
</table>
</div>
</details>

<details class="cli-group" markdown="1">
  <summary class="cli-summary">Decimation</summary>
<div class="table-scroll">
<table class="cli-table">
  <colgroup>
    <col style="width: 220px;">
    <col style="width: 80px;">
    <col style="width: 220px;">
    <col style="width: 120px;">
    <col style="width: auto;">
  </colgroup>
  <thead>
    <tr>
      <th class="col-option">Option</th>
      <th class="col-required">Required</th>
      <th class="col-type">Type</th>
      <th class="col-default">Default</th>
      <th class="col-desc">Description</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td class="col-option"><code>--DecimationSelector</code></td>
      <td class="col-required">no</td>
      <td class="col-type"><code>TEXT:{Default,Sensor}</code></td>
      <td class="col-default"><code>Default</code></td>
      <td class="col-desc">GenICam: DecimationSelector (Default or Sensor). Utility supports only Default (accepted for QA scripting parity)</td>
    </tr>
    <tr>
      <td class="col-option"><code>--DecimationHorizontal</code></td>
      <td class="col-required">no</td>
      <td class="col-type"><code>UINT:UINT in [1 - 2]</code></td>
      <td class="col-default"><code>1</code></td>
      <td class="col-desc">GenICam: DecimationHorizontal (1 or 2)</td>
    </tr>
    <tr>
      <td class="col-option"><code>--DecimationVertical</code></td>
      <td class="col-required">no</td>
      <td class="col-type"><code>UINT:UINT in [1 - 2]</code></td>
      <td class="col-default"><code>1</code></td>
      <td class="col-desc">GenICam: DecimationVertical (1 or 2)</td>
    </tr>
  </tbody>
</table>
</div>
</details>

<details class="cli-group" markdown="1">
  <summary class="cli-summary">Output</summary>
<div class="table-scroll">
<table class="cli-table">
  <colgroup>
    <col style="width: 220px;">
    <col style="width: 80px;">
    <col style="width: 220px;">
    <col style="width: 120px;">
    <col style="width: auto;">
  </colgroup>
  <thead>
    <tr>
      <th class="col-option">Option</th>
      <th class="col-required">Required</th>
      <th class="col-type">Type</th>
      <th class="col-default">Default</th>
      <th class="col-desc">Description</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td class="col-option"><code>--refoutput</code></td>
      <td class="col-required">no</td>
      <td class="col-type"><code>TEXT</code></td>
      <td class="col-default"><code>@args@</code></td>
      <td class="col-desc">Output RAW file name (unpacked by default)</td>
    </tr>
    <tr>
      <td class="col-option"><code>--outdir</code></td>
      <td class="col-required">no</td>
      <td class="col-type"><code>TEXT</code></td>
      <td class="col-default"><code></code></td>
      <td class="col-desc">Optional output directory for both RAW output and log file</td>
    </tr>
  </tbody>
</table>
</div>
</details>

<details class="cli-group" markdown="1">
  <summary class="cli-summary">Extra</summary>
<div class="table-scroll">
<table class="cli-table">
  <colgroup>
    <col style="width: 220px;">
    <col style="width: 80px;">
    <col style="width: 220px;">
    <col style="width: 120px;">
    <col style="width: auto;">
  </colgroup>
  <thead>
    <tr>
      <th class="col-option">Option</th>
      <th class="col-required">Required</th>
      <th class="col-type">Type</th>
      <th class="col-default">Default</th>
      <th class="col-desc">Description</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td class="col-option"><code>--refdump-stages</code></td>
      <td class="col-required">no</td>
      <td class="col-type"><code></code></td>
      <td class="col-default"><code></code></td>
      <td class="col-desc">Dump intermediate buffers after each stage (not implemented yet)</td>
    </tr>
    <tr>
      <td class="col-option"><code>--refpacked-io</code></td>
      <td class="col-required">no</td>
      <td class="col-type"><code></code></td>
      <td class="col-default"><code></code></td>
      <td class="col-desc">Use packed RAW for input/output when bpp is 10/12/14 (default is unpacked 16-bit for &gt;8)</td>
    </tr>
    <tr>
      <td class="col-option"><code>--refdebayer</code></td>
      <td class="col-required">no</td>
      <td class="col-type"><code>TEXT:{nearest,bilinear}</code></td>
      <td class="col-default"><code></code></td>
      <td class="col-desc">Enable debayer output: nearest or bilinear</td>
    </tr>
  </tbody>
</table>
</div>
</details>

<details class="cli-group" markdown="1">
  <summary class="cli-summary">Meta</summary>
<div class="table-scroll">
<table class="cli-table">
  <colgroup>
    <col style="width: 220px;">
    <col style="width: 80px;">
    <col style="width: 220px;">
    <col style="width: 120px;">
    <col style="width: auto;">
  </colgroup>
  <thead>
    <tr>
      <th class="col-option">Option</th>
      <th class="col-required">Required</th>
      <th class="col-type">Type</th>
      <th class="col-default">Default</th>
      <th class="col-desc">Description</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td class="col-option"><code>--refconfig</code></td>
      <td class="col-required">no</td>
      <td class="col-type"><code>:FILE ...</code></td>
      <td class="col-default"><code></code></td>
      <td class="col-desc">Config file. TOML syntax: https://toml.io/en/ . Later config files may override earlier ones; command line options override config. Worked examples: this repository's TESTDIR/*.toml fixtures; [[blc]]/[[gain]]/[[lut]]/[[wb]] scripting-block contract: https://sar-vision.github.io/sar-sw-camera_qa_studio/cli/#toml-config-file-scripting-blocks</td>
    </tr>
    <tr>
      <td class="col-option"><code>--refversion</code></td>
      <td class="col-required">no</td>
      <td class="col-type"><code></code></td>
      <td class="col-default"><code></code></td>
      <td class="col-desc">Display program version information and exit</td>
    </tr>
    <tr>
      <td class="col-option"><code>--refprint-cli-json</code></td>
      <td class="col-required">no</td>
      <td class="col-type"><code></code></td>
      <td class="col-default"><code></code></td>
      <td class="col-desc">Print CLI schema as JSON and exit</td>
    </tr>
  </tbody>
</table>
</div>
</details>


<!-- AUTOGEN:OPTIONS:END -->

## TOML config-file scripting blocks

`--refconfig <file.toml>` (or a bare `.toml` path token) loads a config file. Plain `Key = value` lines at the top level set any CLI option directly (e.g. `Width = 640`). Four pipeline steps additionally support **repeated blocks** for scripting multiple assignments in one file: `[[blc]]`, `[[gain]]`, `[[lut]]`, `[[wb]]`. Config-file operations are always applied before command-line operations, regardless of where the `--refconfig` token sits among the CLI arguments.

### `[[blc]]` / `[[gain]]` / `[[wb]]`: one flat assignment per block

These three are a selector plus a single value, one full assignment per block:

```toml
[[blc]]
BlackLevelSelector = "Red"
BlackLevel = 1
[[blc]]
BlackLevelSelector = "Green"
BlackLevel = 2

[[gain]]
GainSelector = "DigitalRed"
Gain = 1.25

[[wb]]
BalanceRatioSelector = "Red"
BalanceRatio = 1.2
```

Each block is self-contained: both fields are required every time, in any order within the block.

### `[[lut]]`: ordered field-by-field writes, persistent selector

Pixel LUT has more write forms than a flat selector+value pair (`LUTEnable`, `LUTIndex`+`LUTValue`, `LUTValueAll`), all sharing one **persistent** `LUTSelector` - exactly like the command-line `--LUTSelector`/`--LUTEnable`/`--LUTIndex`/`--LUTValue`/`--LUTValueAll` options. Each field in a `[[lut]]` block fires its write immediately, in the exact order it's written in the file, and `LUTSelector` carries over from one block to the next if a later block omits it:

```toml
[[lut]]
LUTSelector = "Red"
LUTEnable = true
LUTIndex = [0, 5, 10]
LUTValue = [100, 105, 110]

[[lut]]
# no LUTSelector here - still applies to Red, the last one selected
LUTValueAll = "table.raw"
LUTIndex = [0]
LUTValue = [999]
```

The second block loads a whole table from `table.raw`, then immediately overrides index 0 to 999 - because that's the order the fields appear in the file, mirroring how a real LUT RAM entry is simply overwritten by whichever access happens later, regardless of which node performed it.

`[[lut]]` blocks do **not** use a discriminator field (there is no `Op = "..."` key anywhere in the contract). If you see a CLI error mentioning `Op`, remove that field and write `LUTEnable`/`LUTIndex`+`LUTValue`/`LUTValueAll` directly as their own keys instead, following the shape above.

<!-- fragments/defect_pixel_edge_handling.md now renders inline inside the "Defect pixel correction"
     <details> group (see scripts/gen_public_cli_md.py _GROUP_APPENDIX_FRAGMENTS), not here. -->
## White Balance: statistics ROI assumption

`--BalanceWhiteAuto` applies `Cw = BalanceRatio[c] * C` per Bayer channel (KAYA GenICam camera manual, section 7.5.5), where `BalanceRatio[c]` is either set manually (`--BalanceRatioSelector`/`--BalanceRatio`) or computed automatically from gray-world statistics gathered over a region of interest.

That manual's White Balance section (7.5.5) does not itself name which ROI feeds those statistics. The only statistics ROI defined anywhere in the manual is `AutoCompensationRoiWidth`/`AutoCompensationRoiHeight`/`AutoCompensationRoiOffsetX`/`AutoCompensationRoiOffsetY` (section 7.4.5), which the manual otherwise uses for the Auto Exposure/Gain brightness algorithm - a physical, analog-capture feature this utility does not implement (there is no real sensor to expose or gain-adjust). This utility assumes White Balance statistics reuse that same `AutoCompensationRoi*` window, since camera GenICam trees typically share one statistics-collection ROI across auto algorithms and the manual defines no alternative. **This is a documented assumption, not a KAYA-confirmed behavior.** If it turns out to be wrong, only the ROI source would need to change - the gray-world formula itself does not depend on where the ROI comes from.

`--BalanceWhiteAuto` mode semantics, specific to this being a single-shot buffer generator rather than a live multi-frame camera stream:

- **Off** - statistics are not gathered; `--BalanceRatio` is used exactly as given (default 1.0, i.e. no correction).
- **Manual** - treated identically to Off in this utility. The KAYA manual lists it as a distinct enum value, but a one-shot generator has no basis to distinguish "manual" from "auto disabled".
- **Once** and **Continuous** - identical in this utility: both gather gray-world statistics from the current frame within `AutoCompensationRoi*` (excluding pixels above `--BalanceWhiteThreshold`) and apply the computed ratio to that same frame. There is no frame-to-frame stream for "Continuous" to mean anything different against.

`--BalanceWhiteCalculationMode` (HighestValue/Red/Green/Blue) selects the reference channel the other channels are normalized against; the manual does not state a default, so this utility defaults to Green.

White Balance requires a Bayer `PixelFormat`. Unlike `--Gain` (which falls back to a single mono multiply when given a Mono frame), gray-world channel normalization has no meaning with only one channel, so enabling White Balance against a Mono `PixelFormat` is a hard CLI/runtime error rather than a silent no-op.

## Output auto-naming (`@args@`)

`--refoutput` supports a special value: `@args@`.

When `--refoutput @args@` is used, the utility auto-generates an output filename based on the effective CLI arguments.
This feature is relied upon by the workflow even if it is not currently shown in `--help`.

Example:

```text
sar-sw-camera_qa_reference_buffer.exe ^
  --Width 640 --Height 640 ^
  --PixelFormat Mono10 ^
  --TestPattern GrayDiagonalRamp ^
  --refoutput @args@
```

This will produce an output file named like:

```text
ref --Width 640 --Height 640 --PixelFormat Mono10 --TestPattern GrayDiagonalRamp.raw
```

## CLI schema export (`--refprint-cli-json`)

`--refprint-cli-json` prints a JSON schema describing all options.

Note: output includes a `CMDLINE:` prefix line before the JSON object.
Consumers should extract JSON by locating the first `{` and the last `}`.

