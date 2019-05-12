#ifndef MYGAME_GAME_MANAGER_H
#define MYGAME_GAME_MANAGER_H

#include <SFML/System/Clock.hpp>
#include "../player/player.h"
#include <unistd.h>
#include "../player/Enemy.h"

class GameManager{
public:
    int interact(const sf::Event &event, sf::RenderWindow &window);
    std::list<Entity*> entities_;
    explicit GameManager(Player * p, Map * m, int enem_num);

private:
    int             score_;
    int             enemyNumber_;
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

#include <assert.h>

int GameManager::interact(const sf::Event &event, sf::RenderWindow &window)
{
    time_ = eventTimer_.getElapsedTime().asMicroseconds();
    score_ += time_ / 1000;
    eventTimer_.restart();
    time_ /= game_speed;

    if(!player_->getState())
    {
        std::ostringstream score;
        score << score_;
        score_text_.setString("Your score is " + score.str());
        score_text_.setPosition(player_->getViewCoord() + sf::Vector2f(-200, -100));
        window.clear(sf::Color::Black);
        window.draw(score_text_);
        window.display();
        usleep(15000);
        return 1;
    }

    if(enemyNumber_) {
        float tlsz = map_->getTileSize();
        for (int i = 0; i < enemyNumber_; i++) {
            entities_.push_back(new Enemy(tlsz * (i + 100), tlsz * 2, enemy_w, enemy_h, enemy_s, enemy_animation_s,
                                          enemy_frame_amount, enemy_collide_area, &textures[easyenemy_texture],
                                          player_));
        }
        enemyNumber_ = 0;
    }

    collide(event, window);

    std::ostringstream health;
    health << player_->getHealth();
    health_text_.setString("Health:" + health.str());
    health_text_.setPosition(sf::Vector2f(player_->getViewCoord().x, player_->getViewCoord().y));

    window.draw(health_text_);

    return 0;
}

GameManager::GameManager(Player * p, Map * m, int enem_num):
    score_              (0),
    enemyNumber_        (enem_num),
    player_             (p),
    map_                (m)
{
    font_.loadFromFile("images/GLADES-DEMO.ttf");
    score_text_.setFont(font_);
    score_text_.setFillColor(sf::Color::Yellow);

    health_text_.setFont(font_);
    health_text_.setFillColor(sf::Color::Black);

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
