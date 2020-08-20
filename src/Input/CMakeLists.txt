target_sources(
    input 
    PRIVATE
    Joypad_Controller.cpp
    Keyboard.cpp
)
target_link_libraries(input PRIVATE project_warnings)