#ifndef MYGAME_PLAYER_H
#define MYGAME_PLAYER_H

class Player{
private:

public:
    Player();
    ~Player();

    float x, y, w, h, dx, dy, speed ; //координаты игрока х и у, высота ширина, ускорение (по х и по у), сама скорость
    int dir ; //направление (direction) движения игрока
    sf::String File; //файл с расширением
    sf::Image image;//сфмл изображение
    sf::Texture texture;//сфмл текстура
    sf::Sprite sprite;//сфмл спрайт

};

Player::Player() {}

Player::~Player() {}

#endif //MYGAME_PLAYER_H
