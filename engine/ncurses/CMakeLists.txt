cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)

add_library(age_curses
        CursesContextManager.h
        CursesContextManager.cpp
        CursesKeyboard.h
        CursesKeyboard.cpp
        CursesRenderAdapter.h
        CursesRenderAdapter.cpp
        CursesRenderer.h
        CursesRenderer.cpp)

target_include_directories(age_curses PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(age_curses PROPERTIES LINKER_LANGUAGE CXX)
