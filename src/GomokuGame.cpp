//
// Created by denys on 02.04.19.
//

#include "../headers/GomokuGame.hpp"
#include "../headers/View.hpp"
#include "../headers/ComputerPlayer.hpp"
#include "../headers/HumanPlayer.hpp"

GomokuGame::GomokuGame() {
    this->_board = new GomokuMainBoard;
    this->_view = new View(1200, 900, "Gomocu", this->_board, 200);
}

GomokuGame::~GomokuGame() {
    delete this->_board;
    delete this->_view;
}

void GomokuGame::start() {
    int         winner;
    Move        winningMove;

    this->_setPlayers();
    if (this->_players.size() < 2) {
        std::cout << "Please select players!" << std::endl;
        return;
    }

    winner = this->_startGomokuGame(winningMove);
    if (winner > 0) {
        std::cout << winner << " WIN!" << std::endl;
        this->_view->showWiningLine("WINING message", &winningMove);
    }
}


void GomokuGame::_setPlayers() {
    int players[2];

    if (!this->_view->showStartWindowAndWaitForStart(START_GAMEBOARD_IMAGE, &players[0]))
    	std::cout << "Error on showStartWindowAndWaitForStart: " << SDL_GetError() << std::endl;

    for (auto playerType : players) {
        if (playerType != AI_PLAYER and playerType != HUMAN_PLAYER and playerType != DEBUG_PLAYER) {
            return;
        }
    }

    this->_players = {
            this->_getPlayerObj(players[FIRST_PLAYER_POSITION], FIRST_PLAYER_POSITION),
            this->_getPlayerObj(players[SECOND_PLAYER_POSITION], SECOND_PLAYER_POSITION)
    };
}

APlayer *GomokuGame::_getPlayerObj(int playerType, int playerNumber) {
    if (playerType == AI_PLAYER)
        return new ComputerPlayer(playerNumber);
    if (playerType == HUMAN_PLAYER)
        return new HumanPlayer(playerNumber);
    std::cout << "WARNING: NO PLAYER SPECIFIED, SELECTING HUMAN PLAYER." << std::endl;
    return new HumanPlayer(playerNumber);
}

int GomokuGame::_startGomokuGame(Move &winningMove) {
    SDL_Event   event;

    this->_moveCounter = 0;

    if (!this->_view->showGameBoard(BACKGROUND_GAMEBOARD_IMAGE)) {
    	std::cout << "Error on creation gameboard background." << std::endl;
		return -1;
    }

    while (this->_view->isRunning()) {
        while (this->_view->pullEvent(&event)) {
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                winningMove.coordinatesList.push_back(new Coordinates(2, 2, 1));
                winningMove.coordinatesList.push_back(new Coordinates(3, 3, 1));
                winningMove.coordinatesList.push_back(new Coordinates(4, 4, 1));
                winningMove.coordinatesList.push_back(new Coordinates(5, 5, 1));
                winningMove.coordinatesList.push_back(new Coordinates(6, 6, 1));
                return 1;
            }
        }
    }
    return -1;
}
