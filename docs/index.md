---
title: "Camera QA – Documentation"
---

# Camera QA – Documentation

This site documents the **public/user-facing** interface of the Camera QA reference buffer generator.

- *Reference buffer CLI:* [CLI reference](cli)

## Scope

At this stage, the project focuses on **test pattern generation** and producing deterministic RAW buffers for Camera QA.

## What is documented here (by design)

Only options that map to stable, SFNC-like camera parameters are documented:
- options that start with an **uppercase** letter after `--` (example: `--Width`)
- plus a small allowlist (`--output`, `--help`, `--version`, `--print-cli-json`)

Internal / placeholder / experimental options are intentionally excluded from public docs.
For the full option list, run `kaya-sw-camera_qa_reference_buffer.exe --help`.
