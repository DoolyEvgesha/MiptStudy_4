#ifndef MYGAME_ENEMY_H
#define MYGAME_ENEMY_H

#include "../entity.h"
#include "../map/map.h"
#include "../player/player.h"

class Enemy: public Entity{
public:
    Enemy(float x, float y, int width, int height, float speed, float animation_speed, int move_frame_amount,
          float collideArea, const sf::Texture *move_animation_texture, Player *player);
    void checkCollisionWithMap(float Dx, float Dy);
    void update(float time);
};

Enemy::Enemy(const sf::Texture* animation_texture, float X, float Y,int W,int H,const sf::String Name):
    Entity(X,Y,W,H,10,10,animation_texture,10,EASY_ENEMY, 10){
    //obj = level.GetObjects("solid");

    if (Name == "EasyEnemy")
    {
        sprite_.setTextureRect(sf::IntRect(0, 0, width_, height_));
        dx_ = 0.1;
    }
}

void Enemy::checkCollisionWithMap(float Dx, float Dy)
{
    for (int i = y_ / 32; i < (y_ + height_) / 32; i++)
        for (int j = x_ / 32; j<(x_ + width_) / 32; j++)
        {
            if (TileMap[i][j] == '0')
            {
                if (Dy>0){ y_ = i * 32 - height_; }
                if (Dy<0){ y_ = i * 32 + 32; }
                if (Dx>0){ x_ = j * 32 - width_; dx_ = -0.1; sprite_.scale(-1, 1); }
                if (Dx<0){ x_ = j * 32 + 32; dx_ = 0.1; sprite_.scale(-1, 1); }
            }
        }
}

void Enemy::update(float time)
{
    if (name_ == "EasyEnemy"){

        checkCollisionWithMap(dx_, 0);
        x_ += dx_*time;
        sprite_.setPosition(x_ + width_ / 2, y_ + height_ / 2);
        if (health_ <= 0){ life_ = false; }
    }
}
#endif //MYGAME_ENEMY_H

