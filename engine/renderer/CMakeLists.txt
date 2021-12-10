cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)

add_library(age_ascii_renderer
        AsciiRenderer.h
        AsciiRenderer.cpp
        RenderTarget.h
        ScreenBuffer.h
        ScreenBuffer.cpp
        RenderComponents/AsciiRenderProp.h
        RenderComponents/CharacterProp.h
        RenderComponents/RectProp.h
        RenderComponents/BitMapProp.h)

target_include_directories(age_ascii_renderer PUBLIC RenderComponents)
set_target_properties(age_ascii_renderer PROPERTIES LINKER_LANGUAGE CXX)
