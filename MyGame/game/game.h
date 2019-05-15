#ifndef MYGAME_GAME_H
#define MYGAME_GAME_H

#include <SFML/Graphics/Texture.hpp>

static sf::Texture *textures = nullptr;

const char playerImageFile[]    = "images/tailsPrower.png";
const char mapImageFile[]       = "images/my_map.png";
const char easyEnemyImageFile[] = "images/shamaich.png";

const int game_speed            = 1000;
const int enemy_number          = 2;

const int x_window_size         = 840;
const int y_window_size         = 780;

enum textures_enum
{
    player_texture      = 0,
    map_texture         = 1,
    easyenemy_texture   = 2,
    texture_amount      = 3
    //this is needed for an array of texture
    //to know it maximum size
    //later there will be used operator new
    //in order to allocate memory for textures variable
};

//TODO: check directions
enum directions{
    STAY            = 1,
    RIGHT_DIR       = 2,
    LEFT_DIR        = 3,
    JUMP            = 4,
    LEFT_JUMP       = 5,
    RIGHT_JUMP      = 6

};

enum types{
    EASY_ENEMY      = 1,
    PLAYER          = 2,
    MAP             = 3
};

int         play            ();
void        setTextures     ();
float       distanceModule  (const sf::Vector2f &v1, const sf::Vector2f &v2);

#endif //MYGAME_GAME_H