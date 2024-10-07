#!/bin/bash
source ./tools/emsdk/emsdk_env.sh
if [ -d ./builds/linux_wasm ]; then
  echo "Directory exists."
else
    mkdir -p ./builds/linux_wasm
fi
cmake -DCMAKE_TOOLCHAIN_FILE=./tools/emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake -B ./builds/linux_wasm

