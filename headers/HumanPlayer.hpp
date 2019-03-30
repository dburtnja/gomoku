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

        HumanPlayer(void);
        HumanPlayer(int playerNumber, int playerSymbol);
        //AComputerPlayer(ComputerPlayer &toCopy);
        ~HumanPlayer();
        //ComputerPlayer & operator=(ComputerPlayer const &rhs);


        Move makeMove(GomokuMainBoard & bord, View *view,  APlayer * player_1, APlayer * player_2) override ;
};

#endif //GOMOKU_HUMANPLAYER_HPP
