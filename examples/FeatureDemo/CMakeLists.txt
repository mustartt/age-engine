cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)

add_library(age_demo
        FeatureDemo.cpp
        FeatureDemo.h
        scenes/IntroScene.cpp
        scenes/IntroScene.h
        scenes/MovementScene.cpp
        scenes/MovementScene.h
        components/Movement.cpp
        components/Movement.h)

target_include_directories(age_demo PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(age_demo PROPERTIES LINKER_LANGUAGE CXX)
