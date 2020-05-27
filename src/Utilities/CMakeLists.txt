target_sources(utilities 
    PRIVATE
    File.cpp
)
target_link_libraries(utilities PRIVATE project_warnings "-lstdc++fs")
target_compile_features(utilities PRIVATE cxx_std_17)