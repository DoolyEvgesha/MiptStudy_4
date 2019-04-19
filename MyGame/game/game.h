#ifndef MYGAME_GAME_H
#define MYGAME_GAME_H

#include <SFML/Graphics/Texture.hpp>

static sf::Texture *textures;

const char playerImageFile[]    = "../images/MilesTailsPrower.gif";
const char easyEnemyImageFile[] = "../images/shamaich.png";
const char mapImageFile[]       = "../images/map.png";

enum textures
{
    player_texture,
    easyenemy_texture,
    map_texture,
    texture_amount
    //this is needed for an array of texture
    //to know it maximum size
    //later there will be used operator new
    //in order to allocate memory for textures variable
};

//TODO: check directions
enum directions{
    UP_DIR          = 1,
    //DOWN_DIR        = 1,
    LEFT_DIR        = 2,
    RIGHT_DIR       = 3,
    //UP_LEFT_DIR     = 4,
    //UP_RIGHT_DIR    = 5,
    //DOWN_LEFT_DIR   = 6,
    //DOWN_RIGHT_DIR  = 7,
};

enum types{
    EASY_ENEMY  = 1,
    PLAYER      = 2,
    MAP         = 3
};

int         play            ();
void        setTextures     ();
float       distanceModule  (const sf::Vector2f &v1, const sf::Vector2f &v2);

#endif //MYGAME_GAME_H