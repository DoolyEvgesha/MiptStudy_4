#ifndef MYGAME_MAP_H
#define MYGAME_MAP_H

#include <SFML/System/String.hpp>

const int HEIGHT_MAP        = 25;
const int WIDTH_MAP         = 40;
const int TILE_SIZE         = 0; //define it later!

sf::String TileMap[HEIGHT_MAP] = {
        "0000000000000000000000000000000000000000",
        "0                                      0",
        "0   s                                  0",
        "0                                      0",
        "0                                      0",
        "0                                      0",
        "0                                      0",
        "0                                      0",
        "0                                      0",
        "0                                      0",
        "0                                      0",
        "0                                      0",
        "0                                      0",
        "0                                      0",
        "0                                      0",
        "0                                      0",
        "0                                      0",
        "0                                      0",
        "0                                      0",
        "0                                      0",
        "0                                      0",
        "0                                      0",
        "0                                      0",
        "0                                      0",
        "0000000000000000000000000000000000000000",
};

class Map{
    Map();
    ~Map();
};

Map::Map() {}

Map::~Map() {}

#endif //MYGAME_MAP_H
