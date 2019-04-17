#ifndef MYGAME_ENEMY_H
#define MYGAME_ENEMY_H

#include "../entity.h"
#include "../map/map.h"

class Enemy: public Entity{
public:
    Enemy(const sf::Texture*, float X, float Y, int W, int H, sf::String Name);
    void checkCollisionWithMap(float Dx, float Dy);
    void update(float time);
};

Enemy::Enemy(const sf::Texture* animation_texture, float X, float Y,int W,int H,sf::String Name):
    Entity(animation_texture,X,Y,W,H,Name){
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

