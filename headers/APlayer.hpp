//
// Created by mirexcool on 29.03.2019.
//



#pragma once

#include "MainHeader.hpp"

#include "ArtificialIntelligence.hpp"

#include "View.hpp"

class ArtificialIntelligence;
struct Move;

class APlayer
{
    public:
            APlayer();
            APlayer(int playerNumber, int playerSymbol);
            //APlayer(APlayer & toCopy);
            virtual ~APlayer();
            //APlayer &operator=(APlayer const &rhs);

            int getPlayerNumber();
            int getplayerSymbol();
            int getPlayerCapture();
            double getTimeLastMove();

            void increaseCapture(int count);
            void setTimeLastMove(double seconds);

            virtual Move makeMove(GomokuMainBoard & bord, View *view,  APlayer * player_1, APlayer * player_2) = 0;

    private:
            int _playerNumber;
            int _playerSymbol;
            int _capture;
            double _moveTime;

};

