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

enum directions{
    UP_DIR      = 0,
    DOWN_DIR    = 1,
    LEFT_DIR,
    RIGHT_DIR,
    UP_LEFT_DIR,
    UP_RIGHT_DIR,
    DOWN_LEFT_DIR,
    DOWN_RIGHT_DIR,
};

int play();

void setTextures();

#endif //MYGAME_GAME_H
