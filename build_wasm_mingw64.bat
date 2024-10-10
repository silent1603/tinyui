@echo off

if exist ./builds/MinGW_wasm (
   echo has builds folder
) else (
  mkdir builds\MinGW_wasm
)

emmake cmake -G "MinGW Makefiles" -DEMSCRIPTEN=1 -B ./builds/wasm