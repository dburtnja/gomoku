//
// Created by mirexcool on 29.03.2019.
//


#include "../headers/APlayer.hpp"
#include "../headers/View.hpp"


APlayer::APlayer(int playerNumber, int playerSymbol) {
    _playerNumber = playerNumber;
    _playerSymbol = playerSymbol;
    _capture = 0;
    _moveTime = 0;
}

APlayer::~APlayer() = default;

int APlayer::getPlayerCapture() {
    return _capture;
}

int APlayer::getPlayerNumber() {
    return _playerNumber;
}

int APlayer::getPlayerSymbol() {
    return _playerSymbol;
}

double APlayer::getTimeLastMove() {
    return _moveTime;
}

void APlayer::setTimeLastMove(double seconds) {
    _moveTime = seconds;
}

void APlayer::increaseCapture(int count) {
    _capture+=count;
}

Move APlayer::makeMove(GomokuMainBoard &board, APlayer *otherPlayer) {
    Move    move{};
    clock_t start;

    start = clock();
    move = this->_makeMove(board, otherPlayer);
    move.moveTime = double(clock() - start) / CLOCKS_PER_SEC;
    if (move.coordinatesList.size() > 0)
    {
        board.putStoneOnBoard(
                move.coordinatesList[0]->getX(),
                move.coordinatesList[0]->getY(),
                this->getPlayerSymbol(), 1);
        board.check_for_capture(
                move.coordinatesList[0]->getX(),
                move.coordinatesList[0]->getY(),
                this, otherPlayer, true, move.coordinatesList);

    }

    return move;
}
