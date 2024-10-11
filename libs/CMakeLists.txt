
#=== LIBRARY: imgui + Dear ImGui
add_library(imgui STATIC 
    imgui/imgui.cpp
    imgui/imgui.h
    imgui/imgui.cpp
    imgui/imgui.h
    imgui/imgui_widgets.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_tables.cpp
    imgui/imgui_demo.cpp)
target_include_directories(imgui PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/imgui)


#=== LIBRARY: imgui + Dear ImGui
add_library(stb STATIC 
    stb/stb_image.h 
    stb_config/stb_image.cpp)
target_include_directories(stb PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/stb)

#=== LIBRARY: box2d
add_subdirectory(box2d)

#=== LIBRARY: sokol
# add headers to the the file list because they are useful to have in IDEs
set(SOKOL_HEADERS 
    sokol/sokol_gfx.h 
    sokol/sokol_app.h 
    sokol/util/sokol_imgui.h 
    sokol/sokol_glue.h)
    if(CMAKE_SYSTEM_NAME STREQUAL Darwin)
    add_library(sokol STATIC sokol_config/sokol.cpp  ${SOKOL_HEADERS})
    target_compile_options(sokol PRIVATE -x objective-c)
    target_link_libraries(sokol PUBLIC
    "-framework QuartzCore"
    "-framework Cocoa"
    "-framework MetalKit"
    "-framework Metal")
    else()
    add_library(sokol STATIC sokol_config/sokol.cpp ${SOKOL_HEADERS})
    if (CMAKE_SYSTEM_NAME STREQUAL Linux)
    target_link_libraries(sokol INTERFACE X11 Xi Xcursor GL dl m)
    target_link_libraries(sokol PUBLIC Threads::Threads)
    endif()
endif()

target_link_libraries(sokol PUBLIC imgui)
target_include_directories(sokol PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/sokol ${CMAKE_CURRENT_SOURCE_DIR}/imgui)


# Jolt Library
add_subdirectory(jolt/Build)






