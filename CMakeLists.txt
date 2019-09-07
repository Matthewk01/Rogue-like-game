cmake_minimum_required(VERSION 3.14)
project(textRpg C)

set(CMAKE_C_STANDARD 11)

include_directories(textRpg/src)

add_executable(textRpg
        textRpg/src/character.c
        textRpg/src/character.h
        textRpg/src/game.c
        textRpg/src/game.h
        textRpg/src/main.c
        textRpg/src/map.c
        textRpg/src/map.h textRpg/src/monster.c textRpg/src/monster.h textRpg/src/inventory.c textRpg/src/inventory.h textRpg/src/logger.c textRpg/src/logger.h)
