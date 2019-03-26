#include "../headers/MainHeader.hpp"
#include "../headers/View.hpp"




//int			main() {
//    AiMove move{};
//    GomokuMainBoard * mainBoard = new GomokuMainBoard;
//
//    ArtificialIntelligence * AI = new ArtificialIntelligence;
//
//    //mainBoard->availablespots.push_back(new AvailableSpot(GOMOKU_BOARD_SIZE / 2, GOMOKU_BOARD_SIZE / 2));
//
//    int i = 0;
//    while(1) {
//        if (i % 2   == AI_PLAYER)
//        {
//            move = AI->runAI(*mainBoard, AI_PLAYER );
//            if (mainBoard->win(move.x, move.y))
//            {
//                std::cout << " AI_PLAYER WON !!! \n";
//                break;
//            }
//            mainBoard->printBoard();
////            int x;
////            int y;
////            std::cout <<"Enter x: ";
////            std::cin >> x;
////            std::cout <<"Enter y: ";
////            std::cin >> y;
////            mainBoard->putStoneOnBoard(x,y,AI_PLAYER, 100);
//
////            mainBoard->printBoard();
////            if (mainBoard->win(x, y))
////            {
////                std::cout << " HUMAN_PLAYER WON !!! \n";
////                break;
////            }
//        }
//        else
//        {
//            int x;
//            int y;
//            std::cout <<"Enter x: ";
//            std::cin >> x;
//            std::cout <<"Enter y: ";
//            std::cin >> y;
//            mainBoard->putStoneOnBoard(x,y,HUMAN_PLAYER, 100);
//
//            mainBoard->printBoard();
//            if (mainBoard->win(x, y))
//            {
//                std::cout << " HUMAN_PLAYER WON !!! \n";
//                break;
//            }
////            move = AI->runAI(*mainBoard, HUMAN_PLAYER );
////            if (mainBoard->win(move.x, move.y))
////            {
////                std::cout << " HUMEN_PYAYER WON !!! \n";
////                break;
////            }
////            mainBoard->printBoard();
//        }
////        int score = AI->evaluation(*mainBoard, AI_PLAYER);
////        printf("SCORE 1 = %d\n", score);
////        score = AI->evaluation(*mainBoard, HUMAN_PLAYER);
////        printf("SCORE 2 = %d\n", score);
//        i++;
//        mainBoard->count++;
//    }
//    mainBoard->printBoard();
//    return 0;
//}

SDL_Event	mouse;
SDL_Event	motion;

bool 	motion_exist;
bool	mouse_exist;
bool	f5;

static void	checkEvents(View *view) {
    std::vector<Uint32> eventTypes;

	SDL_Event	event;
	SDL_Point	indexesPoint;

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
    int			moveCounter;
    bool		gameOver;

    GomokuMainBoard * mainBoard = new GomokuMainBoard;
	ArtificialIntelligence * AI = new ArtificialIntelligence;
	AiMove	move{};

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

			move = AI->runAI(*mainBoard, AI_PLAYER);
			indexesPoint.x = move.x;
			indexesPoint.y = move.y;
			view->putStoneOnBoard(indexesPoint, AI_PLAYER);
			mainBoard->check_for_capture(*mainBoard, move.x, move.y, AI_PLAYER, HUMAN_PLAYER, true);
			if (mainBoard->win(move.x, move.y) || mainBoard->ai_capture >= 10)
			{
			    winingCoords[0] = Coordinates(move.x, move.y, HUMAN_PLAYER);
				std::cout << " AI_PLAYER WON !!! \n";
				view->showWiningLine(winingCoords, 1, "AI Player WON!");
				gameOver = true;
			}
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

				if (mainBoard->putStoneOnBoard(indexesPoint.x, indexesPoint.y, player, 100)) {
					mainBoard->check_for_capture(*mainBoard, indexesPoint.x, indexesPoint.y, HUMAN_PLAYER, AI_PLAYER, true);
					view->putStoneOnBoard(indexesPoint, player);
					view->updateGameScreen();
					if (mainBoard->win(indexesPoint.x, indexesPoint.y) || mainBoard->player_capture >= 10)
					{
						std::cout << " HUMAN WON !!! \n";
						winingCoords[0] = Coordinates(move.x, move.y, AI_PLAYER);
						view->showWiningLine(winingCoords, 1, "Human Player WON!");
						gameOver = true;
					}
					moveCounter++;
				}
			}
		}
    }
}
