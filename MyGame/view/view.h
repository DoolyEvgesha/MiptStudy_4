#ifndef MYGAME_VIEW_H
#define MYGAME_VIEW_H

#include <SFML/Graphics/View.hpp>

sf::View view;

sf::View getPlayerCoordForView(float x, float y)
{
    view.setCenter(x + 100, y);
    return view;
}

void viewMap(float time) {


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        view.move(0.1*time, 0);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        view.move(0, 0.1 * time);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        view.move(-0.1*time, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        view.move(0, -0.1*time);
    }


}

#endif //MYGAME_VIEW_H
