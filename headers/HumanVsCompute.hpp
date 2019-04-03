//
// Created by denys on 03.04.19.
//

#ifndef GOMOKU_HUMANVSCOMPUTE_HPP
#define GOMOKU_HUMANVSCOMPUTE_HPP


#include "APlayer.hpp"

class HumanVsCompute : public APlayer {
public:
    HumanVsCompute(int playerNumber, int playerSymbol);

protected:
    Move _makeMove(GomokuMainBoard &board, APlayer *otherPlayer) override;
};


#endif //GOMOKU_HUMANVSCOMPUTE_HPP
