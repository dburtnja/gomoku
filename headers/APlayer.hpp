//
// Created by mirexcool on 29.03.2019.
//



#pragma once

#include "MainHeader.hpp"
#include "ArtificialIntelligence.hpp"

class ArtificialIntelligence;
struct Move;

class APlayer
{
public:
    APlayer(int playerNumber, int playerSymbol);
    virtual ~APlayer();

    int getPlayerNumber();
    int getPlayerSymbol();
    int getPlayerCapture();
    double getTimeLastMove();

    void increaseCapture(int count);
    void setTimeLastMove(double seconds);

    Move makeMove(GomokuMainBoard &board, APlayer *otherPlayer);

protected:
    virtual Move _makeMove(GomokuMainBoard &board, APlayer *otherPlayer) = 0;

private:
    int _playerNumber;
    int _playerSymbol;
    int _capture;
    double _moveTime;

};

