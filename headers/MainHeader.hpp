//
// Created by mirex on 04.07.2018.
//

#ifndef GOMOKU_MAINHEADER_HPP
#define GOMOKU_MAINHEADER_HPP

#define GOMOKU_BOARD_SIZE 19
#define REC_DEPT 3

#define AI_PLAYER 1
#define HUMAN_PLAYER 2
#define DEBUG_PLAYER 3

#define POINTS_TO_WIN 5

#define FIRST_PLAYER_ON_MAP     1
#define SECOND_PLAYER_ON_MAP	2
#define EMPTY_CELL_ON_MAP		0
#define EMPTY_CELL              0

#define FIRST_PLAYER_POSITION   0
#define SECOND_PLAYER_POSITION  1


#define START_GAMEBOARD_IMAGE		"media/start-game-nachat-igru-start-start-the-game.jpg"
#define BACKGROUND_GAMEBOARD_IMAGE	"media/wildtextures-wooden-chopping-board-texture.jpg"
#define HELPER_CIRCLE_IMAGE_BLACK	"media/c335fbfdaa3108405b2107b604242bf3.png"
#define CIRCLE_IMAGE_WHITE			"media/white-basic-plate-topview-115309816956uh4u3kfo4.png"
#define CIRCLE_IMAGE_BLACK			"media/black-sphere-png-7.png"

#define FONT_FILE                   "media/OpenSans-Bold.ttf"
#define FONT_SIZE_24                24
#define FONT_SIZE_46                46

#include <limits>
#include <climits>
#include "iostream"
#include <iomanip>
#include "string.h"
#include "vector"
#include "map"
#include "algorithm"
#include <unordered_map>
#include <cmath>
#include "time.h"


//#include <SDL2/SDL.h>
//#include <SDL2/SDL_image.h>
//#include <SDL2/SDL_ttf.h>

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>

/*#include "GomokuMainBoard.hpp"
#include "ArtificialIntelligence.hpp"
#include "AvailableSpot.hpp"
#include "AiMove.hpp"
#include "Coordinates.hpp"
#include "BoardState.hpp"
#include "APlayer.hpp"
#include "HumanPlayer.hpp"
#include "ComputerPlayer.hpp"
#include "View.hpp"*/


#endif //GOMOKU_MAINHEADER_HPP
