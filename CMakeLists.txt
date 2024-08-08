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

if (MSVC)
    # warning level 4
    add_compile_options(/W4)
else()
    # additional warnings
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

check_subdirectories("src" HAS_SUBDIR)

file(GLOB_RECURSE SOURCES "src/*.cpp" "src/**/*.cpp")
message("files: " ${SOURCES})

# SDL config

set(SDL2_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")
set(SDL2_LIBRARY_DIR "${CMAKE_SOURCE_DIR}/lib/SDL/x64")
set(SDL2image_LIBRARY_DIR "${CMAKE_SOURCE_DIR}/lib/SDL2image/x64")

file(GLOB_RECURSE include_dirs "include/**/*.h")

include_directories(include ${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIBRARY_DIR} ${SDL2image_LIBRARY_DIR})

add_executable(${PROJECT_NAME} ${SOURCES})

#debug configuration
#set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DTEMPORAL_DEBUGGER")

target_link_libraries(${PROJECT_NAME} SDL2 SDL2_image)