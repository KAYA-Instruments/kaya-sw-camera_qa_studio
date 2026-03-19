TEMPLATE = aux
TARGET   = publish_release

# Absolute (source-tree) path to the built executable
releaseExe = $$PWD/TESTDIR/kaya-sw-camera_qa_studio.exe

# Override the default 'all' target so building this project runs the PowerShell script
all.target = all
all.commands = powershell -NoProfile -ExecutionPolicy Bypass -File $$shell_path($$PWD/scripts/publish_release_studio.ps1) -ExePath $$shell_path($$releaseExe)

QMAKE_EXTRA_TARGETS += all

DISTFILES += \
    release/notes.md
