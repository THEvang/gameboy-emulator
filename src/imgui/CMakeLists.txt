set(CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED ON)

add_library(ImgGui imgui_demo.cpp imgui_draw.cpp imgui_widgets.cpp imgui.cpp imgui_impl_sdl.cpp imgui_impl_opengl3.cpp)
target_include_directories(ImgGui PUBLIC ${CMAKE_SOURCE_DIR}/include/imgui)