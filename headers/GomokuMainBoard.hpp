//
// Created by mirex on 04.07.2018.
//



#ifndef GOMOKU_GOMOKUMAINBOARD_HPP
#define GOMOKU_GOMOKUMAINBOARD_HPP

#include "MainHeader.hpp"
#include "SingleStone.hpp" //не бачить цей хедер з MainHeader.hpp ??????
#include "AvailableSpot.hpp" //не бачить цей хедер з MainHeader.hpp ??????

class GomokuMainBoard {
public:
    GomokuMainBoard();
    GomokuMainBoard(const GomokuMainBoard & toCopy);
    ~GomokuMainBoard();
    GomokuMainBoard & operator = (const GomokuMainBoard & rhs);

    //void putStoneOnBoard(SingleStone * newStone);
    void putStoneOnBoard(int x, int y, int plyaer);
    void addNewSpots(int x, int y);

    void clearStoneOnBoard(int x, int y);
    void dellOldSpots(int x, int y);

    bool checkForSameSpot(int x, int y);
    void deleteUsedSpot(int x, int y);
    int board[GOMOKU_BOARD_SIZE][GOMOKU_BOARD_SIZE];
    void printBoard();

    int checkVictoryBoard(int (& Board)[GOMOKU_BOARD_SIZE][GOMOKU_BOARD_SIZE]);


    std::vector<AvailableSpot*> availablespots;

private:
    unsigned int _boardSize;
};


#endif //GOMOKU_GOMOKUMAINBOARD_HPP
