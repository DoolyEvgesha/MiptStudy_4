#ifndef MYGAME_ENTITY_H
#define MYGAME_ENTITY_H

#include <SFML/Graphics.hpp>
#include "level.h"

class Entity
{
public:
    float       dx_;
    float       dy_;
    float       x_;
    float       y_;
    int         width_;
    int         height_;
    float       speed_;
    float       moveTimer;
    bool        life_;
    bool        isMoved_;
    bool        onGround_;
    int         health_;
    sf::String  name_;
    //sf::Texture texture_;
    const sf::Texture * texture_;
    sf::Sprite  sprite_;

    Entity(const sf::Texture * , float, float, int, int, sf::String);
    virtual void update(float time) = 0;
    //sf::FloatRect getRect();
};

Entity::Entity(const sf::Texture * animation_texture, float X, float Y, int W, int H, sf::String Name):
    dx_         (0),
    dy_         (0),
    x_          (X),
    y_          (Y),
    width_      (W),
    height_     (H),
    speed_      (0),
    moveTimer   (0),
    life_       (true),
    isMoved_    (false),
    onGround_   (false),
    health_     (100),
    name_       (Name),
    texture_    (animation_texture)

{
    //texture_.loadFromImage(image);
    sprite_.setTexture(*texture_);
    sprite_.setOrigin(width_/2, height_/2);

}

//sf::FloatRect Entity::getRect(){ return sf::FloatRect(x_, y_, width_, height_); }

#endif //MYGAME_ENTITY_H
