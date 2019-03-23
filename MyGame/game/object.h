#ifndef MYGAME_OBJECT_H
#define MYGAME_OBJECT_H

#include <SFML/Window.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Object{

public:
    Object(float x, float y, float speed);
    float           getX            ();
    float           getY            ();
    int             getDirection    ();
    sf::Vector2f    getLocation     ();

protected:
    int             direction_;
    float           speed_;
    void            move            (float dx, float dy);
    sf::Vector2f    obj_coord;      //coordinates, using structure from SFML
};

class GraphObject{
public:

protected:
    sf::Vector2f    sprite_coord;
    float           animation_speed_;
    float           cur_frame;

    float           width_, height_;
    sf::String      File_;
    sf::Image       image_;
    sf::Texture     texture_;
    sf::Sprite      sprite_;
};

#endif //MYGAME_OBJECT_H
