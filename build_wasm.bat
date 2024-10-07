@echo off

if exist ./builds/wasm (
   echo has builds folder
) else (
  mkdir builds\wasm
)

emmake cmake -G Ninja -B ./builds/wasm