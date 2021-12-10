cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)

add_library(age_ecs ecs.h EntityManager.h ComponentManager.h SystemManager.h Registry.h Entity.h)
target_include_directories(age_ecs PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(age_ecs PROPERTIES LINKER_LANGUAGE CXX)
