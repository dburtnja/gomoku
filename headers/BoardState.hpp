//
// Created by Mirex on 10.08.2018.
//

#ifndef GOMOKU_BOARDSTATE_HPP
#define GOMOKU_BOARDSTATE_HPP

#include "MainHeader.hpp"

class BoardState {
public:
    BoardState();
    BoardState(int (& board)[19][19]);
    ~BoardState();
    int board[19][19];
};


#endif //GOMOKU_BOARDSTATE_HPP
