cmake_minimum_required(VERSION 3.13)
project(MyGame)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "/usr/share/SFML/cmake/Modules")

add_executable(MyGame main.cpp player/player.h map/map.h game/object.h game/object.cpp view/view.h)

find_package(SFML 2.4.1 COMPONENTS network graphics audio window system REQUIRED)
target_link_libraries(MyGame sfml-graphics sfml-audio sfml-window sfml-system)