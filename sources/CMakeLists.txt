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

target_link_libraries(${TARGET} PUBLIC sokol stb)

# explicitly strip dead code
if (CMAKE_C_COMPILER_ID MATCHES "Clang" AND EMSCRIPTEN EQUAL 0)
    target_link_options(${TARGET} PRIVATE LINKER:-dead_strip)
endif()

message(STATUS "SYSTEM ${CMAKE_SYSTEM_NAME}")
# Emscripten-specific linker options
if (EMSCRIPTEN EQUAL 1)
    message(STATUS "Configuration Emscripten")
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    target_link_options(${TARGET} PRIVATE -sEXPORTED_FUNCTIONS=_main)
    # File system support: https://emscripten.org/docs/api_reference/Filesystem-API.html#including-file-system-support
    target_link_options(${TARGET} PRIVATE -sWASMFS -sFORCE_FILESYSTEM -sEXPORTED_RUNTIME_METHODS=['FS'] -sALLOW_MEMORY_GROWTH)
    # use our own minimal shell.html
    target_link_options(${TARGET} PRIVATE --shell-file ${CMAKE_CURRENT_SOURCE_DIR}/html/shell.html)
    # link with WebGL2
    target_link_options(${TARGET} PRIVATE -sUSE_WEBGL2=1)
    # WASM+JS size optimizations
    target_link_options(${TARGET} PRIVATE -sASSERTIONS=0 -sMALLOC=emmalloc --closure=1)


    if(CMAKE_SYSTEM_NAME STREQUAL Darwin)
        message(STATUS "Darwin Linking System Libs")
        target_compile_options(${TARGET} PRIVATE -x objective-c)
        target_link_libraries(${TARGET} PUBLIC
            "-framework QuartzCore"
            "-framework Cocoa"
            "-framework MetalKit"
         "-framework Metal")
    elif(CMAKE_SYSTEM_NAME STREQUAL Windows)
    elif(CMAKE_SYSTEM_NAME STREQUAL Linux)
        message(STATUS "Linux Linking System Libs")
        target_link_libraries(${TARGET} INTERFACE X11 Xi Xcursor GL dl m)
        target_link_libraries(${TARGET} PUBLIC Threads::Threads)
    endif()
else()
    if(CMAKE_SYSTEM_NAME STREQUAL Darwin)
        target_compile_options(${TARGET} PRIVATE -x objective-c)
        target_link_libraries(${TARGET} PUBLIC
            "-framework QuartzCore"
            "-framework Cocoa"
            "-framework MetalKit"
            "-framework Metal")
    elif(CMAKE_SYSTEM_NAME STREQUAL Windows)
    elif (CMAKE_SYSTEM_NAME STREQUAL Linux) 
        message(STATUS "Linux Linking System Libs")
        target_link_libraries(${TARGET} INTERFACE X11 Xi Xcursor GL dl m)
        target_link_libraries(${TARGET} PUBLIC Threads::Threads)
    endif()
endif()

