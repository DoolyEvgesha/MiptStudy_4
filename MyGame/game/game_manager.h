#ifndef MYGAME_GAME_MANAGER_H
#define MYGAME_GAME_MANAGER_H

#include <SFML/System/Clock.hpp>
#include "../player/player.h"
#include <unistd.h>

class GameManager{
public:
    int interact(const sf::Event &event, sf::RenderWindow &window);
    std::list<Entity*> entities_;
    explicit GameManager(Player * p, Map * m);
private:
    int             score_;
    sf::Clock       enemyTimer_;
    sf::Clock       eventTimer_;
    Player *        player_;
    Map *           map_;
    sf::Font        font_;
    sf::Text        score_text_;
    sf::Text        health_text_;
    float           time_;

    void            collide(const sf::Event &event, sf::RenderWindow &window);

};

int GameManager::interact(const sf::Event &event, sf::RenderWindow &window)
{
    time_ = eventTimer_.getElapsedTime().asMicroseconds();
    score_ += time_ / 1000;
    eventTimer_.restart();
    time_ /= game_speed;

    if(!player_->getState())
    {
        //TODO:write screen with score
        //the player dies, so
        //there is a window with it's score
        usleep(15000);
        return 1;
    }

    collide(event, window);
    //TODO: set writen score
    return 0;
}

GameManager::GameManager(Player * p, Map * m):
    score_      (0),
    player_     (p),
    map_        (m)
{
    /*font_.loadFromFile("../images/GLADES_DEMO.ttf");
    score_text_.setFont(font_);
    score_text_.setFillColor(sf::Color::Yellow);

    health_text_.setFont(font_);
    health_text_.setFillColor(sf::Color::Red);*/

    entities_.push_back(map_);
    entities_.push_back(player_);
}

void GameManager::collide(const sf::Event &event, sf::RenderWindow &window)
{
    Entity * cur_entity = nullptr;
    std::list<Entity*>::iterator it;
    std::list<Entity*>::iterator jt;

    //check the state of an object
    //delete if it is dead
    //and erase in that case
    for(auto it = entities_.begin(); it != entities_.end(); it++)
    {
        cur_entity = *it;

        if(!(cur_entity->getState()))
        {
            delete cur_entity;
            it = entities_.erase(it);
        }
        else
        {
            cur_entity->update(time_, event);
            for(jt = it; jt != entities_.end(); jt++)
            {
                if(!(cur_entity->getState()))
                    break;

                cur_entity->collide(*jt);
                (*jt)->collide(cur_entity);
            }
        }
        if((cur_entity->getState()))
        {
            cur_entity->move();
            cur_entity->draw(window);
        }
    }
}

#endif //MYGAME_GAME_MANAGER_H
