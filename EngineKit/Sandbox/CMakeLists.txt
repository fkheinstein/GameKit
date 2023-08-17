cmake_minimum_required(VERSION 3.14 FATAL_ERROR)


get_filename_component(PROJ_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" PROJ_NAME ${PROJ_NAME})

project(${PROJ_NAME} LANGUAGES C CXX)



set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


if (MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()


include_directories(${Engine_DIR})
include_directories(${INCLUDE_OUTPUT_PATH})


link_directories(${LIBRARY_OUTPUT_PATH})



file(GLOB_RECURSE SRC_FILES
    "Src/*.h"
    "Src/*.cpp"
    "Src/*.rc")

add_executable(${PROJ_NAME}  main.cpp ${SRC_FILES}  )

target_link_libraries(${PROJ_NAME} 
        PRIVATE  
        EngineLib )