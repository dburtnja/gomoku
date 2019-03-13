//
// Created by Mirex on 10.08.2018.
//

#include "../headers/BoardState.hpp"

BoardState::BoardState() {}

BoardState::BoardState(int (& board)[19][19]) {
    for (int i = 0; i < 19; ++i) {
        for (int j = 0; j < 19; ++j) {
            this->board[i][j] = board[i][j];
        }
    }
}

BoardState::~BoardState() {}