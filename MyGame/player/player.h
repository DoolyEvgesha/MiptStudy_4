#ifndef MYGAME_PLAYER_H
#define MYGAME_PLAYER_H

#include "../map/map.h"
#include "../view/view.h"
#include "../entity.h"
#include "../game/game.h"

const int   player_w            = 100;
const int   player_h            = 100;
const float player_s            = 0.4;
const float player_animation_s  = 0.04;
const int   move_frame_amount   = 8;
const float player_collide_area = 1000;

class Player : public Entity{
public:
    Player(float x, float y, int w, int h, float speed, float animation_speed, int move_frame_amount,
           float collideArea, const sf::Texture *move_animation_texture);

    int  getHealth              ();
    sf::Vector2f getViewCoord   ();

    sf::View     view_;

    void draw                   (sf::RenderWindow &window)              override;
    void update                 (float time, const sf::Event &event)    override;
    int  getDirection           (const sf::Event& event)                override;
    int  move                   ()                                      override;
    int  collide                (Entity * entity)                       override;

private:
    int                         health_;
    sf::Vector2f                viewCoord_;

};

//TODO: consider directions and maybe speed the character when he is falling by "S"
int Player::getDirection(const sf::Event &event)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        return LEFT_DIR;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        return UP_DIR;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
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
        case RIGHT_DIR:
            changeFramePosition(RIGHT_DIR);
            dir_.x      = speed_ * time;
            direction_  = RIGHT_DIR;
            break;

        case LEFT_DIR:
            changeFramePosition(LEFT_DIR);
            dir_.x      = - speed_ * time;
            direction_  = LEFT_DIR;
            break;

        case UP_DIR:
            changeFramePosition(UP_DIR);
            dir_.y      = - speed_ * time;
            direction_  = UP_DIR;
            break;
        default:
            stopFrame(direction_);
            break;

    }
    //TODO:write the proper exit
    exit(EXIT_FAILURE);
}

int Player::collide(Entity *entity)
{
    switch(entity->getType())
    {
        case MAP:
            //TODO:write interaction with map(lives, stones, etc)
            break;

        case EASY_ENEMY:
            if(collideArea_ + entity->getCollideArea() > distanceModule(getLocation(), entity->getLocation()))
            {
                dir_.x = 0;
                dir_.y = 0;
                //TODO:do adjustments to sprite if he is hit by an enemy
                //maybe he dies
                //health--;
                //if(health_ < 0)
                   // state_ = false;
            }
            break;

        default:
            break;
    }

}


Player::Player(float x, float y, int w, int h, float speed, float animation_speed, int move_frame_amount,
       float collideArea, const sf::Texture *move_animation_texture):
    Entity       (x, y, w, h, speed, animation_speed, move_animation_texture, move_frame_amount, PLAYER, collideArea),
    health_      (100),
    viewCoord_   (physEntity::bodyCoord_)

{}

int             Player::getHealth   ()                         { return height_; }
sf::Vector2f    Player::getViewCoord()                         { return viewCoord_; }
void            Player::draw        (sf::RenderWindow &window) { window.draw(sprite_); }

#endif //MYGAME_PLAYER_H
