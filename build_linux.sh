#!/bin/sh
if [ -d /builds/linux ]; then
  echo "Directory exists."
else
    mkdir -p /builds/linux
fi
cmake -G Ninja -B ./builds/linux