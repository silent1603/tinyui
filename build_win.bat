@echo off

if exist ./builds/window (
   echo has builds folder
) else (
  mkdir builds\window
)

cmake -G "Visual Studio 17 2022" -B ./builds/window  