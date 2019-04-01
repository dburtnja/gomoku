//
// Created by mirex on 04.07.2018.
//

#ifndef GOMOKUMAINBOARD_HPP
#define GOMOKUMAINBOARD_HPP

#include "MainHeader.hpp"

#include "AvailableSpot.hpp"
#include "BoardState.hpp"
#include <list>
#include "Coordinates.hpp"


class APlayer;

class GomokuMainBoard {
    public:
        GomokuMainBoard();
        GomokuMainBoard(const GomokuMainBoard & toCopy);
        ~GomokuMainBoard();
        GomokuMainBoard & operator = (const GomokuMainBoard & rhs);
        int getValue(int x, int y);
        bool checkEmpty(int x, int y);
        void setValue(int x,int y, int c);
        std::string toString();

        bool win(int, int);
        bool draw();
        int check_for_capture( int x_cor, int y_cor, APlayer * attack, APlayer * feed, bool, std::vector<Coordinates*> &);


        bool rowOfTwo(int, int, int, int, bool, std::vector<Coordinates*> &);
        bool columnOfTwo(int, int, int, int, bool, std::vector<Coordinates*> &);
        bool mainDiagnolOfTwo(int, int, int, int, bool, std::vector<Coordinates*> &);
        bool reverseDiagnolOfTwo(int, int, int, int, bool, std::vector<Coordinates*> &);

        bool rowOfFive(int, int);
        bool columnOfFive(int, int);
        bool mainDiagnolOfFive(int, int);
        bool reverseDiagnolOfFive(int, int);


        bool putStoneOnBoard(int x, int y, int plyaer, int depth);
        void addNewSpots(int x, int y, int depth);

        void clearStoneOnBoard(int x, int y);
        void dellOldSpots(int x, int y);

        bool checkForSameSpot(int x, int y);
        void deleteUsedSpot(int x, int y);
        int board[GOMOKU_BOARD_SIZE][GOMOKU_BOARD_SIZE];
        void printBoard();

        //int checkVictoryBoard(int (& board)[GOMOKU_BOARD_SIZE][GOMOKU_BOARD_SIZE]);

        std::vector<AvailableSpot*> availablespots;
        std::vector<BoardState *> boardHash;


        int getBoardSize();

        int getPlayer();

        int getPlayer(int move);

        void setMoveCounter(int move);

        std::list<Coordinates> * getPlacedCoordinates();

    private:
        unsigned int _boardSize;
        int _players[2];
        int _move;
};

#endif

