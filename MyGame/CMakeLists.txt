cmake_minimum_required(VERSION 3.13)
project(MyGame)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "/usr/share/SFML/cmake/Modules")

add_executable(MyGame player/player.h map/map.h view/view.h mission.h entity.h player/Enemy.h level.h
        TinyXML/tinystr.cpp TinyXML/tinyxml.cpp TinyXML/tinyxmlerror.cpp TinyXML/tinyxmlparser.cpp
        game/game.cpp game/game.h game/game_manager.h)

find_package(SFML 2.4.1 COMPONENTS network graphics audio window system REQUIRED)
target_link_libraries(MyGame sfml-graphics sfml-audio sfml-window sfml-system)