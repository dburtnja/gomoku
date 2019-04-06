//
// Created by denys on 03.04.19.
//

#include "../headers/HumanVsCompute.hpp"
#include "../headers/View.hpp"

HumanVsCompute::HumanVsCompute(int playerNumber, int playerSymbol) : APlayer(playerNumber, playerSymbol) {

}

Move HumanVsCompute::_makeMove(GomokuMainBoard &board, APlayer *otherPlayer) {
    View                    *view;
    SDL_Event               event;
    SDL_Point               index;
    Move                    move{};
    ArtificialIntelligence  *artificialIntelligence;

    artificialIntelligence = new ArtificialIntelligence;
    move = artificialIntelligence->runAI(board, this, otherPlayer);
    delete artificialIntelligence;
    view = View::getInstance();
    index.x = move.coordinatesList[0]->getX();
    index.y = move.coordinatesList[0]->getY();
    view->showBoardHelper(index, this->getPlayerSymbol());
    view->updateGameScreen();
    while (view->isRunning()) {
        while (view->pullEvent(&event)) {
            if (
                    event.type == SDL_MOUSEBUTTONDOWN &&
                    view->getIndexesFromCoordinate(&index, event.motion.x, event.motion.y) &&
                    board.getValue(index.x, index.y) == EMPTY_CELL_ON_MAP)
            {
                move.coordinatesList.push_back(new Coordinates(index.x, index.y, this->getPlayerSymbol()));
                move.coordinatesList[0]->setX(index.x);
                move.coordinatesList[0]->setY(index.y);
                return move;
            }
        }
    }
    return move;
}
