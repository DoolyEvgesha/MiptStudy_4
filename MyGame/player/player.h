#ifndef MYGAME_PLAYER_H
#define MYGAME_PLAYER_H

#include "../map/map.h"
#include "../game/object.h"

/*class Player : protected Object, GraphObject{
private:

    sf::Vector2f view_coord_;

public:
    Player() = delete;

};*/

class Player{

public:
    float       x_;
    float       y_;
    float       width_;
    float       height_;
    float       dx_;
    float       dy_;
    float       speed_;
    int         direction_;
    sf::String  File_;
    sf::Image   image_;
    sf::Texture texture_;
    sf::Sprite  sprite_;

    Player(sf::String F, float X, float Y, float W, float H);

    void update         (float time);
    void interactionWithMap();
    inline float getX   ();
    inline float getY   ();
};

Player::Player(const sf::String F, float X, float Y, float W, float H):
    x_          (X),
    y_          (Y),
    width_      (W),
    height_     (H),
    dx_         (0),
    dy_         (0),
    speed_      (0),
    direction_  (0),
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
                x_ = 300;
                y_ = 300;
                TileMap[i][j] = ' ';
            }
        }
    }
}

float Player::getX() { return x_; }
float Player::getY() { return y_; }

#endif //MYGAME_PLAYER_H
