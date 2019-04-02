//
// Created by denys on 15.03.19.
//

#ifndef GOMOKU_VIEW_HPP
#define GOMOKU_VIEW_HPP

#include <list>
#include <array>
#include <functional>
#include "MainHeader.hpp"
#include "SDLTextureClass.hpp"
#include "GomokuMainBoard.hpp"
#include "ArtificialIntelligence.hpp"

#define HELPER_ALPHA	150

#define CENTER(size, minsize)	((size / 2) - (minsize / 2))

#define BOARD_LINE_SIZE							3
#define POINT_RADIUS_PERCENT_FROM_CELL_DISTANCE	40

const SDL_Color	WHITE_COLOR_SDL = {255, 255, 255, 255};
const SDL_Color	BLACK_COLOR_SDL = {0, 0, 0, 255};
const SDL_Color	GREY_COLOR_SDL = {128, 128, 128, 255};
const SDL_Color	RED_COLOR_SDL = {255, 0, 0, 255};



class View {

public:

	View(int width, int height, char const *name, GomokuMainBoard *board, Uint32 sleep_time);
	~View();

	static View	*getInstance();

	bool		showStartWindowAndWaitForStart(const char *img_file_path, int *players);
	bool		isRunning();
	bool 		pullEvent(SDL_Event *event);
	bool 		waitEvent(SDL_Event *event);
	bool		showGameBoard(const char *img_file_path);
	bool		getIndexesFromCoordinate(SDL_Point *index, int &x, int &y);
	void		showBoardHelper(SDL_Point indexPoint, int playerNumber);
	void		updateGameScreen();
	void		putStoneOnBoard(SDL_Point indexPoint, int playerNumber);
	void		putStoneOnBoard(Coordinates *coordinates);

    void showWiningLine(const char *message, Move *winingMove);

    void updateAllBoard(GomokuMainBoard *board);

    void setEventTypesToCheck(std::vector<Uint32> eventTypes);
    void addEventHandler(std::function<bool(View *view, SDL_Event *event)>);

private:

	int								_width;
	int								_height;
	const char						*_name;
	int								_first_player;
	int								_second_player;
	int 							_sleep_time;
	bool							_running;
	SDL_Window						*_window;
	SDL_Renderer					*_renderer;
	SDLTextureClass					*_boardBackground;
	SDLTextureClass 				*_firsPlayerHelperStoneTexture;
	SDLTextureClass					*_secondPlayerHelperStoneTexture;
	SDLTextureClass 				*_firstPlayerStoneTexture;
	SDLTextureClass 				*_secondPlayerStoneTexture;
	SDLTextureClass 				*_boardTextureClass;
	TTF_Font                        *_font24;
	TTF_Font                        *_font46;
	std::array<SDLTextureClass*, 1>	_textures;
	std::list<std::function<bool(View*, SDL_Event*)>>	_eventHandlers;
	int								*_boardCoordinates;
	int								_coordinatesLength;
	int								_distance;
	int								_pointRadious;
    bool                            _debug;
    static View						*_selfInstance;

	SDL_Texture*	_loadImage(const char *img_file_path);
	void 			_applyTexture(int x, int y, SDL_Texture *texture);
	void			_drawLine(int x1, int y1, int x2, int y2, const SDL_Color color, Uint8 alpha, int w);
	bool			_checkViewEvent(SDL_Event *event);
	void			_renderBackgroundBoard();
	void 			_setBoardCoordinates();
	bool 			_coordinatesOnBoard(int &x, int &y);
	void 			_setBoardBackground(const char *img_file_path);
	void 			_placeTextureByIndexPoint(SDL_Point indexPoint, SDLTextureClass *textureToPlace);
    void            _debugMessage(const char *message);
    void            _afterInitSDL();
    void            _setBoardValues(GomokuMainBoard *board);

    void _renderText(const char *message, TTF_Font *font, int x, int y);

	void _renderStone(Coordinates *coordinates);
};



#endif //GOMOKU_VIEW_HPP
