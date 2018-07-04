//
// Created by mirex on 04.07.2018.
//



#ifndef GOMOKU_GOMOKUMAINBOARD_HPP
#define GOMOKU_GOMOKUMAINBOARD_HPP

#include "MainHeader.hpp"
#include "SingleStone.hpp" //не бачить цей хедер з MainHeader.hpp ??????

class GomokuMainBoard {
public:
    GomokuMainBoard();
    GomokuMainBoard(const GomokuMainBoard & toCopy);
    ~GomokuMainBoard();
    GomokuMainBoard & operator = (const GomokuMainBoard & rhs);

    void putStoneOnBoard(SingleStone & newStone);

private:
    unsigned int _boardSize;
    // треба поінтер зробити на ліст з обєктами SingelStone, putStoneOnBoard() буде кидати новий
    // камінь по заданим координатам з номером гравця
};


#endif //GOMOKU_GOMOKUMAINBOARD_HPP
