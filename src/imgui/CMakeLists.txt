target_sources(
    imgui 
    PRIVATE
    imgui_demo.cpp 
    imgui_draw.cpp 
    imgui_widgets.cpp 
    imgui.cpp 
    imgui_impl_sdl.cpp 
    imgui_impl_opengl3.cpp
)

set_target_properties(imgui PROPERTIES CXX_CLANG_TIDY "")