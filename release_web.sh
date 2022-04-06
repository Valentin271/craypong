#!/usr/bin/env bash
set -euo pipefail

EMSDK_PATH="../emsdk"
RAYLIB_SRC_PATH="../raylib/src"

PROJECT_PATH="$(pwd)"
BUILD_DIR="build/craypong_web"

# Get emsdk env variables
source "${EMSDK_PATH}/emsdk_env.sh"

# Build raylib for web
cd "${RAYLIB_SRC_PATH}"
make clean
make PLATFORM=PLATFORM_WEB --always-make --environment-overrides --jobs

# Build project
cd "${PROJECT_PATH}"
make clean
make PLATFORM=PLATFORM_WEB --always-make --environment-overrides --jobs

# Recreate build dir
rm --force --verbose --recursive --preserve-root "${BUILD_DIR}"
mkdir --parent --verbose "${BUILD_DIR}"

# Move build files to build dir
mv --verbose craypong.data craypong.wasm craypong.js "${BUILD_DIR}"
mv --verbose craypong.html "${BUILD_DIR}/index.html"

# Create build zip
rm --force --verbose "${BUILD_DIR}.zip"
zip -r "${BUILD_DIR}.zip" "${BUILD_DIR}"