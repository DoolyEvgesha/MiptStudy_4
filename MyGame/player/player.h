#ifndef MYGAME_PLAYER_H
#define MYGAME_PLAYER_H

#include "../map/map.h"
#include "../view/view.h"
#include "../entity.h"
#include "Enemy.h"
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Player : public Entity{
public:
    enum{left, right, up, down, jump, stay} state_;
    int playerScore_;

    Player(sf::Image &image, float X, float Y, int W, int H, sf::String Name);

    void update                 (float time);
    void checkCollisionWithMap  (float Dx, float Dy);
    void control                ();
};


Player::Player(sf::Image &image, float X, float Y, int W, int H, sf::String Name):
    Entity            (image, X, Y, W, H, Name),
    playerScore_      (0),
    state_            (stay)

{
    if(name_ == "Player1")
        sprite_.setTextureRect(sf::IntRect(4, 19, width_, height_));
}

void Player::update(float time)
{
    control();
    switch (state_)
    {
        case right: dx_ =   speed_;     break;
        case left:  dx_ =   -speed_;    break;
        case up:                        break;
        case down:  dx_ =   0;          break;
        case jump:                      break;
        case stay:                      break;

        default: std::cout << "Direction is out of bound\n";
    }

    x_ += dx_ * time;
    checkCollisionWithMap(dx_, 0);
    y_ += dy_ * time;
    checkCollisionWithMap(0, dy_);
    sprite_.setPosition(x_ + width_/2, y_ + height_/2);
    if(health_ <= 0) {life_= false;}
    if(!isMoved_) speed_ = 0;

    if(life_)
        setPlayerCoordForView(x_, y_);

    dy_ += 0.0015 * time;

}

void Player::checkCollisionWithMap(float Dx, float Dy)
{
    for (int i = y_ / 32; i < (y_ + height_) / 32; i++)
    {
        for (int j = x_ / 32; j < (x_ + width_) / 32; j++)
        {
            if (TileMap[i][j] == '0')
            {
                if (Dy > 0) {
                    y_ = i * 32 - height_;
                    dy_ = 0;
                    onGround_ = true;
                }
                if (Dy < 0) {
                    y_ = i * 32 + 32;
                    dy_ = 0;
                }
                if (Dx > 0) {
                    x_ = j * 32 - width_;
                }
                if (Dx < 0) {
                    x_ = j * 32 + 32;
                }
            }
        }
    }
}

void Player::control()
{
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left))) {
        state_ = left;
        speed_ = 0.1;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        state_ = right;
        speed_ = 0.1;
    }


    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && onGround_) {
        state_ = jump;
        dy_ = -0.6;
        onGround_ = false;
    }

    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down))) {
        state_ = down;
    }
}


#endif //MYGAME_PLAYER_H
