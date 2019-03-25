//
// Created by denys on 22.03.19.
//

#ifndef GOMOKU_COORDINATES_HPP
#define GOMOKU_COORDINATES_HPP


class Coordinates {

public:
    Coordinates();
    Coordinates(int x, int y, int player);
    ~Coordinates();

    int getX();
    int getY();
    int getPlayer();

private:
    int _x;
    int _y;
    int _player;
};


#endif //GOMOKU_COORDINATES_HPP
