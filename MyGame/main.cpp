#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>

#include "player/player.h"
#include "map/map.h"
#include "view/view.h"
#include "mission.h"


int main() {
    sf::RenderWindow window(sf::VideoMode(1366, 768), "My Game UwU");
    view.reset(sf::FloatRect(0, 0, 640, 480));

    sf::Image map_image;
    map_image.loadFromFile("images/map.png");
    sf::Texture map;
    map.loadFromImage(map_image);
    sf::Sprite s_map;
    s_map.setTexture(map);

    Player p("hero.png", 250, 250, 96.0, 96.0);

    bool showMissionText = true;

    sf::Image quest_image;
    quest_image.loadFromFile("images/missionbg.jpg");
    quest_image.createMaskFromColor(sf::Color(0, 0, 0));
    sf::Texture quest_texture;
    quest_texture.loadFromImage(quest_image);
    sf::Sprite s_quest;
    s_quest.setTexture(quest_texture);
    s_quest.setTextureRect(sf::IntRect(0, 0, 340, 510));
    s_quest.setScale(0.6f, 0.6f);

    sf::Font font;
    font.loadFromFile("images/GLADES-DEMO.ttf");
    sf::Text text("", font, 20);
    text.setFillColor(sf::Color::Black);

    float CurrentFrame = 0;
    sf::Clock clock;
    sf::Clock gameTimeClock;
    int gameTime = 0;
    int createObjectForMapTimer = 0;

    bool isMove = false;
    float dX = 0;
    float dY = 0;

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds();

        if (p.life_)
        { gameTime = gameTimeClock.getElapsedTime().asSeconds();}
        clock.restart();
        time = time/800;

        sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
        sf::Vector2f pos = window.mapPixelToCoords(pixelPos);

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if(event.type == sf::Event::MouseButtonPressed)
                if(event.key.code == sf::Mouse::Left)
                    if(p.sprite_.getGlobalBounds().contains(pos.x, pos.y))
                    {
                        dX = pos.x - p.sprite_.getPosition().x;
                        dY = pos.y - p.sprite_.getPosition().y;
                        isMove = true;
                    }

            if(event.type == sf::Event::MouseButtonReleased)
                if(event.key.code == sf::Mouse::Left) {
                    isMove = false;
                    p.sprite_.setColor(sf::Color::White);
                }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Tab) {
                    switch (showMissionText) {
                        case true: {
                            std::ostringstream playerHealthString;
                                playerHealthString << p.health_;
                                std::ostringstream task;
                                task << getTextMission(getCurrentMission(p.getX()));
                                text.setString("Health: " + playerHealthString.str() + "\n" + task.str());
                                showMissionText = false;
                            break;
                        }
                        case false: {
                            text.setString("");
                            showMissionText = true;
                            break;
                        }
                    }
                }
            }
        }

        if(isMove)
        {
            p.sprite_.setColor(sf::Color::Blue);
            p.x_ = pos.x - dX;
            p.y_ = pos.y - dY;
        }

        //---------------CHANGING DIRECTIONS---------------
        //-------------------------------------------------
        if(p.life_) {
            if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left))) {
                p.direction_ = 1;
                p.speed_ = 0.1;

                CurrentFrame += 0.005 * time;
                if (CurrentFrame > 3) CurrentFrame -= 3;

                p.sprite_.setTextureRect(sf::IntRect(96 * int(CurrentFrame), 96, 96, 96));
            }

            if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right))) {
                p.direction_ = 0;
                p.speed_ = 0.1;

                CurrentFrame += 0.005 * time;
                if (CurrentFrame > 3) CurrentFrame -= 3;

                p.sprite_.setTextureRect(sf::IntRect(96 * int(CurrentFrame), 192, 96, 96));
            }


            if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up))) {
                p.direction_ = 3;
                p.speed_ = 0.1;
                CurrentFrame += 0.005 * time;
                if (CurrentFrame > 3) CurrentFrame -= 3;
                p.sprite_.setTextureRect(sf::IntRect(96 * int(CurrentFrame), 288, 96, 96));
            }

            if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down))) {
                p.direction_ = 2;
                p.speed_ = 0.1;
                CurrentFrame += 0.005 * time;
                if (CurrentFrame > 3) CurrentFrame -= 3;
                p.sprite_.setTextureRect(sf::IntRect(96 * int(CurrentFrame), 0, 96, 96));

            }
            //getPlayerCoordForView(p.getX(), p.getY());
        }
        else{
            view.rotate(0.1);
        }
        //---------------------------------------------------------------------------
        //---------------------------------------------------------------------------

        sf::Vector2i localPosition = sf::Mouse::getPosition(window);

        if(localPosition.x < 15){ view.move(-0.2 * time, 0); }
        if(localPosition.x > window.getSize().x - 15) { view.move(0.2*time, 0); }
        if(localPosition.y > window.getSize().y - 15) { view.move(0, 0.2*time); }
        if(localPosition.y < 15) { view.move(0, -0.2*time); }

        createObjectForMapTimer += time;
        if(createObjectForMapTimer > 3000)
        {
            randomMapGenerate();
            createObjectForMapTimer = 0;
        }

        p.update(time);

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

        if (!showMissionText)
        {
            text.setPosition(view.getCenter().x + 125, view.getCenter().y - 120);
            s_quest.setPosition(view.getCenter().x + 115, view.getCenter().y - 130);
            window.draw(s_quest);
            window.draw(text);
        }

        window.draw(p.sprite_);
        window.display();
    }

    return 0;
}