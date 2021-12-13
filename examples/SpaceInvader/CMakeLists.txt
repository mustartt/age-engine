cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)

add_library(space_invader
        SpaceInvader.h
        SpaceInvader.cpp
        components/SpaceInvaderComponentSystem.h
        scenes/MainScene.h
        scenes/MainScene.cpp
        components/Health.h
        components/OutOfBound.cpp
        components/OutOfBound.h
        components/Player.cpp
        components/Player.h
        scenes/GameOverScene.cpp
        scenes/GameOverScene.h
        components/MeteorSpawn.cpp
        components/MeteorSpawn.h
        scenes/GameStartScene.cpp
        scenes/GameStartScene.h
        components/PlayerScore.cpp
        components/PlayerScore.h
        events/ScoreEvent.h
        events/MeteorPastBorder.h main.cpp)

target_include_directories(space_invader PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(space_invader PROPERTIES LINKER_LANGUAGE CXX)
