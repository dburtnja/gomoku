//
// Created by mirexcool on 29.03.2019.
//


#include "../headers/APlayer.hpp"


APlayer::APlayer(int playerNumber, int playerSymbol) {
    _playerNumber = playerNumber;
    _playerSymbol = playerSymbol;
}

APlayer::~APlayer() = default;

int APlayer::getPlayerCapture() {
    return _capture;
}

int APlayer::getPlayerNumber() {
    std::cout << "getPlayer number" << std::endl;
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