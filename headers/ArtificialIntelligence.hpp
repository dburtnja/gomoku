//
// Created by Mirex on 30.07.2018.
//



#pragma once

#include "MainHeader.hpp"
#include "Coordinates.hpp"
#include "GomokuMainBoard.hpp"

#include "APlayer.hpp"

class APlayer;

class ArtificialIntelligence {
    public:
        ArtificialIntelligence();
        ~ArtificialIntelligence();
        ArtificialIntelligence(const ArtificialIntelligence & toCopy);
        ArtificialIntelligence &operator = (const ArtificialIntelligence & rhs);

        std::unordered_map<std::string, int> hashMap;



        Move runAI(GomokuMainBoard & mainBoard, APlayer * player_1, APlayer * player_2) ;
        Move minmaxSearch(GomokuMainBoard & mainBoard, APlayer * player_1, APlayer * player_2);
        int minimaxAlphaBeta(GomokuMainBoard & mainBoard, int depth, bool player, int alpha, int beta , int x, int y, APlayer * player_1, APlayer * player_2);
        int evaluation(GomokuMainBoard &mainBoard, int isMax, int player_1);
        void insertToHashMap(GomokuMainBoard & board, int value);
        bool checkVisitedBoard(GomokuMainBoard & board);
        int getEvaluation (GomokuMainBoard & board);
        int getScoreByPatterns(GomokuMainBoard & board, int captured_nb, int player, int x, int y);
        int checkPatternWeight(std::string pattern, int player, int captured_nb);



        static int checkVictory(int (& Board)[GOMOKU_BOARD_SIZE][GOMOKU_BOARD_SIZE], int player);
        void printBoard(int (& Board)[GOMOKU_BOARD_SIZE][GOMOKU_BOARD_SIZE]);
        int maxSearch(GomokuMainBoard * mainBoard, int depth);
        int minSearch(GomokuMainBoard * mainBoard, int depth);

        int checkPatterns(int (& Board)[GOMOKU_BOARD_SIZE][GOMOKU_BOARD_SIZE], int x, int y);
        void deleteAvaibleSpotsVector(std::vector<AvailableSpot*> old, std::vector<AvailableSpot*> availablespots);
};


