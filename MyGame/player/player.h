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
    Player(float x, float y, int w, int h, float speed, float animation_speed, int move_frame_amount,
           float collideArea, const sf::Texture *move_animation_texture);

    void checkCollisionWithMap  (float Dx, float Dy);
    void control                ();
    int  getHealth              ();
    sf::Vector2f getViewCoord   ();
    sf::Vector2f getView        ();

    sf::View     view_;

    void draw                   (sf::RenderWindow &window)              override;
    void update                 (float time, const sf::Event &event)    override;
    int  getDirection           (const sf::Event& event)                override;
    int  move                   ()                                      override;
    int collide                 (Entity * entity)                       override;
private:
    int                         health_;
    sf::Vector2f                viewCoord_;

};

//TODO: consider directions and maybe speed the character when he is falling by "S"
int Player::getDirection(const sf::Event &event)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        return LEFT_DIR;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        return UP_DIR;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        return RIGHT_DIR;
   /* if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        return _DIR;*/
   //TODO: rethink the way to get out if the problem occurs
    exit(EXIT_FAILURE);
}

int Player::move()
{
    Entity::move();
    view_.setCenter(viewCoord_);
}

void Player::update(float time, const sf::Event &event)
{
    sprite_.setColor(sf::Color::White);
    changeFrame(time);

    dir_.x = 0;
    dir_.y = 0;

    switch(getDirection(event))
    {
        case RIGHT_DIR
        {
            changeFramePosition(RIGHT_DIR);
            dir_.x      = speed_ * time;
            direction_  = RIGHT_UP;
            break;
        }
        case LEFT_DIR
        {
            changeFramePosition(LEFT_DIR);
            dir_.x      = - speed_ * time;
            direction_  = LEFT_UP;
            break;
        }
        case UP_DIR
        {
            changeFramePosition(UP_DIR);
            dir_.y      = - speed_ * time;
            direction_  = UP_DIR;
            break;
        }
        default
        {
            stopFrame(direction_);
            break;
        }

    }
    return 0;
}


Player::Player(float x, float y, int w, int h, float speed, float animation_speed, int move_frame_amount,
       float collideArea, const sf::Texture *move_animation_texture):
    Entity       (x, y, w, h, speed, animation_speed, move_animation_texture, move_frame_amount, PLAYER, collideArea),
    health_      (100),
    viewCoord_   (physEntity::bodyCoord_)

{}

int             Player::getHealth()     { return height_; }
sf::Vector2f    Player::getViewCoord()  { return viewCoord_; }
void Player::draw(sf::RenderWindow &window) { window.draw(sprite_); }

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
