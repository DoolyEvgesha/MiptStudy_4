#ifndef MYGAME_PLAYER_H
#define MYGAME_PLAYER_H

#include "../map/map.h"
#include "../game/object.h"

class Player{

public:
    float       x_;
    float       y_;
    float       width_;
    float       height_;
    float       dx_;
    float       dy_;
    float       speed_;
    bool        life_;
    int         direction_;
    int         score_;
    int         health_;
    sf::String  File_;
    sf::Image   image_;
    sf::Texture texture_;
    sf::Sprite  sprite_;

    Player                  (sf::String F, float X, float Y, float W, float H);

    void update             (float time);
    void interactionWithMap ();
    float getX              ();
    float getY              ();
};

#endif //MYGAME_PLAYER_H
