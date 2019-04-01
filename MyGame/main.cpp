#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <cmath>

#include "player/player.h"
#include "map/map.h"
#include "view/view.h"
#include "mission.h"
#include "player/Enemy.h"


int main() {
    sf::RenderWindow window(sf::VideoMode(640, 480), "My Game UwU");
    view.reset(sf::FloatRect(0, 0, 640, 480));

    sf::Image map_image;
    map_image.loadFromFile("images/map.png");
    sf::Texture map;
    map.loadFromImage(map_image);
    sf::Sprite s_map;
    s_map.setTexture(map);

    sf::Image heroImage;
    heroImage.loadFromFile("images/MilesTailsPrower.gif");
    heroImage.createMaskFromColor(sf::Color::Black);

    sf::Image easyEnemyImage;
    easyEnemyImage.loadFromFile("images/shamaich.png");
    easyEnemyImage.createMaskFromColor(sf::Color(255, 0, 0));

    Player p(heroImage, 750, 500, 40, 30, "Player1");
    Enemy easyEnemy(easyEnemyImage, 850, 671, 200, 97, "EasyEnemy");

    sf::Clock clock;

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time /= 800;

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

        }
        p.update(time);
        easyEnemy.update(time);

        window.setView(view);
        window.clear();

        //===============================================================================
        //============DRAWING A MAP======================================================
        for (int i = 0; i < HEIGHT_MAP; i++)
            for (int j = 0; j < WIDTH_MAP; j++)
            {
                if (TileMap[i][j] == ' ')  s_map.setTextureRect(sf::IntRect(0, 0, 32, 32));
                if (TileMap[i][j] == 's')  s_map.setTextureRect(sf::IntRect(32, 0, 32, 32));
                if (TileMap[i][j] == '0')  s_map.setTextureRect(sf::IntRect(64, 0, 32, 32));
                if (TileMap[i][j] == 'f') s_map.setTextureRect(sf::IntRect(96, 0, 32, 32));
                if (TileMap[i][j] == 'h') s_map.setTextureRect(sf::IntRect(128, 0, 32, 32));
                s_map.setPosition(j * 32, i * 32);

                window.draw(s_map);
            }
        //===============================================================================
        //===============================================================================

        window.draw(easyEnemy.sprite_);
        window.draw(p.sprite_);
        window.display();
    }

    return 0;
}