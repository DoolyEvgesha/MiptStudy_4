#ifndef MYGAME_ENEMY_H
#define MYGAME_ENEMY_H

#include <math.h>
#include "../entity.h"
#include "../map/map.h"
#include "../player/player.h"

class Enemy: public Entity{
private:
    Player * player_;
    //maybe health
public:
    Enemy(float x, float y, int w, int h, float speed, float animation_speed, int move_frame_amount,
          float collideArea, const sf::Texture *move_animation_texture, Player *player);

    int         move        () override;
    void        draw        (sf::RenderWindow &window) override { window.draw(sprite_); }
    int         update      (float time, const sf::Event & event) override;
    int         collide     (Entity * entity) override;
    int         getDirection(const sf::Event &event) override { return 0; }
};

int Enemy::update(float time, const sf::Event &event)
{
    changeFrame(time);

    dir_.x = 0;
    dir_.y = 0;

    sf::Vector2f player_coords(player_->getX(), player_->getY());
    if(player_coords.x < bodyCoord_.x)
    {
        dir_.x = -speed_ * time;
        if(player_coords.y < bodyCoord_.y)
        {
            //TODO:rethink this case
            //dir_.y = -speed_ * time / 1.4;
            //direction_ =
        }
    }
    else if(player_coords.x > bodyCoord_.x)
    {
        //....
    }

    if(fabsf(player_coords.x - physEntity::bodyCoord_.x) < 5 * fabsf(dir_.x))
    {
        changeFramePosition(UP_DIR);
    }
    else
        changeFramePosition(physEntity::direction_);
    return 0;
}

int Enemy::collide(Entity *entity)
{
    switch(entity->getType())
    {
        case EASY_ENEMY:
            if(collideArea_ + entity->getCollideArea() > distanceModule(getLocation(), entity->getLocation()))
            {
                dir_.x = -1.5 * dir_.x;
                dir_.y = -1.5 * dir_.y;
            }

            break;

        case PLAYER:
            if(collideArea_ + entity->getCollideArea() > distanceModule(getLocation(), entity->getLocation()))
            {
                dir_.x = -1.5 * dir_.x;
                dir_.y = -1.5 * dir_.y;

                move();
            }
            break;
        default:
            break;
    }
    return 0;
}

Enemy::Enemy(float x, float y, int w, int h, float speed, float animation_speed, int move_frame_amount,
             float collideArea, const sf::Texture *move_animation_texture, Player *player) :
       Entity(x, y, w, h, speed, animation_speed, move_animation_texture, move_frame_amount,
               EASY_ENEMY, collideArea)
{}

int Enemy::move()
{
    physEntity::move(dir_.x, dir_.y);
    visualEntity::move(dir_.x, dir_.y);
    return 0;
}
#endif //MYGAME_ENEMY_H