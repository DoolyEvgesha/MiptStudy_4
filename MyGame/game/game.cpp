#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <list>

#include "../player/player.h"
#include "../view/view.h"
#include "../mission.h"
#include "../player/Enemy.h"
#include "../map/map.h"
#include "game.h"
#include "game_manager.h"
#include <math.h>

///////////THE MAIN FILE
///////////HERE IS WHERE ALL THE GAME STARTS

//*********************************************************

int play() {
    setTextures();

    sf::RenderWindow window(sf::VideoMode(640, 480), "My Game UwU");
    view.reset(sf::FloatRect(0, 0, 640, 480));

    Map map(TileMap, HEIGHT_MAP, WIDTH_MAP, TILE_SIZE, &textures[map_texture]);

    Player player(1000, 300, player_w, player_h, player_s, player_animation_s, move_frame_amount,
            player_collide_area, &textures[PLAYER]);

    player.view_.reset(sf::FloatRect(0, 0, 640, 480));
    GameManager gamemanager(&player, &map);
    //sf::Clock clock;

    while (window.isOpen())
    {
        window.clear();
        //float time = clock.getElapsedTime().asMicroseconds();
        //clock.restart();
        //time /= 800;

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        //window.setView(player.view_);
        player.draw(window);
        map.draw(window);

        window.display();
    }

    delete[] textures;
    return 0;
}

float distanceModule(const sf::Vector2f &v1, const sf::Vector2f &v2)
{
    return sqrt((v1.x - v2.x)*(v1.x - v2.x) + (v1.y - v2.y)*(v1.y - v2.y));
}

void setTextures()
{
    textures = new sf::Texture[texture_amount];

    sf::Image mapImage;
    mapImage.loadFromFile(mapImageFile);
    textures[map_texture].loadFromImage(mapImage);

    //sf::Texture map;
    //map.loadFromImage(mapImage);
    //sf::Sprite s_map;
    //s_map.setTexture(map);

    sf::Image heroImage;
    heroImage.loadFromFile(playerImageFile);
    heroImage.createMaskFromColor(sf::Color::Black);
    textures[player_texture].loadFromImage(heroImage);


    sf::Image easyEnemyImage;
    easyEnemyImage.loadFromFile(easyEnemyImageFile);
    easyEnemyImage.createMaskFromColor(sf::Color(255, 0, 0));
    textures[easyenemy_texture].loadFromImage(easyEnemyImage);
}
