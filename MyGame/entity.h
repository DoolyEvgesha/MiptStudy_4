#ifndef MYGAME_ENTITY_H
#define MYGAME_ENTITY_H

#include <SFML/Graphics.hpp>

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
    sf::Texture texture_;
    sf::Sprite  sprite_;

    Entity(sf::Image &, float, float, int, int, sf::String);
};

Entity::Entity(sf::Image & image, float X, float Y, int W, int H, sf::String Name):
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
    name_       (Name)

{
    texture_.loadFromImage(image);
    sprite_.setTexture(texture_);
    sprite_.setOrigin(width_/2, height_/2);

}

#endif //MYGAME_ENTITY_H
