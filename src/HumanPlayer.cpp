//
// Created by mirexcool on 29.03.2019.
//

#include "../headers/HumanPlayer.hpp"

HumanPlayer::HumanPlayer(int playerNumber) : APlayer(playerNumber, HUMAN_PLAYER){
}

Move HumanPlayer::makeMove(GomokuMainBoard &board, APlayer *player_1, APlayer *player_2)
{

    Move oneMove;
    oneMove.y = 0;

    return oneMove;
}
