#include <iostream>
#include "player.h"


Player::Player(const sf::String F, float X, float Y, float W, float H):
        x_          (X),
        y_          (Y),
        width_      (W),
        height_     (H),
        dx_         (0),
        dy_         (0),
        speed_      (0),
        life_       (true),
        direction_  (0),
        score_      (0),
        health_     (100),
        File_       (F)

{
    image_.loadFromFile("images/" + File_);
    image_.createMaskFromColor(sf::Color(41, 33, 59));
    texture_.loadFromImage(image_);
    sprite_.setTexture(texture_);
    sprite_.setTextureRect(sf::IntRect(0, 0, width_, height_));
}

void Player::update(float time)
{
    switch (direction_)
    {
        case 0: dx_ = speed_;   dy_ = 0;        break;
        case 1: dx_ = -speed_;  dy_ = 0;        break;
        case 2: dx_ = 0;        dy_ = speed_;   break;
        case 3: dx_ = 0;        dy_ = -speed_;  break;

        default: std::cout << "Direction is out of bound\n";
    }

    x_ += dx_ * time;
    y_ += dy_ * time;

    speed_ = 0;
    sprite_.setPosition(x_,y_);

    interactionWithMap();

    if (health_ <= 0){
        life_ = false;
        speed_ = 0;
    }
}

void Player::interactionWithMap()
{
    for (int i = y_ / 32; i < (y_ + height_) / 32; i++)
    {
        for (int j = x_ / 32; j < (x_ + width_) / 32; j++)
        {
            if (TileMap[i][j] == '0')
            {
                if (dy_ > 0) {
                    y_ = i * 32 - height_;
                }
                if (dy_ < 0) {
                    y_ = i * 32 + 32;
                }
                if (dx_ > 0) {
                    x_ = j * 32 - width_;
                }
                if (dx_ < 0) {
                    x_ = j * 32 + 32;
                }
            }

            if (TileMap[i][j] == 's') {
                score_++;
                TileMap[i][j] = ' ';
            }

            if (TileMap[i][j] == 'f') {
                health_ -= 40;
                TileMap[i][j] = ' ';
            }

            if (TileMap[i][j] == 'h') {
                health_ += 20;
                TileMap[i][j] = ' ';
            }
        }
    }
}

float Player::getX() { return x_; }
float Player::getY() { return y_; }
