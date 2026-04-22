$ErrorActionPreference = "Stop"

# Renode Workbench scaffold
# Fill in your actual toolchain, source files, linker script, and outputs.
# This script is intentionally minimal and will stop until you customize it.

$sessionRoot = Split-Path -Parent $PSScriptRoot
$buildDir = Join-Path $sessionRoot "build"

New-Item -ItemType Directory -Force $buildDir | Out-Null

throw "Update this session-local build.ps1 with your real build steps before using Renode Build."
