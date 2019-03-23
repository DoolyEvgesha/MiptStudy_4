#ifndef MYGAME_PLAYER_H
#define MYGAME_PLAYER_H

class Player{
private:

public:
    Player();
    ~Player();

    float x, y, w, h, dx, dy, speed ;
    int dir ;
    sf::String File;
    sf::Image image;
    sf::Texture texture;
    sf::Sprite sprite;

};

Player::Player() {}

Player::~Player() {}

#endif //MYGAME_PLAYER_H
