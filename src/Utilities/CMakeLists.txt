target_sources(utilities 
    PRIVATE
    BitOperations.cpp 
    File.cpp
)
target_link_libraries(utilities PRIVATE project_warnings)