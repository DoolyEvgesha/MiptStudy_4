#ifndef MYGAME_ENTITY_H
#define MYGAME_ENTITY_H

#include <SFML/Graphics.hpp>
//#include "level.h"
#include "game/game.h"

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
//all the parameters, that living creatures in this
//game have
class physEntity{
public:
    physEntity() = default;
    physEntity(float x, float y, float speed, float collide_area);
    float           getX();
    float           getY();
    int             getDir();
    float           getCollidArea();
    sf::Vector2f    getLocation();

protected://so that the child class can see this parameters and others don't
    int             move(float dx, float dy);
    sf::Vector2f    bodyCoord_;
    float           collideArea_;
    float           speed_;
    int             direction_;
};

physEntity::physEntity(float x, float y, float speed, float collide_area):
    bodyCoord_      (sf::Vector2f(x, y)),
    collideArea_    (collide_area),
    speed_          (speed),
    direction_      (1)
{}

float           physEntity::getX()          { return bodyCoord_.x;  }
float           physEntity::getY()          { return bodyCoord_.y;  }
int             physEntity::getDir()        { return direction_;    }
float           physEntity::getCollidArea() { return collideArea_;  }
sf::Vector2f    physEntity::getLocation()   { return bodyCoord_;    }

int physEntity::move(float dx, float dy) { bodyCoord_.x += dx; bodyCoord_.y += dy; }
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

//this is responsible for all textures
//images, frames, sprites and so on (graphics)
class visualEntity{
protected:
    sf::Vector2f        sprite_coord_;
    float               animation_speed_;
    float               current_frame_;
    int                 width_;
    int                 height_;
    int                 frame_size_;
    const sf::Texture * texture_;
    sf::Sprite          sprite_;

public:
    visualEntity() = default;
    visualEntity(float x, float y, float animation_speed, int w, int h,
            int frame_size, const sf::Texture * texture);

    int move(float dx, float dy);
    void changeTexture(const sf::Texture *texture, int width, int height, int frameAmount, float animation_speed);
    int changeFramePosition(int direction);
    int changeFrame(float time);
    int stopFrame(int direction);
};

visualEntity::visualEntity(float x, float y, float animation_speed, int w, int h, int frame_size,
        const sf::Texture *texture):
        sprite_coord_       (sf::Vector2f(x, y)),
        animation_speed_    (animation_speed),
        current_frame_      (0),
        width_              (w),
        height_             (h),
        frame_size_         (frame_size),
        texture_            (texture),
        sprite_             (*texture, sf::IntRect(0, 0, w, h))
{}

int visualEntity::move(float dx, float dy)
{
    sprite_coord_ += sf::Vector2f(dx, dy);
    sprite_.setPosition(sprite_coord_);
}

int visualEntity::changeFrame(float time)
{
    current_frame_ += time * animation_speed_;
    if(current_frame_ > frame_size_)
        current_frame_ = 0;
}

int visualEntity::stopFrame(int direction)
{
    sprite_.setTextureRect(sf::IntRect(0, direction * height_, width_, height_));
}

int visualEntity::changeFramePosition(int dir)
{
    sprite_.setTextureRect(sf::IntRect(width_ * (int)current_frame_, height_ * dir,
            width_, height_));
}

void visualEntity::changeTexture(const sf::Texture *texture, int width, int height, int frame_size,
                                 float animation_speed)
{
    current_frame_      = 0;
    move(width_/2 - width/2, height_/2 - height/2);
    texture_            = texture;
    width_              = width;
    height_             = height;
    sprite_.setTexture(*texture_);
    frame_size_         = frame_size;
    animation_speed_    = animation_speed;

}
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
class Entity : public visualEntity, public physEntity
{
public:/*
    float       dx_;
    float       dy_;
    float       x_;
    float       y_;
    int         width_;
    int         height_;
    float       speed_;
    float       moveTimer;
    bool        life_;
    bool        isMoved_;
    bool        onGround_;
    int         health_;
    sf::String  name_;
    //sf::Texture texture_;
    const sf::Texture * texture_;
    sf::Sprite  sprite_;*/
    //Entity(const sf::Texture * , float, float, int, int, sf::String);
    Entity(float x, float y, int text_width, int text_height, float speed, float animation_speed,
            const sf::Texture *anim_texture, int frame_size, int type, float collide_area);
    virtual void update(float time) = 0;

protected:
    bool            is_alive_;
    bool            state_;
    int             type_;
    sf::Vector2f    direction_;
};

Entity::Entity(float x, float y, int text_width, int text_height, float speed, float animation_speed,
               const sf::Texture *anim_texture, int frame_size, int type, float collide_area):
        physEntity  (x + (float)text_width / 2, y + (float)text_height / 2, speed, collide_area),
        visualEntity(x, y, animation_speed, text_width, text_height, frame_size, anim_texture),
        type_       (type),
        direction_  (sf::Vector2f(0, 0)),
        state_      (true),
        is_alive_   (true)
{}

/*Entity::Entity(const sf::Texture * animation_texture, float X, float Y, int W, int H, sf::String Name):
        dx_         (0),
        dy_         (0),
        x_          (X),
        y_          (Y),
        width_      (W),
        height_     (H),
        speed_      (0),
        moveTimer   (0),
        life_       (true),
        isMoved_    (false),
        onGround_   (false),
        health_     (100),
        name_       (Name),
        texture_    (animation_texture)

{
    //texture_.loadFromImage(image);
    sprite_.setTexture(*texture_);
    sprite_.setOrigin(width_/2, height_/2);

}*/



#endif //MYGAME_ENTITY_H
