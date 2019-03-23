#include "object.h"

Object::Object(float x, float y, float speed):
    direction_(1),
    speed_(speed),
    obj_coord(sf::Vector2f(x, y))
{}

void Object::move(float dx, float dy)
{
    obj_coord.x += dx;
    obj_coord.y += dy;
}

float Object::getX() { return obj_coord.x; }
float Object::getY() { return obj_coord.y; }

sf::Vector2f Object::getLocation() { return obj_coord; }

int Object::getDirection() { return direction_; }