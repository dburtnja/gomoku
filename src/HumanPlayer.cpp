//
// Created by mirexcool on 29.03.2019.
//

#include "../headers/HumanPlayer.hpp"
#include "../headers/View.hpp"

HumanPlayer::HumanPlayer(int playerNumber, int playerSymbol) : APlayer(playerNumber, playerSymbol){
}

Move HumanPlayer::_makeMove(GomokuMainBoard &board, APlayer *otherPlayer) {
    View        *view;
    SDL_Event   event;
    SDL_Point   index;
    Move        move{};

    otherPlayer->increaseCapture(0);
    view = View::getInstance();
    while (view->isRunning()) {
        while (view->pullEvent(&event)) {
            if (
                    event.type == SDL_MOUSEBUTTONDOWN &&
                    view->getIndexesFromCoordinate(&index, event.motion.x, event.motion.y) &&
                    board.getValue(index.x, index.y) == EMPTY_CELL_ON_MAP)
            {
                move.coordinatesList.push_back(new Coordinates(index.x, index.y, this->getPlayerSymbol()));
                return move;
            }
        }
    }
    return move;
}