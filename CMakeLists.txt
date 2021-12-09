cmake_minimum_required(VERSION 3.16)
project(final_project)

set(CMAKE_CXX_STANDARD 20)

include_directories(lib)
include_directories(engine)

link_libraries(ncurses)

# AddressSanitize
set(CMAKE_C_FLAGS_ASAN
        "-fsanitize=address -fno-optimize-sibling-calls -fsanitize-address-use-after-scope -fno-omit-frame-pointer -g -O1"
        CACHE STRING "Flags used by the C compiler during AddressSanitizer builds."
        FORCE)
set(CMAKE_CXX_FLAGS_ASAN
        "-fsanitize=address -fno-optimize-sibling-calls -fsanitize-address-use-after-scope -fno-omit-frame-pointer -g -O1"
        CACHE STRING "Flags used by the C++ compiler during AddressSanitizer builds."
        FORCE)

add_compile_definitions(COMPILE_AS_ENGINE)

add_executable(final_project main.cpp engine/components/EngineComponents.h engine/ncurses/CursesRenderer.cpp engine/ncurses/CursesRenderer.h engine/ncurses/CursesContextManager.cpp engine/ncurses/CursesContextManager.h engine/renderer/ScreenBuffer.cpp engine/renderer/ScreenBuffer.h engine/renderer/AsciiRenderer.cpp engine/renderer/AsciiRenderer.h engine/renderer/RenderTarget.h engine/ecs/Entity.h engine/ecs/ecs.h engine/ecs/ComponentManager.h engine/ecs/SystemManager.h engine/ecs/Registry.h engine/age.h engine/renderer/RenderComponents/AsciiRenderProp.h engine/renderer/RenderComponents/impl/CharacterProp.h engine/renderer/RenderComponents/impl/RectProp.h engine/renderer/RenderComponents/impl/BitMapProp.h engine/utils/vec2.h engine/ncurses/CursesKeyboard.cpp engine/ncurses/CursesKeyboard.h engine/events/Event.h engine/entry/EntryPoint.cpp engine/entry/EntryPoint.h engine/ncurses/CursesRenderAdapter.cpp engine/ncurses/CursesRenderAdapter.h engine/ncurses/curseswrapper.h engine/Scene.h engine/ecs/EntityManager.h engine/components/EngineSystems.h engine/events/engine_events/EngineEvent.h engine/SceneManager.h)
