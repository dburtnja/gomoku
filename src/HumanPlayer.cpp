//
// Created by mirexcool on 29.03.2019.
//

#include "../headers/HumanPlayer.hpp"
#include "../headers/View.hpp"

HumanPlayer::HumanPlayer(int playerNumber, int playerSymbol) : APlayer(playerNumber, playerSymbol){
}

Move HumanPlayer::makeMove(GomokuMainBoard &board, APlayer *otherPlayer)
{
    View        *view;
    SDL_Event   event;
    SDL_Point   index;
    Move        move;


    view = View::getInstance();
    while (view->isRunning()) {
        while (view->pullEvent(&event)) {
            if (event.type == SDL_MOUSEBUTTONDOWN &&
            view->getIndexesFromCoordinate(&index, event.motion.x, event.motion.y)) {
                move.coordinatesList.push_back(new Coordinates(index.x, index.y, this->getPlayerNumber()));
                move.x = index.x;
                move.y = index.y;
                board.putStoneOnBoard(index.x, index.y, this->getPlayerSymbol(), 0); //todo ask about depth in put stone on board;
                board.check_for_capture(index.x, index.y, this, otherPlayer, true, move.coordinatesList);
                return move;
            }
        }
    }
    return move;
}
