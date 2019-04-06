//
// Created by denys on 22.03.19.
//

#ifndef GOMOKU_COORDINATES_HPP
#define GOMOKU_COORDINATES_HPP

#include "MainHeader.hpp"

class Coordinates {

public:
    Coordinates();
    Coordinates(int x, int y, int player);
    ~Coordinates();

    int getX();
    int getY();
    void setX(int x);
    void setY(int x);
    int getPlayer();

private:
    int _x;
    int _y;
    int _player;
};

struct Move{
    int x;
    int y;

    std::vector<Coordinates*> coordinatesList;
    double moveTime;
    int capturePlayer_1;
    int capturePlayer_2;
    int moveCounter;
};



#endif //GOMOKU_COORDINATES_HPP
