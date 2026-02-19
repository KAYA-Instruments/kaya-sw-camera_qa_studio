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
`kaya-sw-camera_qa_reference_buffer.exe --help`


## Synopsis

```text
kaya-sw-camera_qa_reference_buffer.exe [OPTIONS]
```

## Options

Tip: groups below are collapsible (expand the ones you need).

<!-- AUTOGEN:OPTIONS:BEGIN -->

<details open class="cli-group">
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

<details class="cli-group">
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
      <td class="col-desc">PixelFormat: Mono8/Mono10/Mono12/Mono14/Mono16, Bayer{GR,RG,GB,BG}{8,10,12,14,16}</td>
    </tr>
    <tr>
      <td class="col-option"><code>--stride</code></td>
      <td class="col-required">no</td>
      <td class="col-type"><code>UINT</code></td>
      <td class="col-default"><code>0</code></td>
      <td class="col-desc">Line stride in bytes (0 means default for selected I/O mode)</td>
    </tr>
  </tbody>
</table>
</div>
</details>

<details class="cli-group">
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
      <td class="col-option"><code>--input</code></td>
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
      <td class="col-desc">Test pattern value minimum (applied as: value = min + base * step). When --tpgRespectPixelFormat=true, values are interpreted in the PixelFormat domain; when false, in the internal --tpg-bpp domain.</td>
    </tr>
    <tr>
      <td class="col-option"><code>--TestPatternValueMax</code></td>
      <td class="col-required">no</td>
      <td class="col-type"><code>INT:INT in [-1 - 4294967295]</code></td>
      <td class="col-default"><code>4095</code></td>
      <td class="col-desc">Test pattern value maximum. Use -1 to auto-calculate from --PixelFormat bit depth. When --tpgRespectPixelFormat=true, values are interpreted in the PixelFormat domain; when false, in the internal --tpg-bpp domain.</td>
    </tr>
    <tr>
      <td class="col-option"><code>--TestPatternValueStep</code></td>
      <td class="col-required">no</td>
      <td class="col-type"><code>UINT:UINT in [1 - 4294967295]</code></td>
      <td class="col-default"><code>1</code></td>
      <td class="col-desc">Test pattern value step (applied as: value = min + base * step). When --tpgRespectPixelFormat=true, values are interpreted in the PixelFormat domain; when false, in the internal --tpg-bpp domain.</td>
    </tr>
    <tr>
      <td class="col-option"><code>--tpg-mode</code></td>
      <td class="col-required">no</td>
      <td class="col-type"><code>TEXT:{spec,developer}</code></td>
      <td class="col-default"><code>spec</code></td>
      <td class="col-desc">TPG mode: spec or developer</td>
    </tr>
    <tr>
      <td class="col-option"><code>--tpg-fraction</code></td>
      <td class="col-required">no</td>
      <td class="col-type"><code>UINT</code></td>
      <td class="col-default"><code>8</code></td>
      <td class="col-desc">TPG fractional bits (F)</td>
    </tr>
    <tr>
      <td class="col-option"><code>--tpg-bpp</code></td>
      <td class="col-required">no</td>
      <td class="col-type"><code>UINT:UINT in [1 - 16]</code></td>
      <td class="col-default"><code>12</code></td>
      <td class="col-desc">TPG internal bit depth (independent of PixelFormat)</td>
    </tr>
    <tr>
      <td class="col-option"><code>--tpgRespectPixelFormat</code></td>
      <td class="col-required">no</td>
      <td class="col-type"><code>BOOLEAN</code></td>
      <td class="col-default"><code>true</code></td>
      <td class="col-desc">When true (default), scale TPG so that --PixelFormat bit depth is respected (emulate fixed firmware). When false, keep legacy behavior: TPG operates purely in internal --tpg-bpp domain (emulate buggy firmware).</td>
    </tr>
    <tr>
      <td class="col-option"><code>--tpg-clamp</code></td>
      <td class="col-required">no</td>
      <td class="col-type"><code></code></td>
      <td class="col-default"><code></code></td>
      <td class="col-desc">Clamp TPG values to output bit depth (off by default)</td>
    </tr>
    <tr>
      <td class="col-option"><code>--tpg-fullscale</code></td>
      <td class="col-required">no</td>
      <td class="col-type"><code></code></td>
      <td class="col-default"><code></code></td>
      <td class="col-desc">Internal: generate full-scale ramps in output bit depth (non-firmware policy)</td>
    </tr>
    <tr>
      <td class="col-option"><code>--tpg-modulo</code></td>
      <td class="col-required">no</td>
      <td class="col-type"><code></code></td>
      <td class="col-default"><code></code></td>
      <td class="col-desc">Internal: generate modulo-wrapped ramps in output bit depth (non-firmware policy)</td>
    </tr>
  </tbody>
</table>
</div>
</details>

<details class="cli-group">
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
      <td class="col-option"><code>--blc-all-added</code></td>
      <td class="col-required">no</td>
      <td class="col-type"><code>BOOLEAN</code></td>
      <td class="col-default"><code>true</code></td>
      <td class="col-desc">When true (default), BlackLevelSelector=All is an independent offset that is ADDED to per-channel black levels (SFNC-style). When false, BlackLevelSelector=All overrides per-channel values and cannot be mixed with them (legacy camera behavior).</td>
    </tr>
  </tbody>
</table>
</div>
</details>

<details class="cli-group">
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

<details class="cli-group">
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

<details class="cli-group">
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
      <td class="col-option"><code>--output</code></td>
      <td class="col-required">yes</td>
      <td class="col-type"><code>TEXT</code></td>
      <td class="col-default"><code></code></td>
      <td class="col-desc">Output RAW file (unpacked by default)</td>
    </tr>
  </tbody>
</table>
</div>
</details>

<details class="cli-group">
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
      <td class="col-option"><code>--dump-stages</code></td>
      <td class="col-required">no</td>
      <td class="col-type"><code></code></td>
      <td class="col-default"><code></code></td>
      <td class="col-desc">Dump intermediate buffers after each stage (not implemented yet)</td>
    </tr>
    <tr>
      <td class="col-option"><code>--packed-io</code></td>
      <td class="col-required">no</td>
      <td class="col-type"><code></code></td>
      <td class="col-default"><code></code></td>
      <td class="col-desc">Use packed RAW for input/output when bpp is 10/12/14 (default is unpacked 16-bit for &gt;8)</td>
    </tr>
    <tr>
      <td class="col-option"><code>--debayer</code></td>
      <td class="col-required">no</td>
      <td class="col-type"><code>TEXT:{nearest,bilinear}</code></td>
      <td class="col-default"><code></code></td>
      <td class="col-desc">Enable debayer output: nearest or bilinear</td>
    </tr>
  </tbody>
</table>
</div>
</details>

<details class="cli-group">
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
      <td class="col-option"><code>--config</code></td>
      <td class="col-required">no</td>
      <td class="col-type"><code>:FILE</code></td>
      <td class="col-default"><code></code></td>
      <td class="col-desc">Config file (TOML/INI). Command line options override config.</td>
    </tr>
    <tr>
      <td class="col-option"><code>--version</code></td>
      <td class="col-required">no</td>
      <td class="col-type"><code></code></td>
      <td class="col-default"><code></code></td>
      <td class="col-desc">Display program version information and exit</td>
    </tr>
    <tr>
      <td class="col-option"><code>--print-cli-json</code></td>
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

## Output auto-naming (`@args@`)

`--output` supports a special value: `@args@`.

When `--output @args@` is used, the utility auto-generates an output filename based on the effective CLI arguments.
This feature is relied upon by the workflow even if it is not currently shown in `--help`.

Example:

```text
kaya-sw-camera_qa_reference_buffer.exe ^
  --Width 640 --Height 640 ^
  --PixelFormat Mono10 ^
  --TestPattern GrayDiagonalRamp ^
  --output @args@
```

This will produce an output file named like:

```text
out --Width 640 --Height 640 --PixelFormat Mono10 --TestPattern GrayDiagonalRamp.raw
```

## CLI schema export (`--print-cli-json`)

`--print-cli-json` prints a JSON schema describing all options.

Note: output includes a `CMDLINE:` prefix line before the JSON object.
Consumers should extract JSON by locating the first `{` and the last `}`.

