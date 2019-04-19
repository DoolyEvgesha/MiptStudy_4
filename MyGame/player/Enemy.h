#ifndef MYGAME_ENEMY_H
#define MYGAME_ENEMY_H

#include "../entity.h"
#include "../map/map.h"
#include "../player/player.h"

class Enemy: public Entity{
public:
    Enemy(float x, float y, int w, int h, float speed, float animation_speed, int move_frame_amount,
          float collideArea, const sf::Texture *move_animation_texture, Player *player);
    void checkCollisionWithMap(float Dx, float Dy);
    void update(float time);
};

Enemy::Enemy(float x, float y, int w, int h, float speed, float animation_speed, int move_frame_amount,
             float collideArea, const sf::Texture *move_animation_texture, Player *player) :
       Entity(x, y, w, h, speed, animation_speed, move_animation_texture, move_frame_amount,
               EASY_ENEMY, collideArea)
{}
#endif //MYGAME_ENEMY_H