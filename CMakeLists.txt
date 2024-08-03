cmake_minimum_required(VERSION 3.30.1) 
project(RPG2D) 
set(CMAKE_CXX_STANDARD 17)

function(check_subdirectories dir out)
    file(GLOB subdirs RELATIVE "${dir}" "${dir}/*")

    foreach(subdir ${subdirs})
        message(STATUS "Checking: ${dir}/${subdir}")
        if(IS_DIRECTORY "${dir}/${subdir}")
            set(${out} TRUE PARENT_SCOPE)
            return() 
        endif()
    endforeach()
    
    set(${out} FALSE PARENT_SCOPE)
endfunction()

check_subdirectories("src" HAS_SUBDIR)

# if(HAS_SUBDIR)
    # file(GLOB_RECURSE SOURCES "src/**/*.cpp")
# else()
    file(GLOB SOURCES "src/*.cpp" "main.cpp")
# endif()

# SDL config

set(SDL2_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")
set(SDL2_LIBRARY_DIR "${CMAKE_SOURCE_DIR}/lib/SDL/x64")
message(STATUS ${SDL2_LIBRARY_DIR})

include_directories(include ${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIBRARY_DIR})

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} SDL2 MINGW32)