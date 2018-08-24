//
// Created by Mirex on 30.07.2018.
//

#ifndef GOMOKU_ARTIFICIALINTELLIGENCE_H
#define GOMOKU_ARTIFICIALINTELLIGENCE_H


#include "MainHeader.hpp"

struct AiMove{
    int x;
    int y;
};

class ArtificialIntelligence {
    public:
        ArtificialIntelligence();
        ~ArtificialIntelligence();
        ArtificialIntelligence(const ArtificialIntelligence & toCopy);
        ArtificialIntelligence &operator = (const ArtificialIntelligence & rhs);
        static int checkVictory(int (& Board)[GOMOKU_BOARD_SIZE][GOMOKU_BOARD_SIZE], int player);
        void printBoard(int (& Board)[GOMOKU_BOARD_SIZE][GOMOKU_BOARD_SIZE]);
        void runAI(GomokuMainBoard * mainBoard, int player) ;
        AiMove minmaxSearch(GomokuMainBoard * mainBoard);
        int maxSearch(GomokuMainBoard * mainBoard, int depth);
        int minSearch(GomokuMainBoard * mainBoard, int depth);
};


#endif //GOMOKU_ARTIFICIALINTELLIGENCE_H
