#ifndef MYGAME_MENU_H
#define MYGAME_MENU_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Audio/Music.hpp>

void menuOpen(sf::RenderWindow & window) {
    sf::Texture menuTexturePlay, menuTextureExit, menuBackground;
    menuTexturePlay.loadFromFile("images/play.png");
    menuTextureExit.loadFromFile("images/exit.png");
    menuBackground. loadFromFile("images/menu_background.png");
    sf::Sprite menuPlay(menuTexturePlay), menuExit(menuTextureExit), menuBg(menuBackground);

    bool isMenu = true;
    int menuNum = 0;

    menuPlay.setPosition(100, 30);
    menuExit.setPosition(100, 150);
    menuBg.  setPosition(0,   0);

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
            menuPlay.setColor(sf::Color::Magenta);
            menuNum = 1;
        }
        if (sf::IntRect(100, 150, 300, 50).contains(sf::Mouse::getPosition(window)))
        {
            menuExit.setColor(sf::Color::Magenta);
            menuNum = 2;
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if (menuNum == 1) isMenu = false;
            if (menuNum == 2)
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

void menuGameOver(sf::RenderWindow & window)
{
    sf::Texture menuTextureExit, menuBackground;
    menuTextureExit.loadFromFile("images/exit.png");
    menuBackground. loadFromFile("images/game_over_normal.png");
    sf::Sprite menuExit(menuTextureExit), menuBg(menuBackground);

    bool isMenu = true;
    bool exit;

    menuExit.setPosition(300, 100);
    //menuBg.  setPosition(500, 20);
    menuBg.  setPosition(0, 0);

    static sf::Music go;
    go.openFromFile("music/yeah.wav");
    go.play();
    go.setLoop(true);


    while (isMenu && window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        menuExit.setColor(sf::Color::White);
        exit = false;
        window.clear(sf::Color::Yellow);

        if (sf::IntRect(300, 70, 300, 100).contains(sf::Mouse::getPosition(window)))
        {
            menuExit.setColor(sf::Color::Magenta);
            exit = true;
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if (exit)
            {
                window.close();
                isMenu = false;
            }
        }

        window.draw(menuBg);
        window.draw(menuExit);

        window.display();
    }
}

void menuScreamer(sf::RenderWindow & window)
{
    sf::Texture menuTextureExit, menuBackground;
    menuTextureExit.loadFromFile("images/exit.png");
    menuBackground. loadFromFile("images/game_over.png");
    sf::Sprite menuExit(menuTextureExit), menuBg(menuBackground);

    bool isMenu = true;
    bool exit;

    menuExit.setPosition(100, 550);
    menuBg.  setPosition(0, 0);
    //menuBg.  setPosition(755, 20);

    static sf::Music go;
    go.openFromFile("music/Smoke_weed_everyday.ogg");
    go.play();
    go.setLoop(true);

    while (isMenu && window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        menuExit.setColor(sf::Color::White);
        exit = false;
        window.clear(sf::Color::Yellow);

        if (sf::IntRect(100, 550, 300, 100).contains(sf::Mouse::getPosition(window)))
        {
            menuExit.setColor(sf::Color::Magenta);
            exit = true;
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if (exit)
            {
                window.close();
                isMenu = false;
            }
        }

        window.draw(menuBg);
        window.draw(menuExit);

        window.display();
    }
    go.stop();
}

#endif //MYGAME_MENU_H
