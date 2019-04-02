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
    explicit ComputerPlayer(int playerNumber);
    Move makeMove(GomokuMainBoard &bord, APlayer *player_1, APlayer *player_2) override ;
};

#endif //GOMOKU_AIPLAYER_HPP
