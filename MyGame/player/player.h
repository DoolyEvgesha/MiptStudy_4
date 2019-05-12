#ifndef MYGAME_PLAYER_H
#define MYGAME_PLAYER_H

#include "../map/map.h"
#include "../view/view.h"
#include "../entity.h"
#include "../game/game.h"

const int JUMP_SPEED = 6;

const int   player_w            = 40;
const int   player_h            = 44;
const float player_s            = 0.4;
const float player_animation_s  = 0.04;
const int   move_frame_amount   = 3;
const float player_collide_area = 1000;

class Player : public Entity{
public:
    Player(float x, float y, int w, int h, float speed, float animation_speed, int move_frame_amount,
           float collideArea, const sf::Texture *move_animation_texture);

    int             getHealth      ();
    sf::Vector2f    getViewCoord   ();
    bool            getOnGround    ();
    float           getDirX        ();
    float           getDirY        ();

    sf::View        view_;

    void draw                   (sf::RenderWindow &window)              override;
    int  update                 (float time, const sf::Event &event)    override;
    int  getDirection           (const sf::Event& event)                override;
    int  move                   ()                                      override;
    int  collide                (Entity * entity)                       override;

private:
    int              health_;
    sf::Vector2f     viewCoord_;
    bool             onGround_;
    float            initialJumpSpeed_;
};


int Player::getDirection(const sf::Event &event)
{
    if(!onGround_) {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            return LEFT_JUMP;

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            return RIGHT_JUMP;

        return JUMP;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && onGround_)
    {
        onGround_   = false;
        initialJumpSpeed_ = -JUMP_SPEED;
        return JUMP;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        return LEFT_DIR;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        return RIGHT_DIR;

   return STAY;
}

int Player::move()
{
    Entity::move();
    view_.setCenter(viewCoord_);
    return 0;
}

int Player::update(float time, const sf::Event &event)
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

        case JUMP:
            changeFramePosition(JUMP);

            if(initialJumpSpeed_ < JUMP_SPEED) {
                dir_.y      = initialJumpSpeed_; //gravitation to the ground
                initialJumpSpeed_ += 0.1;
            }
            else{
                onGround_ = true;
            }

            direction_  = JUMP;
            break;

        case RIGHT_JUMP:
            changeFramePosition(RIGHT_JUMP);
            if(initialJumpSpeed_ < JUMP_SPEED) {
                dir_.y      = initialJumpSpeed_; //gravitation to the ground
                initialJumpSpeed_ += 0.1;
            }
            else{
                onGround_ = true;
            }

            dir_.x      = speed_ * time;
            direction_  = RIGHT_JUMP;
            break;

        case LEFT_JUMP:
            changeFramePosition(LEFT_JUMP);
            if(initialJumpSpeed_ < JUMP_SPEED) {
                dir_.y      = initialJumpSpeed_; //gravitation to the ground
                initialJumpSpeed_ += 0.1;
            }
            else{
                onGround_ = true;
            }

            dir_.x      = -speed_ * time;
            direction_  = LEFT_JUMP;
            break;

        default: //STAY
            stopFrame(direction_);
            break;

    }
    return 0;
}

int Player::collide(Entity *entity)
{
    switch(entity->getType()) {
        case MAP:
        {
            //TODO:write interaction with map(lives, stones, etc)
            auto map = dynamic_cast<Map *> (entity);

            if (bodyCoord_.x    < map->getTileSize()) {
                bodyCoord_.x    = map->getTileSize();
                sprite_coord_.x = map->getTileSize() - visualEntity::width_ / 2;
            }

            if (bodyCoord_.y    < 0.7 * map->getTileSize()) {
                bodyCoord_.y    = 0.7 * map->getTileSize();
                sprite_coord_.y = 0.7 * map->getTileSize() - Player::height_ / 2;
            }

            if (bodyCoord_.x    > map->getTileSize() * map->getWidth() - map->getTileSize()) {
                bodyCoord_.x    = map->getTileSize() * map->getWidth() - map->getTileSize();
                sprite_coord_.x = map->getTileSize() * map->getWidth() - map->getTileSize() - Player::width_ / 2;
            }

            if (bodyCoord_.y    > map->getHeight() * map->getTileSize() - 1.7 * map->getTileSize()) {
                bodyCoord_.y    = map->getHeight() * map->getTileSize() - 1.7 * map->getTileSize();
                sprite_coord_.y = map->getHeight() * map->getTileSize() - 1.7 * map->getTileSize() - Player::height_ / 2;
            }

            sf::Vector2f a;
            a = bodyCoord_;

            if (bodyCoord_.x    < view.getSize().x / 2)
                a.x             = view.getSize().x / 2;

            if (bodyCoord_.x    > map->getWidth() * TILE_SIZE - view.getSize().x / 2)
                a.x             = map->getWidth() * TILE_SIZE - view.getSize().x / 2;

            if (bodyCoord_.y    < view.getSize().y / 2)
                a.y             = view.getSize().y / 2;

            if (bodyCoord_.y    > map->getHeight() * TILE_SIZE - view.getSize().y / 2)
                a.y             = map->getHeight() * TILE_SIZE - view.getSize().y / 2;

            viewCoord_ = a;

            break;
        }
        case EASY_ENEMY:
            if(collideArea_ + entity->getCollideArea() > distanceModule(getLocation(), entity->getLocation()))
            {
                if((dir_.y > 0) && (!onGround_))
                {
                    dir_.y = - 0.2; //jump up after hitting an enemy
                }
                else{
                dir_.x = 0;
                dir_.y = 0;

                health_--;
                if(health_ < 0)
                    state_ = false;
                }
            }
            break;

        default:
            break;
    }
    return 0;
}


Player::Player(float x, float y, int w, int h, float speed, float animation_speed, int move_frame_amount,
       float collideArea, const sf::Texture *move_animation_texture):
    Entity       (x, y, w, h, speed, animation_speed, move_animation_texture, move_frame_amount, PLAYER, collideArea),
    health_      (100),
    viewCoord_   (physEntity::bodyCoord_),
    onGround_    (true)

{}

int             Player::getHealth   ()                         { return health_; }
sf::Vector2f    Player::getViewCoord()                         { return viewCoord_; }
void            Player::draw        (sf::RenderWindow &window) { window.draw(sprite_);}
bool            Player::getOnGround ()                         { return onGround_; }
float           Player::getDirX     ()                         { return dir_.x; }
float           Player::getDirY     ()                         { return dir_.y; }

#endif //MYGAME_PLAYER_H
