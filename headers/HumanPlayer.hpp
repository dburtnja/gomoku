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
    explicit HumanPlayer(int playerNumber);
    Move makeMove(GomokuMainBoard &board, APlayer *player_1, APlayer *player_2) override ;
};

#endif //GOMOKU_HUMANPLAYER_HPP
