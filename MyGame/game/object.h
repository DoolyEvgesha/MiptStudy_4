#ifndef MYGAME_OBJECT_H
#define MYGAME_OBJECT_H

#include <SFML/Window.hpp>

class Object{

public:
    Object(float x, float y, float speed);
    float           getX            ();
    float           getY            ();
    int             getDirection    ();
    sf::Vector2f    getLocation     ();
    //~Object();

protected:
    int             direction_;
    float           speed_;
    void            move            (float dx, float dy);
    sf::Vector2f    obj_coord; //coordinates, using structure from SFML
};

#endif //MYGAME_OBJECT_H
