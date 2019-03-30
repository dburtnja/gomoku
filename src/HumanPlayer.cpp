//
// Created by mirexcool on 29.03.2019.
//

#include "../headers/HumanPlayer.hpp"

HumanPlayer::HumanPlayer(int playerNumber, int playerSymbol ) :
        APlayer(playerNumber, playerSymbol){}



HumanPlayer::HumanPlayer() {}

HumanPlayer::~HumanPlayer() {}

//AIPlayer::AIPlayer(AIPlayer & toCopy){}

//AIPlayer& AIPlayer::operator=(AIPlayer const &rhs) {}



Move HumanPlayer::makeMove(GomokuMainBoard & bord, View *view,  APlayer * player_1, APlayer * player_2)
{

    SDL_Event	mouse;
    SDL_Event	motion;

    bool 	motion_exist;
    bool	mouse_exist;

    Move oneMove;
    SDL_Point indexesPoint;

    while (view->isRunning())
    {
        if (view->getIndexesFromCoordinate(&indexesPoint, mouse.button.x, mouse.button.y))
        {
            oneMove.x = indexesPoint.x;
            oneMove.y = indexesPoint.y;
            break ;
        }
    }
    return oneMove;
}