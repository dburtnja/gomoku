
#include "../headers/MainHeader.hpp"
#include "../headers/APlayer.hpp"
#include "../headers/ComputerPlayer.hpp"
#include "../headers/HumanPlayer.hpp"
#include "../headers/View.hpp"

SDL_Event	mouse;
SDL_Event	motion;

bool 	motion_exist;
bool	mouse_exist;
bool	f5;

static void	checkEvents(View *view) {
    std::vector<Uint32> eventTypes;

	SDL_Event	event;
	//SDL_Point	indexesPoint;

	while (view->pullEvent(&event)) {
		if (event.type == SDL_MOUSEMOTION) {
			motion = event;
			motion_exist = true;
		}
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			mouse = event;
			mouse_exist = true;
		}
		if (event.type == SDL_KEYDOWN) {
			if (event.key.keysym.sym == SDLK_F5)
				f5 = true;
		}
	}
}


int main()
{


    View		*view;
    int			moveCounter = 0;
    bool		gameOver;
    int         players[2];

    GomokuMainBoard * mainBoard = new GomokuMainBoard;
	ArtificialIntelligence * AI = new ArtificialIntelligence;
	Move	oneMove{};

	gameOver = false;
	try {
        view = new View(1200, 900, "Gomocu", mainBoard, 0);
    } catch (std::string &error) {
        std::cout << error << std::endl;
        return -1;
    }

    if (!view->showStartWindowAndWaitForStart(START_GAMEBOARD_IMAGE, &players[0]))
    	std::cout << "Error on showStartWindowAndWaitForStart: " << SDL_GetError() << std::endl;

    if (!view->showGameBoard(BACKGROUND_GAMEBOARD_IMAGE)) {
    	std::cout << "Error on creation gameboard background." << std::endl;
		return -1;
    }

//    setEventTypesToCheck(view);
	moveCounter++;



    int player_1 = FIRST_PLAYER_ON_MAP;
    int player_2 = SECOND_PLAYER_ON_MAP;

    APlayer *  FirstPlayer = new ComputerPlayer(0, player_1);
    APlayer * SecondPlayer = new ComputerPlayer(1, player_2);
    
    SDL_Event   event;
    
    while (view->waitEvent(&event)) {
        
        view->updateAllBoard(mainBoard);
        view->updateGameScreen();

    	std::reverse(mainBoard->availablespots.begin(), mainBoard->availablespots.end());

		checkEvents(view);
		if (motion_exist) {
			SDL_Point	indexesPoint;

			motion_exist = false;
			if (view->getIndexesFromCoordinate(&indexesPoint, motion.button.x, motion.button.y)) {
				view->showBoardHelper(indexesPoint, mainBoard->getPlayer());
				view->updateGameScreen();
			}
		}
		if (moveCounter % 2 == FirstPlayer->getPlayerNumber() && !gameOver && f5) {
		    f5 = false;

			SDL_Point   indexesPoint;
			Coordinates	winingCoords[1];

            oneMove =  FirstPlayer->makeMove(* mainBoard, view, FirstPlayer, SecondPlayer);
            mainBoard->putStoneOnBoard(oneMove.x, oneMove.y, FirstPlayer->getplayerSymbol(), GOMOKU_BOARD_SIZE * GOMOKU_BOARD_SIZE - moveCounter);

			indexesPoint.x = oneMove.x;
			indexesPoint.y = oneMove.y;

			view->putStoneOnBoard(indexesPoint, FirstPlayer->getplayerSymbol());

			mainBoard->check_for_capture(oneMove.x, oneMove.y, FirstPlayer, SecondPlayer, true, oneMove.coordinatesList);

			oneMove.moveTime = FirstPlayer->getTimeLastMove();
			oneMove.capturePlayer_1 = FirstPlayer->getPlayerCapture();


            if (mainBoard->win(oneMove.x, oneMove.y) || FirstPlayer->getPlayerCapture() >= 10)
            {
                printf(" Player %d WIN!!!!!", FirstPlayer->getPlayerNumber() );
                gameOver = true;
            }

            view->updateGameScreen();

			mainBoard->printBoard();
			moveCounter++;

		}
        else if (moveCounter % 2 == SecondPlayer->getPlayerNumber() && !gameOver && f5)
        {
            f5 = false;

            SDL_Point   indexesPoint;
            Coordinates	winingCoords[1];

            oneMove =  SecondPlayer->makeMove(* mainBoard, view, SecondPlayer, FirstPlayer);
            mainBoard->putStoneOnBoard(oneMove.x, oneMove.y, SecondPlayer->getplayerSymbol(), GOMOKU_BOARD_SIZE * GOMOKU_BOARD_SIZE - moveCounter);

            indexesPoint.x = oneMove.x;
            indexesPoint.y = oneMove.y;

            view->putStoneOnBoard(indexesPoint, SecondPlayer->getplayerSymbol());

            mainBoard->check_for_capture(oneMove.x, oneMove.y, SecondPlayer, FirstPlayer, true, oneMove.coordinatesList);
            if (mainBoard->win(oneMove.x, oneMove.y) || SecondPlayer->getPlayerCapture() >= 10)
            {
                printf(" Player %d WIN!!!!!", SecondPlayer->getPlayerNumber() );

                gameOver = true;
            }

            view->updateGameScreen();

            mainBoard->printBoard();
            moveCounter++;
        }
    }
    free(FirstPlayer);
    free(SecondPlayer);
    free(mainBoard);
    free(AI);
}
