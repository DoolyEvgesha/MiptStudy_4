#ifndef MYGAME_MAP_H
#define MYGAME_MAP_H

#include <SFML/System/String.hpp>
#include <SFML/Graphics.hpp>
#include "../entity.h"

const int HEIGHT_MAP        = 25;
const int WIDTH_MAP         = 60;
const int TILE_SIZE         = 32; //define it later!

static sf::String TileMap[HEIGHT_MAP] = { //?????????? how to replace the loot?
        "000000000000000000000000000000000000000000000000000000000000",
        "0                                                          0",
        "0                                f                         0",
        "0       f                                                  0",
        "0                    f                     f               0",
        "0                                                          0",
        "0                                                          0",
        "0              s                                           0",
        "0                              f                           0",
        "0                                                          0",
        "0                                           f              0",
        "0                                                          0",
        "0                                                          0",
        "0     f               sf                                   0",
        "0                                                          0",
        "0                                                          0",
        "0                                 fss                      0",
        "0    ssh                                        f          0",
        "0              ss   0000                                   0",
        "0           000000000000                                   0",
        "0   f    h  000000000000 h                                 0",
        "0          000000000000000    0                            0",
        "000000000000000000000000000000000000000000000000000000000000",
        "000000000000000000000000000000000000000000000000000000000000"
};

class Map : public Entity{
public:
    Map(const sf::String TileMap[], int map_height, int map_width, int tile_size,
        const sf::Texture *move_animation_texture);

    int     update      (float time, const sf::Event &event)    override;
    void    draw        (sf::RenderWindow &window)              override;
    int     getDirection(const sf::Event &event)                override;
    int     collide     (Entity *entity)                        override;

    int     getWidth()      { return width_;    };
    int     getHeight()     { return height_;   };
    int     getTileSize()   { return tileSize_; };
    float   getDirX()       { return 0;}
private:
    const sf::String *  tiledMap_;
    int                 tileSize_;
};

int     Map::update         (float time, const sf::Event &event)    { changeFrame(time); return 0; }
int     Map::getDirection   (const sf::Event &event)                { return 0; }
int     Map::collide        (Entity *entity)                        { return 0; }

void Map::draw(sf::RenderWindow &window)
{
    for(int i = 0; i < width_; i++)
        for(int j = 0; j < height_; j++)
        {
            sprite_.setTextureRect(sf::IntRect(/*i * tileSize_*/ 0, /*j * tileSize_*/ 0, tileSize_, tileSize_));
            //sprite_.setPosition(i * tileSize_, j * tileSize_);
            sprite_.setPosition(i * tileSize_, j * tileSize_);
            window.draw(sprite_);

            switch(tiledMap_[j][i])
            {
                case ' ':
                    sprite_.setTextureRect(sf::IntRect(0, 0, TILE_SIZE, TILE_SIZE));
                    break;
                //TODO: write stones, hearts etc on the map
                case 's': //stone
                    sprite_.setTextureRect(sf::IntRect(TILE_SIZE, 0, TILE_SIZE, TILE_SIZE));
                    break;
                case 'f': //flower
                    sprite_.setTextureRect(sf::IntRect(TILE_SIZE * 3, 0, TILE_SIZE, TILE_SIZE));
                    break;
                case 'h': //heart
                    sprite_.setTextureRect(sf::IntRect(TILE_SIZE * 4, 0, TILE_SIZE, TILE_SIZE));
                    break;
                case 't': //tree
                    //
                    break;
                case 'g': //
                    //
                    break;
                case '0': //boundaries
                    sprite_.setTextureRect(sf::IntRect(TILE_SIZE * 2, 0, TILE_SIZE, TILE_SIZE));
                    break;

                default:
                    break;
            }
            window.draw(sprite_);
            //window.display();
        }
}

Map::Map(const sf::String *TileMap, int map_height, int map_width, int tile_size,
         const sf::Texture *move_animation_texture) :
     Entity(0, 0, map_width, map_height, 0, 0.005, move_animation_texture, 2, MAP, 0),
     tiledMap_  (TileMap),
     tileSize_  (tile_size)
{}
/*
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
*/
#endif //MYGAME_MAP_H
