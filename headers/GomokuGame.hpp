//
// Created by denys on 02.04.19.
//

#ifndef GOMOKU_GOMOKUGAME_HPP
#define GOMOKU_GOMOKUGAME_HPP


#include "View.hpp"

class GomokuGame {
public:
    GomokuGame();
    ~GomokuGame();

    void start();

private:
    View                    *_view;
    GomokuMainBoard         *_board;
    std::vector<APlayer*>   _players;
    int                     _moveCounter;

    void _setPlayers();

    APlayer *_getPlayerObj(int playerType, int playerNumber);

    int _startGomokuGame(Move &winningMove);
};


#endif //GOMOKU_GOMOKUGAME_HPP
