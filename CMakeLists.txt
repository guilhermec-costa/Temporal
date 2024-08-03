cmake_minimum_required(VERSION 3.30.1) 
project(RPG2D) 

set(CMAKE_CXX_STANDARD 17)

function(check_subdirectories dir out)
    file(GLOB subdirs RELATIVE "${dir}" "${dir}/*")

    message(STATUS "Items found in ${dir}: ${subdirs}")

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

message(STATUS "HAS_SUBDIR: ${HAS_SUBDIR}")

include_directories(include)

if(HAS_SUBDIR)
    file(GLOB_RECURSE SOURCES "src/**/*.cpp")
else()
    file(GLOB SOURCES "src/*.cpp")
endif()

message(STATUS "Source files: ${SOURCES}")

add_executable(${PROJECT_NAME} ${SOURCES})
