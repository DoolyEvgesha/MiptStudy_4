#ifndef MYGAME_MAP_H
#define MYGAME_MAP_H

#include <SFML/System/String.hpp>
#include "../entity.h"

const int HEIGHT_MAP        = 25;
const int WIDTH_MAP         = 40;
const int TILE_SIZE         = 0; //define it later!

static sf::String TileMap[HEIGHT_MAP] = { //?????????? how to replace the loot?
        "0000000000000000000000000000000000000000",
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
        "0    ssh                               0",
        "0    0000                              0",
        "0                                      0",
        "0              ss   0000               0",
        "0           000000000000               0",
        "0           000000000000               0",
        "0   f    h  000000000000 h             0",
        "0000000000000000000000000000000000000000",
};

class Map:public Entity{
public:
private:
    //std::vector<sf::Vector2f> fires;
};

static void randomMapGenerate()
{
    int randomElementX = 0;
    int randomElementY = 0;
    srand(time(0));
    int countStone = 1;

    while(countStone > 0)
    {
        randomElementX = 1 +rand() % (WIDTH_MAP - 1);
        randomElementY = 1 +rand() % (HEIGHT_MAP -1);

        if(TileMap[randomElementY][randomElementX] == ' ')
        {
            TileMap[randomElementY][randomElementX] = 's';
            countStone--;
        }
    }
}

#endif //MYGAME_MAP_H
