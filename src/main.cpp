#include "../headers/MainHeader.hpp"
#include "../headers/View.hpp"
#include "../headers/ArtificialIntelligence.hpp"

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


int main() {
    View		*view;
    int			moveCounter = 0;
    bool		gameOver;

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

    if (!view->showStartWindowAndWaitForStart(START_GAMEBOARD_IMAGE))
    	std::cout << "Error on showStartWindowAndWaitForStart: " << SDL_GetError() << std::endl;

    if (!view->showGameBoard(BACKGROUND_GAMEBOARD_IMAGE)) {
    	std::cout << "Error on creation gameboard background." << std::endl;
		return -1;
    }

//    setEventTypesToCheck(view);
	moveCounter++;

    while (view->isRunning()) {
    	std::reverse(mainBoard->availablespots.begin(), mainBoard->availablespots.end());
		checkEvents(view);
		if (f5) {
			f5 = false;
			view->updateAllBoard(mainBoard);
			view->updateGameScreen();
		}
		if (motion_exist) {
			SDL_Point	indexesPoint;

			motion_exist = false;
			if (view->getIndexesFromCoordinate(&indexesPoint, motion.button.x, motion.button.y)) {
				view->showBoardHelper(indexesPoint, mainBoard->getPlayer());
				view->updateGameScreen();
			}
		}
		if (mainBoard->getPlayer(moveCounter) == AI_PLAYER && !gameOver) {
			SDL_Point   indexesPoint;
			Coordinates	winingCoords[1];

            oneMove = AI->runAI(*mainBoard, AI_PLAYER, HUMAN_PLAYER);
			mainBoard->putStoneOnBoard(oneMove.x, oneMove.y, AI_PLAYER, GOMOKU_BOARD_SIZE * GOMOKU_BOARD_SIZE - moveCounter);

			indexesPoint.x = oneMove.x;
			indexesPoint.y = oneMove.y;

			view->putStoneOnBoard(indexesPoint, AI_PLAYER);

			mainBoard->check_for_capture(oneMove.x, oneMove.y, AI_PLAYER, HUMAN_PLAYER, true, oneMove.coordinatesList);
			oneMove.capturePlayer_1 = mainBoard->ai_capture;
			oneMove.capturePlayer_2 = mainBoard->player_capture;
			//how to get structures info
            for(auto & element: oneMove.coordinatesList)
            {
                printf("COORDS TO UPDATE = %d, %d, SYMBOL = %d\n", element->getX(), element->getY(), element->getPlayer());
            }
                if (mainBoard->win(oneMove.x, oneMove.y) || mainBoard->ai_capture >= 10)
			{
			    winingCoords[0] = Coordinates(oneMove.x, oneMove.y, HUMAN_PLAYER);
                printf(" AI_PLAYER WON !!! in %d moves \n", moveCounter);

                view->showWiningLine(winingCoords, 1, "AI Player WON!");
				gameOver = true;
			}
            //end
            view->updateGameScreen();

			mainBoard->printBoard();
			moveCounter++;
		}
		if (mainBoard->getPlayer(moveCounter) == HUMAN_PLAYER && mouse_exist && !gameOver) {
			SDL_Point	indexesPoint;
			int			player;
			Coordinates	winingCoords[1];


			mouse_exist = false;
			if (view->getIndexesFromCoordinate(&indexesPoint, mouse.button.x, mouse.button.y)) {
				player = mainBoard->getPlayer(moveCounter);

				if (mainBoard->putStoneOnBoard(indexesPoint.x, indexesPoint.y, player, GOMOKU_BOARD_SIZE * GOMOKU_BOARD_SIZE - moveCounter)) {
					mainBoard->check_for_capture(indexesPoint.x, indexesPoint.y, HUMAN_PLAYER, AI_PLAYER, true, oneMove.coordinatesList);
					view->putStoneOnBoard(indexesPoint, player);
					view->updateGameScreen();
					if (mainBoard->win(indexesPoint.x, indexesPoint.y) || mainBoard->player_capture >= 10)
					{
						printf(" HUMAN WON !!! in %d moves \n", moveCounter);
						winingCoords[0] = Coordinates(oneMove.x, oneMove.y, AI_PLAYER);
						view->showWiningLine(winingCoords, 1, "Human Player WON!");
						gameOver = true;
					}
					moveCounter++;
				}
			}
		}
		//TODO free(move)
    }
}
