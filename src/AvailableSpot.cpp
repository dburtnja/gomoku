//
// Created by Mirex on 31.07.2018.
//

#include "../headers/MainHeader.hpp"


AvailableSpot::AvailableSpot() : _x(0), _y(0) {}

AvailableSpot::AvailableSpot(int x, int y) : _x(x),_y(y) {}

AvailableSpot::~AvailableSpot() {}

AvailableSpot::AvailableSpot(const AvailableSpot &toCopy) {
    * this = toCopy;
}

AvailableSpot& AvailableSpot::operator=(const AvailableSpot &rhs) {
    return (* this);
}

int const AvailableSpot::getX() {
    return this->_x;
}

int const AvailableSpot::getY() {
    return this->_y;
}