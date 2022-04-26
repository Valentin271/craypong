#!/usr/bin/env bash
set -euo pipefail

# Version 1.2

L_RAYLIB_SRC_PATH="../raylib/src"

L_PROJECT_NAME="craypong"
L_PROJECT_PATH="$(pwd)"
L_ARCHIVE_NAME="${L_PROJECT_NAME}_linux"
L_BUILD_DIR="build/${L_ARCHIVE_NAME}"

# Build raylib for desktop
cd "${L_RAYLIB_SRC_PATH}"
make clean
make PLATFORM=PLATFORM_DESKTOP --always-make --jobs

# Build project
cd "${L_PROJECT_PATH}"
make clean
make PLATFORM=PLATFORM_DESKTOP BUILD_MODE=RELEASE --always-make --jobs

# Recreate build dir
rm --force --verbose --recursive --preserve-root "${L_BUILD_DIR}"
mkdir --parent --verbose "${L_BUILD_DIR}"

# Move build files and resources to build dir
mv --verbose ${L_PROJECT_NAME} "${L_BUILD_DIR}"
cp --verbose --recursive resources "${L_BUILD_DIR}"

# Create build zip
cd build
rm --force --verbose "${L_ARCHIVE_NAME}.zip"
zip -r "${L_ARCHIVE_NAME}.zip" "${L_ARCHIVE_NAME}"