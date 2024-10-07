set(TARGET tinyui)

#=== EXECUTABLE: ${TARGET}
if(CMAKE_SYSTEM_NAME STREQUAL Windows)
    add_executable(${TARGET} WIN32)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${TARGET})
else()
    add_executable(${TARGET})
endif()

target_sources(${TARGET} PUBLIC cpp/main.cpp)

target_include_directories(${TARGET} PUBLIC 
    ${CMAKE_SOURCE_DIR}/libs/imgui
    ${CMAKE_SOURCE_DIR}/libs/imgui/backends
    ${CMAKE_SOURCE_DIR}/libs/sokol 
    ${CMAKE_SOURCE_DIR}/libs/stb)

# Emscripten-specific linker options
if (CMAKE_SYSTEM_NAME STREQUAL Emscripten)
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    target_link_options(imzip PRIVATE -sEXPORTED_FUNCTIONS=_main)
    # File system support: https://emscripten.org/docs/api_reference/Filesystem-API.html#including-file-system-support
    target_link_options(imzip PRIVATE -sWASMFS -sFORCE_FILESYSTEM -sEXPORTED_RUNTIME_METHODS=['FS'] -sALLOW_MEMORY_GROWTH)
    # use our own minimal shell.html
    target_link_options(${TARGET} PRIVATE --shell-file ${CMAKE_CURRENT_SOURCE_DIR}/html/shell.html)
    # link with WebGL2
    target_link_options(${TARGET} PRIVATE -sUSE_WEBGL2=1)
    # WASM+JS size optimizations
    target_link_options(${TARGET} PRIVATE -sNO_FILESYSTEM=1 -sASSERTIONS=0 -sMALLOC=emmalloc --closure=1)
endif()

# explicitly strip dead code
if (CMAKE_C_COMPILER_ID MATCHES "Clang" AND NOT CMAKE_SYSTEM_NAME STREQUAL Emscripten)
    target_link_options(${TARGET} PRIVATE LINKER:-dead_strip)
endif()

if(CMAKE_SYSTEM_NAME STREQUAL Darwin)
    target_compile_options(${TARGET} PRIVATE -x objective-c)
    target_link_libraries(${TARGET} PUBLIC
        "-framework QuartzCore"
        "-framework Cocoa"
        "-framework MetalKit"
        "-framework Metal")
else()
    if (CMAKE_SYSTEM_NAME STREQUAL Linux)
        target_link_libraries(${TARGET} INTERFACE X11 Xi Xcursor GL dl m)
        target_link_libraries(${TARGET} PUBLIC Threads::Threads)
    endif()
endif()
