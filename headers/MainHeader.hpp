//
// Created by mirex on 04.07.2018.
//

#ifndef GOMOKU_MAINHEADER_HPP
#define GOMOKU_MAINHEADER_HPP

#define GOMOKU_BOARD_SIZE 19
#define AI_PLAYER 1
#define HUMAN_PLAYER 2
#define REC_DEPT 3
#define POINTS_TO_WIN 5

#define FIRST_PLAYER	1
#define SECOND_PLAYER	2
#define EMPTY_CELL		0

#define START_GAMEBOARD_IMAGE		"media/start-game-nachat-igru-start-start-the-game.jpg"
#define BACKGROUND_GAMEBOARD_IMAGE	"media/wildtextures-wooden-chopping-board-texture.jpg"
#define HELPER_CIRCLE_IMAGE_BLACK	"media/c335fbfdaa3108405b2107b604242bf3.png"
#define CIRCLE_IMAGE_WHITE			"media/white-basic-plate-topview-115309816956uh4u3kfo4.png"
#define CIRCLE_IMAGE_BLACK			"media/black-sphere-png-7.png"

#include <limits>
#include <climits>
#include "iostream"
#include <iomanip>
#include "string.h"
#include "vector"
#include "map"
#include "algorithm"
#include <unordered_map>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


#include "GomokuMainBoard.hpp"
#include "SingleStone.hpp"
#include "ArtificialIntelligence.hpp"
#include "AvailableSpot.hpp"
#include "AiMove.hpp"
//#include "BoardState.hpp"
#include "time.h"
#endif //GOMOKU_MAINHEADER_HPP
