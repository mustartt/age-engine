cmake_minimum_required(VERSION 3.16)
project(final_project)

set(CMAKE_CXX_STANDARD 20)

include_directories(lib)
include_directories(engine)

link_libraries(ncurses)

add_compile_definitions(COMPILE_AS_ENGINE)

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")

# engine subdirectory
add_subdirectory(engine/ecs)
add_subdirectory(engine/events)
add_subdirectory(engine/ncurses)
add_subdirectory(engine/renderer)
add_subdirectory(engine/components)

# example subdirectory
add_subdirectory(examples/SpaceInvader)

add_executable(final_project main.cpp
        engine/age.h
        engine/utils/vec2.h
        engine/entry/EntryPoint.cpp
        engine/entry/EntryPoint.h
        engine/Scene.h
        engine/utils/BitMapLoader.cpp engine/utils/BitMapLoader.h)

# example static library
target_link_libraries(final_project LINK_PUBLIC space_invader)

# engine static library
target_link_libraries(final_project LINK_PUBLIC age_ecs)
target_link_libraries(final_project LINK_PUBLIC age_events)
target_link_libraries(final_project LINK_PUBLIC age_curses)
target_link_libraries(final_project LINK_PUBLIC age_ascii_renderer)
target_link_libraries(final_project LINK_PUBLIC age_components)
