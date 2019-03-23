#include <iostream>
#include <SFML/Graphics.hpp>

#include "player/player.h"
#include "map/map.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(640, 480), "My Game UwU");

    sf::Image heroimage;
    heroimage.loadFromFile("images/hero.png");

    sf::Texture herotexture;
    herotexture.loadFromImage(heroimage);

    sf::Sprite herosprite;
    herosprite.setTexture(herotexture);
    herosprite.setTextureRect(sf::IntRect(0, 192, 96, 96));
    herosprite.setPosition(50, 25);

    sf::Clock clock;

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time/800;

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {herosprite.move(-0.1 * time, 0);}

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {herosprite.move(0.1 * time, 0);}

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {herosprite.move(0, -0.1 * time);}

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {herosprite.move(0, 0.1 * time);}

        window.clear();
        window.draw(herosprite);
        window.display();
    }

    return 0;
}