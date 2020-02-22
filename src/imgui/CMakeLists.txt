set(CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED ON)

add_library(ImgGui imgui_demo.cpp imgui_draw.cpp imgui_widgets.cpp imgui.cpp)
target_include_directories(ImgGui PUBLIC ${CMAKE_SOURCE_DIR}/include/imgui)