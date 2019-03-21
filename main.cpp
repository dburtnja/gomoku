#include "headers/MainHeader.hpp"
#include "headers/View.hpp"




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

static void	checkEvents(View *view) {
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
	}
}

int main() {
    View		*view;
    int			moveCounter;


//	GomokuMainBoard * mainBoard = nullptr;
    GomokuMainBoard * mainBoard = new GomokuMainBoard;
	ArtificialIntelligence * AI = new ArtificialIntelligence;
	AiMove	move{};

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

    while (view->isRunning()) {
		checkEvents(view);
		if (motion_exist) {
			SDL_Point	indexesPoint;

			motion_exist = false;
			if (view->getIndexesFromCoordinate(&indexesPoint, motion.button.x, motion.button.y)) {
				view->showBoardHelper(indexesPoint, mainBoard->getPlayer());
				view->updateGameScreen();
			}
		}
		if (mainBoard->getPlayer(moveCounter) == AI_PLAYER) {
			SDL_Point	indexesPoint;

			move = AI->runAI(*mainBoard, AI_PLAYER );
			indexesPoint.x = move.x;
			indexesPoint.y = move.y;
			view->putStoneOnBoard(indexesPoint, AI_PLAYER);
			view->updateGameScreen();
			if (mainBoard->win(move.x, move.y))
			{
				std::cout << " AI_PLAYER WON !!! \n";
				break;
			}
			mainBoard->printBoard();
			moveCounter++;
		}
		if (mainBoard->getPlayer(moveCounter) == HUMAN_PLAYER && mouse_exist) {
			SDL_Point	indexesPoint;
			int			player;

			mouse_exist = false;
			if (view->getIndexesFromCoordinate(&indexesPoint, mouse.button.x, mouse.button.y)) {
				player = mainBoard->getPlayer(moveCounter);

				if (mainBoard->putStoneOnBoard(indexesPoint.x, indexesPoint.y, player, 100)) {
					view->putStoneOnBoard(indexesPoint, player);
					view->updateGameScreen();
					if (mainBoard->win(indexesPoint.x, indexesPoint.y))
					{
						std::cout << " HUMAN WON !!! \n";
						break;
					}
					moveCounter++;
				}
			}
		}


    }
}

//
//
//#include <iostream>
//
//#ifdef __linux__
//#include <SDL2/SDL.h>
//#elif defined(_WIN32)
//#include <SDL.h>
//#endif
//
//const int WIN_WIDTH = 640;
//const int WIN_HEIGHT = 480;
//
//int main(int argc, char **argv){
//	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
//		std::cerr << "SDL_Init failed: " << SDL_GetError() << "\n";
//		return 1;
//	}
//	SDL_Window *win = SDL_CreateWindow("Rendering to a texture!", SDL_WINDOWPOS_CENTERED,
//									   SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, 0);
//	SDL_Renderer *renderer = SDL_CreateRenderer(win, -1,
//												SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
//
//	//Put your own bmp image here
//	SDL_Surface *bmpSurf = IMG_Load(HELPER_CIRCLE_IMAGE_BLACK);
//	SDL_Texture *bmpTex = SDL_CreateTextureFromSurface(renderer, bmpSurf);
//	SDL_FreeSurface(bmpSurf);
//
//	//Make a target texture to render too
//	SDL_Texture *texTarget = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
//											   SDL_TEXTUREACCESS_TARGET, WIN_WIDTH, WIN_HEIGHT);
//
//	//Now render to the texture
//	SDL_SetRenderTarget(renderer, texTarget);
//	SDL_RenderClear(renderer);
//	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 150);
//	SDL_RenderFillRect(renderer, NULL);
//
//	SDL_RenderCopy(renderer, bmpTex, NULL, NULL);
//
////	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 150);
////	SDL_RenderDrawLine(renderer, 0, 0, 50, 250);
//
//	//Detach the texture
//	SDL_SetRenderTarget(renderer, NULL);
//
//	//Now render the texture target to our screen, but upside down
//	SDL_RenderClear(renderer);
//	SDL_RenderCopyEx(renderer, texTarget, NULL, NULL, 0, NULL, SDL_FLIP_VERTICAL);
//	SDL_RenderPresent(renderer);
//
//	SDL_Delay(2000);
//	SDL_DestroyTexture(texTarget);
//	SDL_DestroyTexture(bmpTex);
//	SDL_DestroyRenderer(renderer);
//	SDL_DestroyWindow(win);
//	SDL_Quit();
//	return 0;
//}


//
//#include <iostream>
//#include <vector>
////#include <SDL.h>
//
//void fillTexture(SDL_Renderer *renderer, SDL_Texture *texture, int r, int g, int b, int a)
//{
//	SDL_SetRenderTarget(renderer, texture);
//	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
//	SDL_SetRenderDrawColor(renderer, r, g, b, a);
//	SDL_RenderFillRect(renderer, NULL);
//}
//
//void prepareForRendering(SDL_Renderer *renderer)
//{
//	SDL_SetRenderTarget(renderer, NULL);
//	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
//	SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
//}
//
//void checkSdlError()
//{
//	const char *sdlError = SDL_GetError();
//	if(sdlError && *sdlError)
//	{
//		::std::cout << "SDL ERROR: " << sdlError << ::std::endl;
//	}
//}
//
//int main(int argc, char *argv[])
//{
//	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_HAPTIC);
//
//	SDL_Window *window = SDL_CreateWindow("SDL test",
//										  SDL_WINDOWPOS_CENTERED,
//										  SDL_WINDOWPOS_CENTERED,
//										  320, 240,
//										  SDL_WINDOW_OPENGL);
//	SDL_Renderer *renderer = SDL_CreateRenderer(
//			window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
//
//	const int width = 50;
//	const int height = 50;
//
//	::std::vector<SDL_Texture*> textures;
//
//	SDL_Texture *redTexture = SDL_CreateTexture(renderer,
//												SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
//	textures.push_back(redTexture);
//
//	SDL_Texture *greenTexture = SDL_CreateTexture(renderer,
//												  SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
//	textures.push_back(greenTexture);
//
//	SDL_Texture *purpleTexture = SDL_CreateTexture(renderer,
//												   SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
//	textures.push_back(purpleTexture);
//
//	// Here is setting the blend mode for each and every used texture:
//	for(int i = 0; i < textures.size(); ++i)
//	{
//		SDL_SetTextureBlendMode(textures[i], SDL_BLENDMODE_BLEND);
//	}
//
//	int purpleAlpha = 0;
//
//	fillTexture(renderer, redTexture, 255, 0, 0, 255);
//	fillTexture(renderer, greenTexture, 0, 255, 0, 128);
//	fillTexture(renderer, purpleTexture, 255, 0, 255, purpleAlpha);
//
//	prepareForRendering(renderer);
//
//	bool running = true;
//	while(running)
//	{
//		SDL_Rect rect;
//		rect.w = width;
//		rect.h = height;
//
//		SDL_RenderClear(renderer);
//
//		rect.x = 50;
//		rect.y = 50;
//		SDL_RenderCopy(renderer, redTexture, NULL, &rect);
//
//		rect.x = 75;
//		rect.y = 70;
//		SDL_RenderCopy(renderer, greenTexture, NULL, &rect);
//
//		rect.x = 75;
//		rect.y = 30;
//		SDL_RenderCopy(renderer, purpleTexture, NULL, &rect);
//
//		SDL_RenderPresent(renderer);
//
//		// Process events
//		{
//			SDL_Event event;
//			while(SDL_PollEvent(&event) == 1)
//			{
//				if(event.type == SDL_QUIT)
//				{
//					running = false;
//				}
//				else if(event.type == SDL_KEYDOWN)
//				{
//					switch(event.key.keysym.sym)
//					{
//						case SDLK_ESCAPE:
//							running = false;
//							break;
//						case SDLK_a:
//							purpleAlpha = ::std::max(purpleAlpha - 32, 0);
//							fillTexture(renderer, purpleTexture, 255, 0, 255, purpleAlpha);
//							prepareForRendering(renderer);
//							::std::cout << "Alpha: " << purpleAlpha << ::std::endl;
//							break;
//						case SDLK_s:
//							purpleAlpha = ::std::min(purpleAlpha + 32, 255);
//							fillTexture(renderer, purpleTexture, 255, 0, 255, purpleAlpha);
//							prepareForRendering(renderer);
//							::std::cout << "Alpha: " << purpleAlpha << ::std::endl;
//							break;
//					}
//				}
//			}
//
//			checkSdlError();
//		}
//	}
//
//	for(int i = 0; i < textures.size(); ++i)
//	{
//		SDL_DestroyTexture(textures[i]);
//	}
//	textures.clear();
//
//	SDL_DestroyRenderer(renderer);
//	renderer = NULL;
//	SDL_DestroyWindow(window);
//	window = NULL;
//
//	SDL_Quit();
//
//	checkSdlError();
//
//	return 0;
//}