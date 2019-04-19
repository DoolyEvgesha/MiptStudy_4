#ifndef MYGAME_MAP_H
#define MYGAME_MAP_H

#include <SFML/System/String.hpp>
#include "../entity.h"

const int HEIGHT_MAP        = 25;
const int WIDTH_MAP         = 40;
const int TILE_SIZE         = 72; //define it later!

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

class Map : public Entity{
public:
    Map(const sf::String TileMap[], int map_height, int map_width, int tile_size,
        const sf::Texture *move_animation_texture);

    void    update      (float time, const sf::Event &event)    override;
    void    draw        (sf::RenderWindow &window)              override;
    int     getDirection(const sf::Event &event)                override;
    int     collide     (Entity *entity)                        override;

    int     getWidth()      { return width_;    };
    int     getHeight()     { return height_;   };
    int     getTileSize()   { return tileSize_; };
private:
    const sf::String *  tiledMap_;
    int                 tileSize_;
};

void Map::update(float time, const sf::Event &event) { changeFrame(time); }
int Map::getDirection(const sf::Event &event) { return 0; }
int Map::collide(Entity *entity) { return 0; }

void Map::draw(sf::RenderWindow &window)
{
    for(int i = 0; i < width_; i++)
        for(int j = 0; i < height_; j++)
        {
            sprite_.setTextureRect(sf::IntRect(8 * tileSize_, 12 * tileSize_, tileSize_, tileSize_));
            sprite_.setPosition(i * tileSize_, j * tileSize_);
            window.draw(sprite_);

            switch(tiledMap_[i][j])
            {
                //TODO: write stones, hearts etc on the map
                case 's':
                    //sprite_.setTextureRect();
                    break;
                //...
                //...
                default:
                    break;
            }
            window.draw(sprite_);
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
