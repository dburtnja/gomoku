//
// Created by denys on 15.03.19.
//


#include <iostream>
#include <sys/stat.h>


#include "../headers/View.hpp"


View::View(int width, int height, char const *name, GomokuMainBoard *board, int sleep_time) {
	this->_debug = true;
	this->_width = width;
	this->_height = height;
	this->_name = name;
	this->_sleep_time = sleep_time;
	this->_running = true;

    this->_debugMessage("Initialising SDL.");

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0 || TTF_Init())
		throw ("SDL_Init/TTF_Init Error");

	this->_window = SDL_CreateWindow(
			this->_name,
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			this->_width, this->_height,
			SDL_WINDOW_OPENGL);
	if (this->_window == nullptr)
		throw  ("SDL error: Can not create window.");

	this->_renderer = SDL_CreateRenderer(this->_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
	if (this->_renderer == nullptr){
		throw ("SDL error: Can not create render.");
	}

	this->_setBoardValues(board);
	this->_afterInitSDL();
}

void View::_setBoardValues(GomokuMainBoard *board) {
	this->_debugMessage("Calcularing board values on View.");
	this->_coordinatesLength = board->getBoardSize();
	this->_boardCoordinates = new int[this->_coordinatesLength]; //TODO check if size -1
	this->_setBoardCoordinates();
	this->_pointRadious = this->_distance * POINT_RADIUS_PERCENT_FROM_CELL_DISTANCE / 100;
}

void View::_setBoardCoordinates() {
	int thirdWindowSize;
	int	boardWindowSize;
	int startCoordinate;

	thirdWindowSize = 2 * this->_width / 3;
	boardWindowSize = (thirdWindowSize / this->_coordinatesLength) * (this->_coordinatesLength - 1);
	this->_distance = boardWindowSize / this->_coordinatesLength;
	startCoordinate = 2 * this->_distance;
	for (int i = 0; i < this->_coordinatesLength; i++)
		this->_boardCoordinates[i] = startCoordinate + (i * this->_distance);
}

void View::_afterInitSDL() {
	this->_debugMessage("Creating textures");

    this->_font24 = TTF_OpenFont(FONT_FILE, FONT_SIZE_24);
    this->_font46 = TTF_OpenFont(FONT_FILE, FONT_SIZE_46);
    SDL_Texture	*texture;
	texture = SDL_CreateTexture(this->_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
								this->_width, this->_height);
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
	this->_textures[0] = new SDLTextureClass(texture, "Wining texture");
}

void View::_debugMessage(const char *message) {
	if (this->_debug)
		std::cout <<  message << std::endl;
}

View::~View() {
	this->_debugMessage("Free View memory.");
	TTF_CloseFont(this->_font24);
	for (SDLTextureClass *texture : this->_textures)
		delete texture;
	delete [] this->_boardCoordinates;
	delete this->_firsPlayerHelperStoneTexture;
	delete this->_secondPlayerHelperStoneTexture;
	delete this->_boardBackground;
	delete this->_boardTextureClass;
	SDL_DestroyRenderer(this->_renderer);
	SDL_DestroyWindow(this->_window);
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}

bool	View::showStartWindowAndWaitForStart(const char *img_file_path) {
	SDL_Texture	*texture = nullptr;
	SDL_Event	event;

	texture = this->_loadImage(img_file_path);
	if (texture == nullptr) {
		std::cout << "Empty texture." << std::endl;
		return false;
	}
	this->_applyTexture(0, 0, texture);

	while (this->waitEvent(&event)) {
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			SDL_DestroyTexture(texture);
			return true;
		}
	}
	return true;
}

SDL_Texture *View::_loadImage(const char *img_file_path) {
	SDL_Surface	*loadedImage = nullptr;
	SDL_Texture	*texture = nullptr;

	loadedImage = IMG_Load(img_file_path);
	if (loadedImage == nullptr) {
		std::cout << "Can't load image: " << SDL_GetError() << std::endl;
		return nullptr;
	}
	texture = SDL_CreateTextureFromSurface(this->_renderer, loadedImage);
	SDL_FreeSurface(loadedImage);
	return texture;
}

void View::_applyTexture(int x, int y, SDL_Texture *texture) {
	SDL_Rect	position;
	//SDL_Texture	*texture1;

	position.x = x;
	position.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &position.w, &position.h);
	SDL_RenderCopy(this->_renderer, texture, NULL, &position);

	SDL_RenderPresent(this->_renderer);
}

bool	View::isRunning(void) {
	return this->_running;
}

void View::_drawLine(int x1, int y1, int x2, int y2, const SDL_Color color, Uint8 alpha, int w) {
	int new1;
	int new2;
	int counter;

	if (w == 0)
		w = 1;
	SDL_SetRenderDrawColor(this->_renderer, color.r, color.g, color.b, alpha);
	if (abs(x2 - x1) > abs(y2 - y1)) {
		new2 = y2 - w / 2;
		new1 = y1 - w / 2;
		for (int i = 0; i < w; i++) {
			SDL_RenderDrawLine(this->_renderer, x1, new1, x2, new2);
			new1++;
			new2++;
		}
	}
	else if (abs(x2 - x1) < abs(y2 - y1)) {
		new2 = x2 - w / 2;
		new1 = x1 - w / 2;
		for (int i = 0; i < w; i++) {
			SDL_RenderDrawLine(this->_renderer, new1, y1, new2, y2);
			new1++;
			new2++;
		}
	}
	else {
		counter =  - w / 2;
		for (int i = 0; i < w; i++) {
			SDL_RenderDrawLine(this->_renderer, x1 + counter, y1 + counter, x2 + counter, y2 + counter);
			counter++;
		}
	}
}

bool View::pullEvent(SDL_Event *event) {
	if (SDL_PollEvent(event))
		return this->_checkViewEvent(event);
	return false;
}

bool View::waitEvent(SDL_Event *event) {
	if (SDL_WaitEvent(event))
		return this->_checkViewEvent(event);
	return false;
}

bool View::_checkViewEvent(SDL_Event *event) {
	if (event->type == SDL_QUIT) {
		this->_running = false;
		return false;
	}
	return true;
}

bool View::showGameBoard(const char *img_file_path) {
	this->_firstPlayerStoneTexture = new SDLTextureClass(CIRCLE_IMAGE_BLACK, nullptr, nullptr, this->_renderer);
	this->_secondPlayerStoneTexture = new SDLTextureClass(CIRCLE_IMAGE_WHITE, nullptr, nullptr, this->_renderer);
	this->_setBoardBackground(img_file_path);

	this->_firsPlayerHelperStoneTexture = new SDLTextureClass(HELPER_CIRCLE_IMAGE_BLACK,
															  nullptr, nullptr, this->_renderer);
	this->_secondPlayerHelperStoneTexture = new SDLTextureClass(HELPER_CIRCLE_IMAGE_BLACK,
																&BLACK_COLOR_SDL, &WHITE_COLOR_SDL, this->_renderer);
	this->_firsPlayerHelperStoneTexture->showOnRender(false);
	this->_secondPlayerHelperStoneTexture->showOnRender(false);
	return true;
}

void View::_renderBackgroundBoard() {
	int     firstCoordinate;
	int     lastCoordinate;
	int     textFirstCoordinate;
	char    message[3];

	firstCoordinate = this->_boardCoordinates[0];
	lastCoordinate = this->_boardCoordinates[this->_coordinatesLength - 1]; //todo check index
	textFirstCoordinate = firstCoordinate - this->_distance;
	for (int i = 0; i < this->_coordinatesLength; i++) {
		sprintf(message, "%d", i + 1);
        this->_renderText(message, this->_font24, textFirstCoordinate, this->_boardCoordinates[i]);
        this->_renderText(message, this->_font24, this->_boardCoordinates[i], textFirstCoordinate);
		this->_drawLine(
				firstCoordinate, this->_boardCoordinates[i],
				lastCoordinate, this->_boardCoordinates[i],
				BLACK_COLOR_SDL, 255, BOARD_LINE_SIZE);
		this->_drawLine(
				this->_boardCoordinates[i], firstCoordinate,
				this->_boardCoordinates[i], lastCoordinate,
				BLACK_COLOR_SDL, 255, BOARD_LINE_SIZE);
	}
}

bool View::getIndexesFromCoordinate(SDL_Point *index, int &x, int &y) {
	int	min;
	int max;
	int	xIndex;
	int yIndex;

	xIndex = -1;
	yIndex = -1;
	if (!this->_coordinatesOnBoard(x, y))
		return false;
	for (int i = 0; i < this->_coordinatesLength; i++) {
		min = this->_boardCoordinates[i] - this->_pointRadious;
		max = this->_boardCoordinates[i] + this->_pointRadious;
		if (x > min && x < max)
			xIndex = i;
		if (y > min && y < max)
			yIndex = i;
		if (xIndex != -1 && yIndex != -1) {
			index->x = xIndex;
			index->y = yIndex;
			return true;
		}
	}
	return false;
}

bool View::_coordinatesOnBoard(int &x, int &y) {
	int min;
	int max;

	min = this->_boardCoordinates[0] - this->_pointRadious;
	max = this->_boardCoordinates[this->_coordinatesLength - 1] + this->_pointRadious;
	return !(x < min || y < min || x > max || y > max);
}

void View::showBoardHelper(SDL_Point indexPoint, int playerNumber) {
	SDLTextureClass	*texture;

	texture = playerNumber == FIRST_PLAYER ? this->_firsPlayerHelperStoneTexture : this->_secondPlayerHelperStoneTexture;
	this->_placeTextureByIndexPoint(indexPoint, texture);
	texture->showOnRender(true);
}

void View::updateGameScreen() {
	SDL_SetRenderTarget(this->_renderer, NULL);
	SDL_SetRenderDrawBlendMode(this->_renderer, SDL_BLENDMODE_BLEND);
	SDL_RenderClear(this->_renderer);

	this->_boardBackground->renderTexture(this->_renderer);
	this->_boardTextureClass->renderTexture(this->_renderer);

	this->_firsPlayerHelperStoneTexture->renderTexture(this->_renderer);
	this->_firsPlayerHelperStoneTexture->showOnRender(false);
	this->_secondPlayerHelperStoneTexture->renderTexture(this->_renderer);
	this->_secondPlayerHelperStoneTexture->showOnRender(false);
	for (SDLTextureClass *element : this->_textures) {
		element->renderTexture(this->_renderer);
	}
	SDL_RenderPresent(this->_renderer);
}

void View::_setBoardBackground(const char *img_file_path) {
	SDL_Texture		*boardBackgroundTexture;
	SDL_Texture		*boardTexture;
	SDLTextureClass imageTexture(img_file_path, NULL, NULL, this->_renderer);

	this->_debugMessage("Setting up Board background.");

	boardTexture = SDL_CreateTexture(this->_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
			this->_width, this->_height);
	SDL_SetTextureBlendMode(boardTexture, SDL_BLENDMODE_BLEND);
	this->_boardTextureClass = new SDLTextureClass(boardTexture, "Board texture");

	boardBackgroundTexture = SDL_CreateTexture(this->_renderer, SDL_PIXELFORMAT_RGBA8888,
								SDL_TEXTUREACCESS_TARGET, this->_width, this->_height);

	this->_boardBackground = new SDLTextureClass(boardBackgroundTexture, "Board background");
	this->_boardBackground->setAsRenderTarget(this->_renderer);
	imageTexture.renderTexture(this->_renderer);
	this->_renderBackgroundBoard();

	SDL_SetRenderTarget(this->_renderer, NULL);
}

void View::putStoneOnBoard(SDL_Point indexPoint, int playerNumber) {
	SDLTextureClass	*texture;

	texture = playerNumber == FIRST_PLAYER ? this->_firstPlayerStoneTexture : this->_secondPlayerStoneTexture;
	this->_placeTextureByIndexPoint(indexPoint, texture);
	this->_boardTextureClass->setAsRenderTarget(this->_renderer);
	texture->renderTexture(this->_renderer);
	SDL_SetRenderTarget(this->_renderer, NULL);
}

void View::_placeTextureByIndexPoint(SDL_Point indexPoint, SDLTextureClass *textureToPlace) {
	SDL_Rect	rect;
	int			x;
	int			y;

	x = this->_boardCoordinates[indexPoint.x];
	y = this->_boardCoordinates[indexPoint.y];
	rect.x = x - this->_pointRadious;
	rect.y = y - this->_pointRadious;
	rect.w = this->_pointRadious * 2;
	rect.h = this->_pointRadious * 2;
	textureToPlace->setDstRenderRect(&rect);
}

void View::showWiningLine(Coordinates *coordinates, int size, const char *message) {
    SDL_Color   color;

	size = 0; //TODO DENYS ???

    this->_debugMessage("Showing winning window.");
    color = GREY_COLOR_SDL;
    color.a = 150;
	this->_textures[0]->clearTexture(this->_renderer, color);
	this->_textures[0]->setAsRenderTarget(this->_renderer);
	this->_renderText(message, this->_font46, 40, 40);
	this->putStoneOnBoard(*coordinates);
}

void View::updateAllBoard(GomokuMainBoard *board) {
	std::list<Coordinates>	            *coordinates;
	std::list<Coordinates>::iterator    iterator;

	this->_debugMessage("Updating all board.");
	coordinates = board->getPlacedCoordinates();
	this->_boardTextureClass->clearTexture(this->_renderer);
	for (iterator = coordinates->begin(); iterator != coordinates->end(); ++iterator) {
	    this->putStoneOnBoard(*iterator);
	}

	delete coordinates;
}

void View::putStoneOnBoard(Coordinates coordinates) {
    SDL_Point   point;

    point.x = coordinates.getX();
    point.y = coordinates.getY();
    this->putStoneOnBoard(point, coordinates.getPlayer());
}

void View::_renderText(const char *message, TTF_Font *font, int x, int y) {
	SDL_Rect	rect;
	SDL_Surface	*surfaceMessage;
	SDL_Texture	*texture;

	surfaceMessage = TTF_RenderText_Solid(font, message, BLACK_COLOR_SDL);
	texture = SDL_CreateTextureFromSurface(this->_renderer, surfaceMessage);
	SDL_QueryTexture(texture, NULL, NULL, &(rect.w), &(rect.h));
	rect.x = x;
	rect.y = y;
	SDL_RenderCopy(this->_renderer, texture, NULL, &rect);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surfaceMessage);
}
