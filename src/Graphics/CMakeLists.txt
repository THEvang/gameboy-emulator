target_sources(graphics 
    PRIVATE
    LCD_Control.cpp
    LCD_Status.cpp
    PPU.cpp
    Pixel.cpp
)
target_link_libraries(graphics PRIVATE project_warnings)