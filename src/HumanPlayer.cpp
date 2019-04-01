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



Move HumanPlayer::makeMove(GomokuMainBoard & board, View *view,  APlayer * player_1, APlayer * player_2)
{

    SDL_Event	mouse;
    Move oneMove;
    SDL_Point indexesPoint;

    while (view->waitEvent(&mouse))
    {
        if (view->getIndexesFromCoordinate(&indexesPoint, mouse.button.x, mouse.button.y))
        {
            oneMove.x = indexesPoint.x;
            oneMove.y = indexesPoint.y;
            board.putStoneOnBoard(oneMove.x, oneMove.y, this->getplayerSymbol(), GOMOKU_BOARD_SIZE * GOMOKU_BOARD_SIZE - 0);
            board.check_for_capture(oneMove.x, oneMove.y, player_1, player_2, true, oneMove.coordinatesList);
            return oneMove;
        }
    }
    return oneMove;
}