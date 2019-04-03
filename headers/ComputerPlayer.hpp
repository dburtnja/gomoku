//
// Created by mirexcool on 29.03.2019.
//



#ifndef GOMOKU_AIPLAYER_HPP
#define GOMOKU_AIPLAYER_HPP

#include "MainHeader.hpp"
#include "APlayer.hpp"
#include "GomokuMainBoard.hpp"

class ComputerPlayer : public APlayer
{
public:
    ComputerPlayer(int playerNumber, int playerSymbol);

protected:
    Move _makeMove(GomokuMainBoard &board, APlayer *otherPlayer) override;
};

#endif //GOMOKU_AIPLAYER_HPP
