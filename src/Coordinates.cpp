//
// Created by denys on 22.03.19.
//

#include "../headers/Coordinates.hpp"

Coordinates::Coordinates() = default;

Coordinates::Coordinates(int x, int y, int player) : _x(x), _y(y), _player(player) {}

Coordinates::~Coordinates() = default;

int Coordinates::getX() {
    return this->_x;
}

int Coordinates::getY() {
    return this->_y;
}

void Coordinates::setX(int x) {
    this->_x = x;
}

void Coordinates::setY(int y) {
    this->_y = y;
}

int Coordinates::getPlayer() {
    return this->_player;
}