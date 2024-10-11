
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

#=== LIBRARY: SDL3
set(SDL_EXAMPLES OFF)
set(SDL_TESTS OFF)
add_subdirectory(SDL3)

#=== LIBRARY: Jolt 
add_subdirectory(jolt/Build)






