#ifndef MYGAME_GAME_MANAGER_H
#define MYGAME_GAME_MANAGER_H

#include <SFML/System/Clock.hpp>
#include "../player/player.h"

class gameManager{
public:
    std::list<Entity*> entities;
    explicit gameManager(Player * p);
private:
    int score_;
    sf::Clock enemyTimer_;
    sf::Clock eventTimer_;
    Player * player_;
    //Map * map; later, buddies
    sf::Font font;
    sf::Text score_text_;
    sf::Text health_text_;
    float time_;

};

gameManager::gameManager(Player * p):
    player_(p)
    {}

#endif //MYGAME_GAME_MANAGER_H
