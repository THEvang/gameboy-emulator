option(ENABLE_CLANG_TIDY "Enables Clang Tidy" OFF)
option(ENABLE_CPP_CHECK "Enables CPPCheck" OFF)

if(ENABLE_CLANG_TIDY)
    find_program(CLANGTIDY clang-tidy)
    if(CLANGTIDY)
        set(CMAKE_CXX_CLANG_TIDY ${CLANGTIDY} -extra-arg=-Wno-unknown-warning-option)
    else() 
        message(SEND_ERROR "clang-tidy requested, but executable not found")
    endif()
endif()

if(ENABLE_CPP_CHECK)
    find_program(CPPCHECK cppcheck)
    if(CPPCHECK)
            set(CMAKE_CXX_CPPCHECK ${CPPCHECK}  --suppress=missingInclude --enable=all
            --inconclusive -i ${CMAKE_SOURCE_DIR}/src/imgui)
        else()
            message(SEND_ERROR "cppcheck requested, but executable not found")
        endif()
endif()