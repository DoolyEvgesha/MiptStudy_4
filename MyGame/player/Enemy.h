#ifndef MYGAME_ENEMY_H
#define MYGAME_ENEMY_H

#include <math.h>
#include "../entity.h"
#include "../map/map.h"
#include "../player/player.h"


const int   enemy_w            = 100;
const int   enemy_h            = 100;
const float enemy_s            = 0.4;
const float enemy_animation_s  = 0.04;
const int   enemy_frame_amount = 8;
const float enemy_collide_area = 1000;

enum
{
    ENEMY_LEFT      = 1,
    ENEMY_RIGHT     = 2
};

class Enemy: public Entity{
private:
    Player * player_;
    int      health_;
public:
    Enemy(float x, float y, int w, int h, float speed, float animation_speed, int move_frame_amount,
          float collideArea, const sf::Texture *move_animation_texture, Player *player);

    int         move        () override;
    void        draw        (sf::RenderWindow &window) override { window.draw(sprite_); }
    int         update      (float time, const sf::Event & event) override;
    int         collide     (Entity * entity) override;
    int         getDirection(const sf::Event &event) override { return 0; }
    float       getDirX(){return 0;}
};

int Enemy::update(float time, const sf::Event &event)
{
    changeFrame(time);

    //dir_.x = 0;
    dir_.y = 0;

    //here we write, where enemy runs
    //in my case a repeating cycle

    if(dir_.x < 0)
    {
        direction_ = ENEMY_LEFT;
        changeFramePosition(ENEMY_LEFT);
    }
    else if(dir_.x > 0)
    {
        direction_ = ENEMY_RIGHT;
        changeFramePosition(ENEMY_RIGHT);
    }
    else {
        dir_.x = speed_ * time;
        std::cout << dir_.x << std::endl;
    }

    return 0;
}

int Enemy::collide(Entity *entity)
{
    switch(entity->getType())
    {
        case EASY_ENEMY:
            if(collideArea_ + entity->getCollideArea() > distanceModule(getLocation(), entity->getLocation()))
            {
                dir_.x = - dir_.x/* *1,5 */;
            }

            break;

        case PLAYER:
            if(collideArea_ + entity->getCollideArea() > distanceModule(getLocation(), entity->getLocation()))
            {
                if((player_->getDirY() > 0) && (!player_->getOnGround()))
                //if player is jumping onto enemy - kill enemy
                {
                    dir_.x  = 0;
                    health_ = 0;
                    state_  = false;
                }
            }
            break;

        case MAP: {
            auto map = dynamic_cast<Map *> (entity);
            //int map_width = map->getWidth();
            //int map_height = map->getHeight();

            float next_position_x = bodyCoord_.x + dir_.x;
            int i = next_position_x / map->getTileSize();
            int j = bodyCoord_.y / map->getTileSize();

            if (TileMap[j][i] == '0') {
                dir_.x = - dir_.x;
                std::cout << dir_.x << " " <<  bodyCoord_.x << std::endl;
                //TODO: CHECK IF MOVE IS RIGHT!!!!!!!!!!!!!!!!!
                std::cout << "========================="<< std::endl;
                move();
                std::cout << dir_.x << " " <<  bodyCoord_.x << std::endl;
                ////////////////////
                std::cout << "========================="<< std::endl;
            }
            break;
        }

        default:
            break;
    }
    return 0;
}

Enemy::Enemy(float x, float y, int w, int h, float speed, float animation_speed, int move_frame_amount,
             float collideArea, const sf::Texture *move_animation_texture, Player *player) :
       Entity(x, y, w, h, speed, animation_speed, move_animation_texture, move_frame_amount,
               EASY_ENEMY, collideArea),
               player_      (player),
               health_      (100)
{}

int Enemy::move()
{
    physEntity::move(dir_.x, dir_.y);
    visualEntity::move(dir_.x, dir_.y);
    return 0;
}
#endif //MYGAME_ENEMY_H