#!/bin/bash

if [ -d ./builds/linux_wasm ]; then
  echo "Directory exists."
else
    mkdir -p ./builds/linux_wasm
fi
emmake cmake -G Ninja -B ./builds/linux_wasm

