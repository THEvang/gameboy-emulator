target_sources(gui
    PRIVATE
    
    Gui.cpp
)

target_compile_options(gui PRIVATE -Wall)
target_link_libraries(gui PRIVATE project_warnings)