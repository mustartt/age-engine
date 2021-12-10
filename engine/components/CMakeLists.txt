cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)

add_library(age_components
        BasicCollision.h
        BasicCollision.cpp
        EntityTag.h
        EntityTag.cpp
        Transform.h
        AsciiRender.h
        AsciiRender.cpp)

target_include_directories(age_components PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(age_components PROPERTIES LINKER_LANGUAGE CXX)
