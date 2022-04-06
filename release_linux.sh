#!/usr/bin/env bash
set -euo pipefail

RAYLIB_SRC_PATH="../raylib/src"

PROJECT_PATH="$(pwd)"
BUILD_DIR="build/craypong_linux"

# Build raylib for desktop
cd "${RAYLIB_SRC_PATH}"
make clean
make PLATFORM=PLATFORM_DESKTOP --always-make --jobs

# Build project
cd "${PROJECT_PATH}"
make clean
make PLATFORM=PLATFORM_DESKTOP --always-make --jobs

# Recreate build dir
rm --force --verbose --recursive --preserve-root "${BUILD_DIR}"
mkdir --parent --verbose "${BUILD_DIR}"

# Move build files and resources to build dir
mv --verbose craypong "${BUILD_DIR}"
cp --verbose --recursive resources "${BUILD_DIR}"

# Create build zip
rm --force --verbose "${BUILD_DIR}.zip"
zip -r "${BUILD_DIR}.zip" "${BUILD_DIR}"