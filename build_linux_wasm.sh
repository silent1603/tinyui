#!/bin/bash

if [ -d ./builds/linux_wasm ]; then
  echo "Directory exists."
else
  sudo mkdir -p ./builds/linux_wasm
fi
emmake cmake -DCMAKE_TOOLCHAIN_FILE=$PWD/tools/emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake -G Ninja -B ./builds/linux_wasm

