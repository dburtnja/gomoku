//
// Created by denys on 22.03.19.
//

#ifndef GOMOKU_COORDINATES_HPP
#define GOMOKU_COORDINATES_HPP


class Coordinates {

public:
    Coordinates();
    Coordinates(int x, int y);
    ~Coordinates();

    int getX();
    int getY();

private:
    int _x;
    int _y;
};


#endif //GOMOKU_COORDINATES_HPP
