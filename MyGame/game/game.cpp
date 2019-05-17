#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <list>

#include "../player/player.h"
#include "../mission.h"
#include "../player/Enemy.h"
#include "../map/map.h"
#include "menu.h"
#include "game.h"
#include "game_manager.h"
#include <math.h>

///////////THE MAIN FILE
///////////HERE IS WHERE ALL THE GAME STARTS

//*********************************************************

int play() {
    setTextures();

    sf::RenderWindow window(sf::VideoMode(x_window_size, y_window_size), "My Game UwU");
    menuOpen(window);

    Map map(TileMap, HEIGHT_MAP, WIDTH_MAP, TILE_SIZE, &textures[map_texture]);

    Player player(TILE_SIZE * 2, 650, player_w, player_h, player_s, player_animation_s, move_frame_amount,
            player_collide_area, &textures[player_texture]);

    player.view_.reset(sf::FloatRect(0, 0, x_window_size, y_window_size));
    GameManager gamemanager(&player, &map, enemy_number);

    static sf::Music back_music;
    back_music.openFromFile("music/eva_opening.ogg");
    back_music.play();

    while (window.isOpen())
    {
        //window.clear();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.setView(player.view_);
        //map.draw(window);
        //window.display();
        window.clear(sf::Color::Yellow);

        if(gamemanager.interact(event, window) == 1)
        {
            //window.close();
            break;
        }

        window.display();
    }

    back_music.stop();

    if(player.isOnDrug_())
        menuScreamer(window);
    else
        menuGameOver(window);

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

    sf::Image heroImage;
    heroImage.loadFromFile(playerImageFile);
    heroImage.createMaskFromColor(sf::Color::Black);
    textures[player_texture].loadFromImage(heroImage);

    sf::Image mapImage;
    mapImage.loadFromFile(mapImageFile);
    textures[map_texture].loadFromImage(mapImage);

    sf::Image easyEnemyImage;
    easyEnemyImage.loadFromFile(easyEnemyImageFile);
    easyEnemyImage.createMaskFromColor(sf::Color(255, 0, 0));
    textures[easyenemy_texture].loadFromImage(easyEnemyImage);
}
