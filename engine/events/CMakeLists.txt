cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)

add_library(age_events Event.h Event.cpp EngineEvents/EngineEvents.h)

target_include_directories(age_events PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(age_events PROPERTIES LINKER_LANGUAGE CXX)
