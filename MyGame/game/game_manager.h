#ifndef MYGAME_GAME_MANAGER_H
#define MYGAME_GAME_MANAGER_H

#include <SFML/System/Clock.hpp>
#include "../player/player.h"

class gameManager{
public:
    std::list<Entity*> entities;
    explicit gameManager(Player * p);
private:
    int             score_;
    sf::Clock       enemyTimer_;
    sf::Clock       eventTimer_;
    Player *        player_;
    //TODO: write map class, like Enemies and Player
    //Map *         map; later, buddies
    sf::Font        font_;
    sf::Text        score_text_;
    sf::Text        health_text_;
    float           time_;

    void            collide(const sf::Event &event, sf::RenderWindow &window);

};

gameManager::gameManager(Player * p):
    score_      (0),
    player_     (p)
{
    font_.loadFromFile("../images/GLADES_DEMO.ttf");
    score_text_.setFont(font_);
    score_text_.setFillColor(sf::Color::Yellow);

    health_text_.setFont(font_);
    health_text_.setFillColor(sf::Color::Red);

}

void gameManager::collide(const sf::Event &event, sf::RenderWindow &window)
{
    Entity * cur_entity = nullptr;
    std::list<Entity*>::iterator it;
    std::list<Entity*>::iterator jt;

    //check the state of an object
    //delete if it is dead
    //and erase in that case
    for(auto i = entities.begin(); i != entities.end(); i++)
    {
        cur_entity = *it;

        if(!(cur_entity->getState()))
        {
            delete cur_entity;
            it = entities.erase(it);
        }
        else
        {
            cur_entity->update(time_, event);
            for(jt = it; jt != entities.end(); jt++)
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
