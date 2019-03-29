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

            ComputerPlayer(void);
            ComputerPlayer(int playerNumber, int playerSymbol);
            //AComputerPlayer(ComputerPlayer &toCopy);
            ~ComputerPlayer();
            //ComputerPlayer & operator=(ComputerPlayer const &rhs);


            Move makeMove(GomokuMainBoard & bord, View *view, APlayer * player_1, APlayer * player_2) override ;
};

#endif //GOMOKU_AIPLAYER_HPP
