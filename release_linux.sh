#!/usr/bin/env bash
set -euo pipefail

# Version 1.1

RAYLIB_SRC_PATH="../raylib/src"

PROJECT_NAME="craypong"
PROJECT_PATH="$(pwd)"
ARCHIVE_NAME="${PROJECT_NAME}_linux"
BUILD_DIR="build/${ARCHIVE_NAME}"

# Build raylib for desktop
cd "${RAYLIB_SRC_PATH}"
make clean
make PLATFORM=PLATFORM_DESKTOP --always-make --jobs

# Build project
cd "${PROJECT_PATH}"
make clean
make PLATFORM=PLATFORM_DESKTOP BUILD_MODE=RELEASE --always-make --jobs

# Recreate build dir
rm --force --verbose --recursive --preserve-root "${BUILD_DIR}"
mkdir --parent --verbose "${BUILD_DIR}"

# Move build files and resources to build dir
mv --verbose ${PROJECT_NAME} "${BUILD_DIR}"
cp --verbose --recursive resources "${BUILD_DIR}"

# Create build zip
cd build
rm --force --verbose "${ARCHIVE_NAME}.zip"
zip -r "${ARCHIVE_NAME}.zip" "${ARCHIVE_NAME}"