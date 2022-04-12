#!/usr/bin/env bash
set -euo pipefail

# Version 1.1

EMSDK_PATH="../emsdk"
RAYLIB_SRC_PATH="../raylib/src"

PROJECT_NAME="craypong"
PROJECT_PATH="$(pwd)"
ARCHIVE_NAME="${PROJECT_NAME}_web"
BUILD_DIR="build/${ARCHIVE_NAME}"

# Get emsdk env variables
source "${EMSDK_PATH}/emsdk_env.sh"

# Build raylib for web
cd "${RAYLIB_SRC_PATH}"
make clean
make PLATFORM=PLATFORM_WEB --always-make --environment-overrides --jobs

# Build project
cd "${PROJECT_PATH}"
make clean
make PLATFORM=PLATFORM_WEB BUILD_MODE=RELEASE --always-make --environment-overrides --jobs

# Recreate build dir
rm --force --verbose --recursive --preserve-root "${BUILD_DIR}"
mkdir --parent --verbose "${BUILD_DIR}"

# Move build files to build dir
mv --verbose ${PROJECT_NAME}.data ${PROJECT_NAME}.wasm ${PROJECT_NAME}.js "${BUILD_DIR}"
mv --verbose ${PROJECT_NAME}.html "${BUILD_DIR}/index.html"

# Create build zip
cd build
rm --force --verbose "${ARCHIVE_NAME}.zip"
zip -r "${ARCHIVE_NAME}.zip" "${ARCHIVE_NAME}"