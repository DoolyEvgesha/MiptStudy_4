#ifndef MYGAME_VIEW_H
#define MYGAME_VIEW_H

#include <SFML/Graphics/View.hpp>

sf::View view;
/*
sf::View setPlayerCoordForView(float x, float y)
{
    float tempX = x;
    float tempY = y;

    if (x < 320) tempX = 320;
    if (y < 240) tempY = 240;
    if (y > 554) tempY = 554;

    view.setCenter(tempX, tempY);
}
*/
#endif //MYGAME_VIEW_H
