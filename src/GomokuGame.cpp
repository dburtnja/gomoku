//
// Created by denys on 02.04.19.
//

#include "../headers/GomokuGame.hpp"
#include "../headers/View.hpp"
#include "../headers/ComputerPlayer.hpp"
#include "../headers/HumanPlayer.hpp"
#include "../headers/HumanVsCompute.hpp"

GomokuGame::GomokuGame() {
    this->_board = new GomokuMainBoard;
    this->_view = new View(1200, 900, "Gomocu", this->_board, 200);
}

GomokuGame::~GomokuGame() {
    std::cout << "Free data in GomokuGame." << std::endl;
    for (auto *player : this->_players)
        delete player;
    delete this->_view;
    delete this->_board;
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

    if (winner >= 0) {
        std::cout << winner << " WIN!" << std::endl;
        this->_view->showWiningLine("Game over!", &winningMove);
    }
}


void GomokuGame::_setPlayers() {
    int players[2];

    players[FIRST_PLAYER_POSITION] = 0;
    players[SECOND_PLAYER_POSITION] = 0;
    if (!this->_view->showStartWindowAndWaitForStart(START_GAMEBOARD_IMAGE, &players[0]))
    	std::cout << "Error on showStartWindowAndWaitForStart: " << SDL_GetError() << std::endl;

    for (auto playerType : players) {
        if (playerType != AI_PLAYER and playerType != HUMAN_PLAYER and playerType != DEBUG_PLAYER) {
            return;
        }
    }

    this->_players = {
            this->_getPlayerObj(players[FIRST_PLAYER_POSITION], FIRST_PLAYER_POSITION, FIRST_PLAYER_ON_MAP),
            this->_getPlayerObj(players[SECOND_PLAYER_POSITION], SECOND_PLAYER_POSITION, SECOND_PLAYER_ON_MAP)
    };
}

APlayer *GomokuGame::_getPlayerObj(int playerType, int playerNumber, int playerSymbol) {
    if (playerType == AI_PLAYER)
        return new ComputerPlayer(playerNumber, playerSymbol);
    if (playerType == HUMAN_PLAYER)
        return new HumanPlayer(playerNumber, playerSymbol);
    if (playerType == DEBUG_PLAYER)
        return new HumanVsCompute(playerNumber, playerSymbol);
    std::cout << "WARNING: NO PLAYER SPECIFIED, SELECTING HUMAN PLAYER." << std::endl;
    return new HumanPlayer(playerNumber, playerSymbol);
}

int GomokuGame::_startGomokuGame(Move &winningMove) {
    SDL_Event   event;
    Move        move{};

    this->_moveCounter = 0;

    if (!this->_view->showGameBoard(BACKGROUND_GAMEBOARD_IMAGE)) {
    	std::cout << "Error on creation gameboard background." << std::endl;
		return -1;
    }

    this->_view->addEventHandler([this](View *view, SDL_Event *event){
        SDL_Point   index;

        if (event->type == SDL_MOUSEMOTION) {
            if (event->motion.x % 5 == 0 || event->motion.y % 5 == 0) {
                if (view->getIndexesFromCoordinate(&index, event->motion.x, event->motion.y)) {
                    view->showBoardHelper(index, this->_getCurrentPlayer()->getPlayerSymbol());
                    view->updateGameScreen();
                }
                return true;
            }
        }
        return false;
    });

    while (this->_view->isRunning()) {
        while (this->_view->pullEvent(&event));
        move = this->_getCurrentPlayer()->makeMove(*(this->_board), this->_getOppositePlayer());
        move.capturePlayer_1 = this->_players[FIRST_PLAYER_POSITION]->getPlayerCapture();
        move.capturePlayer_2 = this->_players[SECOND_PLAYER_POSITION]->getPlayerCapture();
        move.moveCounter = this->_moveCounter;
        if (!this->_view->isRunning())
            return -1;
        this->_view->updateMenuValues(move);
        if (this->_board->win(move.coordinatesList[0]->getX(), move.coordinatesList[0]->getY(), &move)
            || this->_getCurrentPlayer()->getPlayerCapture() >= 10) {
            winningMove = move;
            return this->_getCurrentPlayer()->getPlayerNumber();
        }
        if (this->_board->draw())
            std::cout << "DRAW!\n";
        this->_view->updateMove(move);
        this->_view->updateAllBoard(this->_board);
        this->_view->updateGameScreen();
        this->_moveCounter++;
    }
    return -1;
}

APlayer *GomokuGame::_getCurrentPlayer() {
    return this->_players[this->_moveCounter % 2];
}

APlayer *GomokuGame::_getOppositePlayer() {
    return this->_players[(this->_moveCounter + 1) % 2];
}

int GomokuGame::getMoveCounter() {
    return _moveCounter;
}
