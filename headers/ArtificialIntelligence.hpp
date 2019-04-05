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
        int evaluation(GomokuMainBoard &mainBoard, int player_1);
        void checkSymbolsInColomns(GomokuMainBoard &mainBoard, int i, int j, int c, bool needMax,
                                   std::vector<int> & firstPlayerPattern, std::vector<int> & secondPlayerPattern);
        void checkSymbolsInRows(GomokuMainBoard &mainBoard, int i, int j, int c, bool needMax,
                               std::vector<int> & firstPlayerPattern, std::vector<int> & secondPlayerPattern);
        void checkSymbolsInMainDiaginal(GomokuMainBoard &mainBoard, int i, int j, int c, bool needMax,
                            std::vector<int> & firstPlayerPattern, std::vector<int> & secondPlayerPattern);
        void checkSymbolsInReverseDiaginal(GomokuMainBoard &mainBoard, int i, int j, int c, bool needMax,
                                    std::vector<int> & firstPlayerPattern, std::vector<int> & secondPlayerPattern);
};


