#ifndef MYGAME_MENU_H
#define MYGAME_MENU_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/Texture.hpp>

void menu(sf::RenderWindow & window) {
    sf::Texture menuTexturePlay, menuTextureExit, menuBackground;
    menuTexturePlay.loadFromFile("images/111.png");
    menuTextureExit.loadFromFile("images/333.png");
    menuBackground.loadFromFile("images/menu_background.png");
    sf::Sprite menuPlay(menuTexturePlay), menuExit(menuTextureExit), menuBg(menuBackground);

    bool isMenu = true;
    int menuNum = 0;

    menuPlay.setPosition(100, 30);
    menuExit.setPosition(100, 150);
    menuBg.setPosition(0, 0);

    while (isMenu && window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        menuPlay.setColor(sf::Color::White);
        menuExit.setColor(sf::Color::White);
        menuNum = 0;
        window.clear(sf::Color::Yellow);

        if (sf::IntRect(100, 30, 300, 50).contains(sf::Mouse::getPosition(window)))
        {
            menuPlay.setColor(sf::Color(1, 1, 1, 1));
            menuNum = 1;
        }
        if (sf::IntRect(100, 150, 300, 50).contains(sf::Mouse::getPosition(window)))
        {
            menuExit.setColor(sf::Color::Blue);
            menuNum = 3; }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if (menuNum == 1) isMenu = false;
            if (menuNum == 3)
            {
                window.close();
                isMenu = false;
            }
        }

        window.draw(menuBg);
        window.draw(menuPlay);
        window.draw(menuExit);

        window.display();
    }
    ////////////////////////////////////////////////////
}

#endif //MYGAME_MENU_H
