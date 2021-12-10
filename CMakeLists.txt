cmake_minimum_required(VERSION 3.16)
project(final_project)

set(CMAKE_CXX_STANDARD 20)

include_directories(lib)
include_directories(engine)

link_libraries(ncurses)

add_compile_definitions(COMPILE_AS_ENGINE)

add_subdirectory(engine/ecs)
add_subdirectory(engine/events)

add_executable(final_project main.cpp
        engine/components/EngineComponents.h
        engine/ncurses/CursesRenderer.cpp
        engine/ncurses/CursesRenderer.h
        engine/ncurses/CursesContextManager.cpp
        engine/ncurses/CursesContextManager.h
        engine/renderer/ScreenBuffer.cpp
        engine/renderer/ScreenBuffer.h
        engine/renderer/AsciiRenderer.cpp
        engine/renderer/AsciiRenderer.h
        engine/renderer/RenderTarget.h
        engine/age.h
        engine/renderer/RenderComponents/AsciiRenderProp.h
        engine/renderer/RenderComponents/impl/CharacterProp.h
        engine/renderer/RenderComponents/impl/RectProp.h
        engine/renderer/RenderComponents/impl/BitMapProp.h
        engine/utils/vec2.h
        engine/ncurses/CursesKeyboard.cpp
        engine/ncurses/CursesKeyboard.h
        engine/entry/EntryPoint.cpp
        engine/entry/EntryPoint.h
        engine/ncurses/CursesRenderAdapter.cpp
        engine/ncurses/CursesRenderAdapter.h
        engine/ncurses/curseswrapper.h
        engine/Scene.h
        engine/ecs/EntityManager.h
        engine/components/EngineSystems.h
        examples/SpaceInvader/scenes/MainScene.cpp
        examples/SpaceInvader/scenes/MainScene.h
        examples/SpaceInvader/SpaceInvader.cpp
        examples/SpaceInvader/SpaceInvader.h
        examples/SpaceInvader/components/SpaceInvaderComponentSystem.h
        engine/components/BasicCollision.h)

target_link_libraries(final_project LINK_PUBLIC age_ecs)
target_link_libraries(final_project LINK_PUBLIC age_events)
