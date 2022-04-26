#!/usr/bin/env bash
set -euo pipefail

# Version 1.2

EMSDK_PATH="../emsdk"
L_RAYLIB_SRC_PATH="../raylib/src"

L_PROJECT_NAME="craypong"
L_PROJECT_PATH="$(pwd)"
L_ARCHIVE_NAME="${L_PROJECT_NAME}_web"
L_BUILD_DIR="build/${L_ARCHIVE_NAME}"

# Get emsdk env variables
source "${EMSDK_PATH}/emsdk_env.sh"

# Build raylib for web
cd "${L_RAYLIB_SRC_PATH}"
make clean
make PLATFORM=PLATFORM_WEB --always-make --environment-overrides --jobs

# Build project
cd "${L_PROJECT_PATH}"
make clean
make PLATFORM=PLATFORM_WEB BUILD_MODE=RELEASE --always-make --environment-overrides --jobs

# Recreate build dir
rm --force --verbose --recursive --preserve-root "${L_BUILD_DIR}"
mkdir --parent --verbose "${L_BUILD_DIR}"

# Move build files to build dir
mv --verbose ${L_PROJECT_NAME}.data ${L_PROJECT_NAME}.wasm ${L_PROJECT_NAME}.js "${L_BUILD_DIR}"
mv --verbose ${L_PROJECT_NAME}.html "${L_BUILD_DIR}/index.html"

# Create build zip
cd build
rm --force --verbose "${L_ARCHIVE_NAME}.zip"
zip -r "${L_ARCHIVE_NAME}.zip" "${L_ARCHIVE_NAME}"