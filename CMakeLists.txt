cmake_minimum_required(VERSION 3.16)
project(final_project)

set(CMAKE_CXX_STANDARD 14)

include_directories(lib)
link_libraries(ncurses)

add_executable(final_project main.cpp CursesRenderer.cpp CursesRenderer.h CursesContextManager.cpp CursesContextManager.h engine/renderer/ScreenBuffer.cpp engine/renderer/ScreenBuffer.h engine/renderer/Renderer.cpp engine/renderer/Renderer.h engine/renderer/RenderTarget.h engine/ecs/Entity.h engine/ecs/ecs.h engine/ecs/Component.h engine/ecs/System.h)
