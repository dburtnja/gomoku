//
// Created by mirexcool on 29.03.2019.
//



#ifndef GOMOKU_HUMANPLAYER_HPP
#define GOMOKU_HUMANPLAYER_HPP

#include "MainHeader.hpp"
#include "APlayer.hpp"
#include "GomokuMainBoard.hpp"

class HumanPlayer : public APlayer
{
public:
    HumanPlayer(int playerNumber, int playerSymbol);

protected:
    Move _makeMove(GomokuMainBoard &board, APlayer *otherPlayer) override;
};

#endif //GOMOKU_HUMANPLAYER_HPP
