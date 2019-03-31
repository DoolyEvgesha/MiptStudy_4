#ifndef MYGAME_MAP_H
#define MYGAME_MAP_H

#include <SFML/System/String.hpp>

const int HEIGHT_MAP        = 25;
const int WIDTH_MAP         = 40;
const int TILE_SIZE         = 0; //define it later!

static sf::String TileMap[HEIGHT_MAP] = { //?????????? how to replace the loot?
        "0000000000000000000000000000000000000000",
        "0                                      0",
        "0   s                                  0",
        "0                  f                   0",
        "0                                      0",
        "0                              s       0",
        "0         h             s              0",
        "0                f                     0",
        "0     s          f                     0",
        "0                f                     0",
        "0                                      0",
        "0                                      0",
        "0             s                s       0",
        "0                                      0",
        "0                             h        0",
        "0                      s               0",
        "0                                      0",
        "0      f                               0",
        "0                       f              0",
        "0                                      0",
        "0            s                         0",
        "0                               h      0",
        "0                                      0",
        "0                     f                0",
        "0000000000000000000000000000000000000000",
};

static void randomMapGenerate()
{
    int randomElementX = 0;
    int randomElementY = 0;
    srand(time(0));
    int countStone = 2;

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
