//
// Created by mirex on 04.07.2018.
//

#include "../headers/MainHeader.hpp"

SingleStone::SingleStone() //:
//    _xCord(NULL),
//    _yCord(NULL)
    //_Player(0)
{}

SingleStone::SingleStone(unsigned int Player, unsigned int CordX, unsigned int CordY):
    _xCord(CordX),
    _yCord(CordY),
    _Player(Player)
{}

SingleStone::~SingleStone() {}

SingleStone::SingleStone(const SingleStone &toCopy) {
    * this = toCopy;
}

SingleStone& SingleStone::operator=(const SingleStone &rhs) {
    this->_xCord = rhs._xCord;
    this->_yCord = rhs._yCord;
    this->_Player = rhs._Player;
    return (* this);
}

void SingleStone::setCordX(unsigned int X) { this->_xCord = X; }

void SingleStone::setCordY(unsigned int Y) { this->_yCord = Y; }

unsigned int SingleStone::getPlayer() { return this->_Player; }

unsigned int SingleStone::getCordX() { return this->_xCord; }

unsigned int SingleStone::getCordY() { return this->_yCord; }