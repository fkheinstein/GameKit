
get_filename_component(PROJ_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" PROJ_NAME ${PROJ_NAME})

project(${PROJ_NAME} C CXX)



#include_directories(.)