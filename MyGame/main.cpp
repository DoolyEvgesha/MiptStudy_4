#include <iostream>
#include <SFML/Graphics.hpp>

#include "player/player.h"
#include "map/map.h"
#include "view/view.h"


int main() {
    sf::RenderWindow window(sf::VideoMode(640, 480), "My Game UwU");
    //view.reset(sf::FloatRect(0, 0, 640, 480));

    Player p("hero.png", 250, 250, 96.0, 96.0);

    float CurrentFrame = 0;
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

        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left))) {
            p.direction_    = 1;
            p.speed_        = 0.1;

            CurrentFrame    += 0.005 * time;
            if (CurrentFrame > 3) CurrentFrame -= 3;

            p.sprite_.setTextureRect(sf::IntRect(96 * int(CurrentFrame), 96, 96, 96));
        }

        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right)))
        {
            p.direction_ = 0;
            p.speed_ = 0.1;

            CurrentFrame += 0.005 * time;
            if (CurrentFrame > 3) CurrentFrame -= 3;

            p.sprite_.setTextureRect(sf::IntRect(96  *  int(CurrentFrame), 192, 96, 96));
        }


        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up)))
        {
            p.direction_ = 3;
            p.speed_ = 0.1;
            CurrentFrame += 0.005 * time;
            if (CurrentFrame > 3) CurrentFrame -= 3;
            p.sprite_.setTextureRect(sf::IntRect(96 * int(CurrentFrame), 288, 96, 96));
        }

        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down)))
        {
            p.direction_    = 2;
            p.speed_        = 0.1;
            CurrentFrame    += 0.005 * time;
            if (CurrentFrame > 3) CurrentFrame -= 3;
            p.sprite_.setTextureRect(sf::IntRect(96  *  int(CurrentFrame), 0, 96, 96));
        }

        p.update(time);

        window.setView(view);
        window.clear();
        window.draw(p.sprite_);
        window.display();
    }

    return 0;
}