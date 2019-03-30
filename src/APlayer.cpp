//
// Created by mirexcool on 29.03.2019.
//


#include "../headers/APlayer.hpp"

APlayer::APlayer() {

}

//APlayer::APlayer(APlayer &toCopy) {}

APlayer::APlayer(int playerNumber, int playerSymbol) {
    _playerNumber = playerNumber;
    _playerSymbol = playerSymbol;
}

//APlayer& APlayer::operator=(APlayer const &rhs) {}

APlayer::~APlayer() {

}

int APlayer::getPlayerCapture() {
    return _capture;
}

int APlayer::getPlayerNumber() {
    return _playerNumber;
}

int APlayer::getplayerSymbol() {
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