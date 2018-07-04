//
// Created by mirex on 04.07.2018.
//

#include "MainHeader.hpp"

GomokuMainBoard::GomokuMainBoard() :
        _boardSize (GOMOKU_GOMOKUMAINBOARD_HPP)
{}

GomokuMainBoard::GomokuMainBoard(const GomokuMainBoard & toCopy) {
    * this = toCopy;
}

GomokuMainBoard & GomokuMainBoard::operator = (const GomokuMainBoard & rhs) {
    this->_boardSize = rhs._boardSize;
    return (* this);
}
