@echo off

if exist ./builds/win_wasm (
   echo has builds folder
) else (
  mkdir builds\win_wasm
)

emmake cmake -DCMAKE_TOOLCHAIN_FILE=%cd%/tools/emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake  -G "Ninja" -B ./builds/win_wasm