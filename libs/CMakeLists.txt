
#=== LIBRARY: imgui + Dear ImGui
set(imgui_source     
imgui/imgui.cpp
imgui/imgui.h
imgui/imgui.cpp
imgui/imgui.h
imgui/imgui_widgets.cpp
imgui/imgui_draw.cpp
imgui/imgui_tables.cpp
imgui/imgui_demo.cpp
imgui/backends/imgui_impl_sdl3.h
imgui/backends/imgui_impl_sdl3.cpp
imgui/backends/imgui_impl_sdlrenderer3.h
imgui/backends/imgui_impl_sdlrenderer3.cpp)

if (CMAKE_SYSTEM_NAME STREQUAL Emscripten)
    list(APPEND imgui_source     
    imgui/backends/imgui_impl_opengl3.h 
    imgui/backends/imgui_impl_opengl3.cpp 
    imgui/backends/imgui_impl_wgpu.h 
    imgui/backends/imgui_impl_wgpu.cpp)
else()

    if(CMAKE_SYSTEM_NAME STREQUAL Darwin)
        list(APPEND imgui_source 
            imgui/backends/imgui_impl_opengl3.h 
            imgui/backends/imgui_impl_opengl3.cpp      
            imgui/backends/imgui_impl_metal.h 
            imgui/backends/imgui_impl_metal.mm)
    elseif(CMAKE_SYSTEM_NAME STREQUAL Windows)
        list(APPEND imgui_source     
            imgui/backends/imgui_impl_opengl3.h 
            imgui/backends/imgui_impl_opengl3.cpp 
            imgui/backends/imgui_impl_dx11.h 
            imgui/backends/imgui_impl_dx11.cpp 
            imgui/backends/imgui_impl_dx12.h 
            imgui/backends/imgui_impl_dx12.cpp)
    elseif (CMAKE_SYSTEM_NAME STREQUAL Linux) 
        list(APPEND imgui_source     
            imgui/backends/imgui_impl_opengl3.h 
            imgui/backends/imgui_impl_opengl3.cpp
            imgui/backends/imgui_impl_vulkan.h 
            imgui/backends/imgui_impl_vulkan.cpp)
    endif()
endif()

add_library(imgui STATIC ${imgui_source})

target_include_directories(imgui PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/imgui 
                                        ${CMAKE_CURRENT_SOURCE_DIR}/SDL3/include )



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


#=== LIBRARY: glm
add_subdirectory(glm)



