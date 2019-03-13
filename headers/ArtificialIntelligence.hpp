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

        std::unordered_map<std::string, int> hashMap;
        std::unordered_map<std::string, int> patternsHashMap;


    AiMove runAI(GomokuMainBoard & mainBoard, int player) ;
        AiMove minmaxSearch(GomokuMainBoard & mainBoard);
        int minimaxAlphaBeta(GomokuMainBoard & mainBoard, int depth, int player, int alpha, int beta , int x, int y);
        int evaluation(GomokuMainBoard & mainBoard, int  isMax);
        void insertToHashMap(GomokuMainBoard & board, int value);
        bool checkVisitedBoard(GomokuMainBoard & board);
        int getEvaluation (GomokuMainBoard & board);

        int getScoreByPatterns(GomokuMainBoard & board, int captured_nb, int player, int x, int y);
        int checkPatternWeight(std::string pattern, int player, int captured_nb);

    bool adjacentPlaced(int (& Board)[GOMOKU_BOARD_SIZE][GOMOKU_BOARD_SIZE] , int x, int y);




    static int checkVictory(int (& Board)[GOMOKU_BOARD_SIZE][GOMOKU_BOARD_SIZE], int player);
    void printBoard(int (& Board)[GOMOKU_BOARD_SIZE][GOMOKU_BOARD_SIZE]);
        int maxSearch(GomokuMainBoard * mainBoard, int depth);
        int minSearch(GomokuMainBoard * mainBoard, int depth);

        int checkPatterns(int (& Board)[GOMOKU_BOARD_SIZE][GOMOKU_BOARD_SIZE], int x, int y);


        //////

};


#endif //GOMOKU_ARTIFICIALINTELLIGENCE_H
