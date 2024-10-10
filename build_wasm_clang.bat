@echo off

if exist ./builds/MinGW_wasm (
   echo has builds folder
) else (
  mkdir builds\MinGW_wasm
)

emmake cmake -DCMAKE_TOOLCHAIN_FILE=%cd%/tools/emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake  -G "Visual Studio 17 2022" -T ClangCL -B ./builds/wasm