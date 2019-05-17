#ifndef MYGAME_PLAYER_H
#define MYGAME_PLAYER_H

#include <algorithm>
#include "../map/map.h"
#include "../entity.h"
#include "../game/game.h"

const int   JUMP_SPEED          = 7;

const int   player_w            = 50;
const int   player_h            = 50;
const float player_s            = 0.2;
const float player_animation_s  = 0.04;
const int   move_frame_amount   = 8;
const float player_collide_area = 25;

class Player : public Entity{
public:
    Player(float x, float y, int w, int h, float speed, float animation_speed, int move_frame_amount,
           float collideArea, const sf::Texture *move_animation_texture);

    int             getHealth      ();
    sf::Vector2f    getViewCoord   ();
    bool            getOnGround    ();
    float           getDirX        ();
    float           getDirY        ();
    bool            isOnDrug_      ()               { return onDrug_; };

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
    bool             onDrug_;
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
                dir_.y = initialJumpSpeed_;
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
                dir_.y = initialJumpSpeed_;
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
                dir_.y = initialJumpSpeed_;
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
            auto map = dynamic_cast<Map *> (entity);

            //float next_step_y = (dir_.y < 0) ? (bodyCoord_.y + dir_.y - height_/2) : (bodyCoord_.y + dir_.y + height_/2);
            //float next_step_x = (dir_.x < 0) ? (bodyCoord_.x + dir_.x - width_/2)  : (bodyCoord_.x + dir_.x + width_ /2);

            float next_step_x, next_step_y;
            if(dir_.x < 0)
                next_step_x = bodyCoord_.x + dir_.x - width_/2;
            else if (dir_.x > 0)
                next_step_x = bodyCoord_.x + dir_.x + width_ /2;
            else if(dir_.x == 0)
                next_step_x = bodyCoord_.x;

            if(dir_.y < 0)
                next_step_y = bodyCoord_.y + dir_.y - height_/2;
            else if(dir_.y > 0)
                next_step_y = bodyCoord_.y + dir_.y + height_/2;
            else if(dir_.y == 0 && TileMap[int((bodyCoord_.y + height_/2)/TILE_SIZE)][int(next_step_x / TILE_SIZE)] != '0')
            {
                dir_.y = speed_ * 8;
                next_step_y = bodyCoord_.y + dir_.y + height_/2; //gravitation (falling after stepping from a cliff)
            }
            else
                next_step_y = bodyCoord_.y;

            int j = (next_step_y / TILE_SIZE);
            int i = (next_step_x / TILE_SIZE);

            //if it steps on spikes, it dies
            if(TileMap[j][i] == 's' || TileMap[int(bodyCoord_.y / TILE_SIZE)][i] == 's')
            {
                health_ = 0;
                state_  = false;
            }

            //if the player eats a drug(mushroom)
            if(TileMap[j][i] == 'b' || TileMap[int(bodyCoord_.y / TILE_SIZE)][i] == 'b')
            {
                if(dir_.y > 0 && onGround_ == false)
                    view_.rotate(0.1);
                dir_.y = 0;
            }

            if(TileMap[j][i] == 'g' || TileMap[int(bodyCoord_.y / TILE_SIZE)][i] == 'g')
            {
                if(dir_.y > 0 && onGround_ == false)
                    view_.rotate(-0.1);
                dir_.y = 0;
            }

            if(TileMap[j][i] == 'm' || TileMap[int(bodyCoord_.y / TILE_SIZE)][i] == 'm')
            {
                onDrug_ = true;
                health_ = 0;
                state_  = false;
                dir_.y  = 0;
            }


            if((dir_.y == 0) && (TileMap[j][i] != '0'))
                dir_.y = 0.1;

            if(TileMap[j][i] == '0')
            {
                if(dir_.y > 0)
                {
                    /*bodyCoord_.y        = (j - 0.1) * TILE_SIZE;
                    sprite_coord_.y     = (j - 0.1) * TILE_SIZE - Player::height_;*/
                    dir_.y              = TILE_SIZE * j - bodyCoord_.y - height_ / 2;
                    dir_.y              = 0;
                    onGround_           = true;
                    move();
                }
                else if(dir_.y < 0 && dir_.x == 0)
                {
                    dir_.y              = TILE_SIZE * (j + 1) - bodyCoord_.y + height_ / 2;
                    move();
                    /*bodyCoord_.y        = j * TILE_SIZE + TILE_SIZE;
                    dir_.y              = - dir_.y;*/
                }
                else if(dir_.y < 0 && dir_.x > 0)
                {
                    dir_.y              = TILE_SIZE * (j + 1) - bodyCoord_.y + height_ / 2;
                    dir_.x              = TILE_SIZE * i - bodyCoord_.x - width_ / 2;
                    move();
                }
                else if(dir_.y == 0 && dir_.x < 0)
                {
                    dir_.x              = TILE_SIZE * (i + 1) - bodyCoord_.x + width_ / 2;
                    move();
                    //bodyCoord_.x        = (i + 1) * TILE_SIZE;
                    //sprite_coord_.x     = (i + 1) * TILE_SIZE + Player::width_ / 2;
                }
                else if(dir_.y == 0 && dir_.x > 0)
                {
                    dir_.x              = TILE_SIZE * i - bodyCoord_.x - width_ / 2;
                    move();
                }
            }

            sf::Vector2f a;
            a = bodyCoord_;

            if (bodyCoord_.x    < view_.getSize().x / 2)
                a.x             = view_.getSize().x / 2;

            if (bodyCoord_.x    > map->getWidth() * TILE_SIZE - view_.getSize().x / 2)
                a.x             = map->getWidth() * TILE_SIZE - view_.getSize().x / 2;

            if (bodyCoord_.y    < view_.getSize().y / 2)
                a.y             = view_.getSize().y / 2;

            if (bodyCoord_.y    > map->getHeight() * TILE_SIZE - view_.getSize().y / 2)
                a.y             = map->getHeight() * TILE_SIZE - view_.getSize().y / 2;

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
    onGround_    (true),
    onDrug_      (false)

{}

int             Player::getHealth   ()                         { return health_; }
sf::Vector2f    Player::getViewCoord()                         { return viewCoord_; }
void            Player::draw        (sf::RenderWindow &window) { window.draw(sprite_);}
bool            Player::getOnGround ()                         { return onGround_; }
float           Player::getDirX     ()                         { return dir_.x; }
float           Player::getDirY     ()                         { return dir_.y; }

#endif //MYGAME_PLAYER_H
