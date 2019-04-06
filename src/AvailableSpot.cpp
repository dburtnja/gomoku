//
// Created by Mirex on 31.07.2018.
//

#include "../headers/MainHeader.hpp"
#include "../headers/AvailableSpot.hpp"


AvailableSpot::AvailableSpot() : _x(0), _y(0) {}

AvailableSpot::AvailableSpot(int x, int y) : _x(x),_y(y) {}

AvailableSpot::~AvailableSpot() {
}

AvailableSpot::AvailableSpot(const AvailableSpot &toCopy) {
    * this = toCopy;
}

AvailableSpot& AvailableSpot::operator=(const AvailableSpot &rhs) {
    this->_x = rhs._x;
    this->_y = rhs._y;
    this->p1_score = rhs.p1_score;

    return (* this);
}

int  AvailableSpot::getX() {
    return this->_x;
}

int  AvailableSpot::getY() {
    return this->_y;
}
void AvailableSpot::setX(int x) {
    this->_x = x;
}
void AvailableSpot::setY(int y) {
    this->_y = y;
}