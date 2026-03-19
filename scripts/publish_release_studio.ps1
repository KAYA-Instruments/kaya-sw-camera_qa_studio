param(
    [Parameter(Mandatory=$true)]
    [string]$ExePath,
    [string]$RepoFullName = "KAYA-Instruments/kaya-sw-camera_qa_studio",
    [string]$InputJsonFile = "release\release_input.json"
)

$ErrorActionPreference = "Stop"

# Determine repository root as the parent directory of this script.  This assumes
# the script is located in a `scripts` subdirectory of the repository.
$scriptRoot = Split-Path -Parent $MyInvocation.MyCommand.Definition
$repoRoot = Split-Path -Parent $scriptRoot

# Validate the executable path.
if (-not (Test-Path -LiteralPath $ExePath)) {
    throw "Executable not found: $ExePath"
}

# Load user-provided configuration for suffix, notes file, draft/prerelease flags, and base version.
$inputPath = Join-Path $repoRoot $InputJsonFile
if (-not (Test-Path -LiteralPath $inputPath)) {
    throw "Release input file not found: $inputPath"
}
$config = Get-Content -Path $inputPath -Raw | ConvertFrom-Json

$suffix = $config.suffix
    # Sanitize the suffix read from the JSON config by replacing whitespace with underscores.
    if ($suffix) {
        $suffix = $suffix -replace "\s+", "_"
    }
$notesFileRel = $config.notes_file
$isPrerelease = $config.is_prerelease
$isDraft = $config.is_draft
$baseNumber = $config.base_number

# Fetch existing release tags and determine the highest numeric part.  Also record
# the full tag corresponding to the highest number for changelog comparison.
$releasesJson = gh release list --repo $RepoFullName --limit 100 --json tagName | ConvertFrom-Json
$maxNum = 0
$previousTag = $null
foreach ($rel in $releasesJson) {
    $tag = $rel.tagName
    if ($tag -match '^v0-0-(\d+)(?:_.*)?$') {
        $num = [int]$matches[1]
        if ($num -gt $maxNum) {
            $maxNum = $num
            $previousTag = $tag
        }
    }
}

# Override the computed version number if a base_number is specified and larger than
# any existing version.  This allows jumping ahead in version sequences while
# still referencing the most recent existing tag for changelog purposes.
if ($baseNumber -ne $null) {
    try { $baseInt = [int]$baseNumber } catch { throw "base_number must be an integer. Provided: $baseNumber" }
    if ($baseInt -gt $maxNum) { $maxNum = $baseInt }
}

$newNum = $maxNum + 1
$newTag = "v0-0-$newNum"
if ($suffix) { $newTag = "${newTag}_${suffix}" }
$newTitle = $newTag

# Prepare arguments for `gh release create`.  Always specify the asset and
# repository name, and set the title to match the tag.
$ghArgs = @(
    $newTag
    $ExePath
    "--title"
    $newTitle
    "--repo"
    $RepoFullName
)

# If a notes file is provided, extract two pieces of information:
# 1) A single-line release title suffix between '--Release title begin--' and
#    '--Release title end--'.  This value is used as the suffix portion of
#    the Git tag and release title (e.g. the '_release_automation' part).
# 2) Multi-line release notes between '--Notes begin--' and '--Notes end--'.
#    These notes are prepended to the auto-generated notes.  Both sections are
#    removed from the file after publishing so the file remains unchanged in
#    version control.  If no notes file is specified, rely solely on
#    auto-generated notes and any suffix supplied in the JSON config.
if ($notesFileRel) {
    $notesPath = Join-Path $repoRoot $notesFileRel
    if (-not (Test-Path -LiteralPath $notesPath)) {
        throw "Notes file not found: $notesPath"
    }
    # Read the entire file as a single string. We need to retain the original
    # end-of-line style (CRLF vs LF) to avoid rewriting the file with a
    # different newline convention. Using -Raw gives us the file verbatim.
    $fileContent = Get-Content -LiteralPath $notesPath -Raw -Encoding UTF8

    # Detect the newline delimiter used in the file. If CRLF is present
    # anywhere, assume CRLF; otherwise fallback to LF. This preserves
    # Windows vs. Unix line endings. PowerShell does not support the
    # ternary operator, so use an if/else statement instead of "? :".
    if ($fileContent -match "`r`n") {
        $delimiter = "`r`n"
    } else {
        $delimiter = "`n"
    }

    # Split the file into lines using the detected delimiter. Note that the
    # delimiter characters are not included in the resulting strings.
    $lines = $fileContent -split [regex]::Escape($delimiter)

    # Locate markers for title and notes sections.  Initialise indices to -1.
    $notesStartIdx = -1
    $notesEndIdx   = -1
    $titleStartIdx = -1
    $titleEndIdx   = -1
    for ($i = 0; $i -lt $lines.Length; $i++) {
        $trim = $lines[$i].Trim()
        if ($trim -eq "--Notes begin--")       { $notesStartIdx = $i }
        elseif ($trim -eq "--Notes end--")     { $notesEndIdx   = $i }
        elseif ($trim -eq "--Release title begin--") { $titleStartIdx = $i }
        elseif ($trim -eq "--Release title end--")   { $titleEndIdx   = $i }
    }

    # Validate the title markers and extract exactly one line of title suffix.
    if ($titleStartIdx -lt 0 -or $titleEndIdx -lt 0 -or $titleEndIdx -le $titleStartIdx) {
        throw "The notes file must contain '--Release title begin--' and '--Release title end--' markers with the title line between them."
    }
    $titleLines = $lines[($titleStartIdx + 1)..($titleEndIdx - 1)]
    if ($titleLines.Count -ne 1) {
        throw "There must be exactly one line of text between '--Release title begin--' and '--Release title end--'."
    }
    $titleLine = $titleLines[0].Trim()
    if ([string]::IsNullOrWhiteSpace($titleLine)) {
        throw "No release title found between '--Release title begin--' and '--Release title end--'. Please insert a single line."
    }
    # Override the suffix from the JSON config with the value from the title markers.
    # Replace any whitespace in the title with underscores to produce a valid tag suffix.
    $suffix = $titleLine -replace "\s+", "_"

    # Recompute the tag and title now that the suffix has changed.  The version
    # number $newNum is already determined from the existing releases and any
    # base_number override.  Update the base arguments array accordingly.
    $newTag = "v0-0-$newNum"
    if ($suffix) { $newTag = "${newTag}_${suffix}" }
    $newTitle = $newTag
    if ($ghArgs.Count -ge 4) {
        $ghArgs[0] = $newTag
        $ghArgs[3] = $newTitle
    }

    # Validate the notes markers and extract the notes content.
    if ($notesStartIdx -lt 0 -or $notesEndIdx -lt 0 -or $notesEndIdx -le $notesStartIdx) {
        throw "The notes file must contain '--Notes begin--' and '--Notes end--' markers in the correct order."
    }
    if ($notesEndIdx - $notesStartIdx -le 1) {
        throw "No release notes found between '--Notes begin--' and '--Notes end--'. Please insert your notes."
    }
    $notesLines = $lines[($notesStartIdx + 1)..($notesEndIdx - 1)]
    # Join the extracted note lines using a single LF. We deliberately use
    # LF here rather than the original delimiter because GitHub CLI accepts
    # LF within notes content.
    $notesContent = ($notesLines -join "`n").Trim()
    if ([string]::IsNullOrWhiteSpace($notesContent)) {
        throw "No release notes found between '--Notes begin--' and '--Notes end--'. Please insert your notes."
    }
    # Append notes and enable generation of the rest of the notes including the full changelog.
    $ghArgs += @("--notes", $notesContent)
    $ghArgs += "--generate-notes"
    if ($previousTag) { $ghArgs += @("--notes-start-tag", $previousTag) }

    # Remove both the title and notes content from the file, leaving markers and other
    # surrounding text intact.  Skip lines strictly between the markers for both sections.
    $newLines = @()
    for ($i = 0; $i -lt $lines.Length; $i++) {
        # Skip lines that are inside the title section (exclusive of markers)
        if ($i -gt $titleStartIdx -and $i -lt $titleEndIdx) {
            continue
        }
        # Skip lines that are inside the notes section (exclusive of markers)
        if ($i -gt $notesStartIdx -and $i -lt $notesEndIdx) {
            continue
        }
        $newLines += $lines[$i]
    }
    # Build the new content string using the original delimiter to preserve
    # line endings. If nothing was removed, skip rewriting the file. This
    # avoids modifying the file when no changes were needed.
    if ($newLines.Length -ne $lines.Length) {
        # Reconstruct the file content using the original delimiter.  Preserve
        # whether the original file ended with a newline by checking if the
        # raw content ends with the delimiter.  When writing a single
        # string via Set-Content, use -NoNewline to avoid PowerShell
        # appending its own newline automatically.
        $endsWithDelimiter = $fileContent.EndsWith($delimiter)
        # Join the remaining lines using the original delimiter. When the
        # original file ends with a delimiter, the split array will include
        # a trailing empty string. Joining will reproduce the trailing
        # delimiter automatically. Only append an extra delimiter when the
        # original ended with a delimiter and the last element is not empty.
        $newContent = $newLines -join $delimiter
        if ($endsWithDelimiter -and $newLines.Count -gt 0 -and $newLines[-1] -ne "") {
            $newContent += $delimiter
        }
        Set-Content -LiteralPath $notesPath -Value $newContent -Encoding UTF8 -NoNewline
    }
} else {
    # If no notes file is provided, fall back to auto-generated notes and any suffix
    # defined in the JSON config.  The suffix value remains unchanged.
    $ghArgs += "--generate-notes"
    if ($previousTag) { $ghArgs += @("--notes-start-tag", $previousTag) }
}

# Apply prerelease and draft flags.
if ($isPrerelease) { $ghArgs += "--prerelease" }
if ($isDraft) { $ghArgs += "--draft" }

# Create the release via GitHub CLI.
Write-Host "Creating release $newTag with asset $ExePath ..."
gh release create @ghArgs
Write-Host "Release created successfully."