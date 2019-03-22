//
// Created by denys on 22.03.19.
//

#include "../headers/Coordinates.hpp"

Coordinates::Coordinates() = default;

Coordinates::Coordinates(int x, int y) : _x(x), _y(y) {}

Coordinates::~Coordinates() = default;

int Coordinates::getX() {
    return this->_x;
}

int Coordinates::getY() {
    return this->_y;
}