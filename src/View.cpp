//
// Created by denys on 15.03.19.
//


#include <iostream>
#include <sys/stat.h>


#include "../headers/View.hpp"
#include "../headers/Widget.hpp"
#include "../headers/WidgetButton.hpp"
#include "../headers/WidgetButtonGroup.hpp"
#include "../headers/ArtificialIntelligence.hpp"
#include "../headers/WidgetLabel.hpp"
#include "../headers/WidgetMenuField.hpp"

View	*View::_selfInstance = nullptr;

View::View(int width, int height, char const *name, GomokuMainBoard *board, Uint32 sleep_time) {
	View::_selfInstance = this;
	this->_debug = false;
	this->_width = width;
	this->_height = height;
	this->_name = name;
	this->_sleep_time = sleep_time;
	this->_running = true;
	this->_menuValues = new std::map<std::string, long>;
	this->_firsPlayerHelperStoneTexture = nullptr;
	this->_secondPlayerHelperStoneTexture = nullptr;
	this->_firstPlayerStoneTexture = nullptr;
	this->_secondPlayerStoneTexture = nullptr;
	this->_boardBackground = nullptr;
	this->_boardTextureClass = nullptr;
	this->_menuWidget = nullptr;

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
    SDLTextureClass *textureClass;
    SDL_Texture     *texture;


    this->_debugMessage("Creating textures");

    this->_font24 = TTF_OpenFont(FONT_FILE, FONT_SIZE_24);
    this->_font46 = TTF_OpenFont(FONT_FILE, FONT_SIZE_46);
    if (!this->_font24 or !this->_font46) {
        std::cout << "Creating fonts error" << std::endl;
        std::cout << TTF_GetError() << std::endl;
        exit(-1);
    }

	texture = SDL_CreateTexture(this->_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
								this->_width, this->_height);

    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    textureClass = new SDLTextureClass(texture);
    textureClass->clearTexture(this->_renderer);
	this->_textures.push_back(textureClass);

	texture = SDL_CreateTexture(this->_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
								this->_width, this->_height);
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    textureClass = new SDLTextureClass(texture);
    textureClass->clearTexture(this->_renderer);
    this->_textures.push_back(textureClass);
}

void View::_debugMessage(const char *message) {
	if (this->_debug)
		std::cout <<  message << std::endl;
}

View::~View() {
	this->_debugMessage("Free View memory.");
	TTF_CloseFont(this->_font24);
	TTF_CloseFont(this->_font46);
	for (SDLTextureClass *texture : this->_textures)
		delete texture;
	delete [] this->_boardCoordinates;
	delete this->_firsPlayerHelperStoneTexture;
	delete this->_secondPlayerHelperStoneTexture;
	delete this->_firstPlayerStoneTexture;
	delete this->_secondPlayerStoneTexture;
	delete this->_boardBackground;
	delete this->_boardTextureClass;
	delete this->_menuWidget;
	delete this->_menuValues;
	SDL_DestroyRenderer(this->_renderer);
	SDL_DestroyWindow(this->_window);
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}

void View::_setStartWidgets(std::vector<Widget *> *widgets, WidgetButton **startButton) {
    WidgetButtonGroup		*firstPlayerSelection;
    WidgetButtonGroup		*secondPlayerSelection;

    *startButton = new WidgetButton(CENTER(this->_width, 100), this->_height - 100, 50, 100);
    (*startButton)->setBackgroundColor(RED_COLOR_SDL);
    (*startButton)->setBackgroundAlphaColor(150);
    (*startButton)->setText("RUN!", WHITE_COLOR_SDL);

    firstPlayerSelection = new WidgetButtonGroup(100, this->_height - 300, 190, 400);
    firstPlayerSelection->setBackgroundColor(GREY_COLOR_SDL);
    firstPlayerSelection->setBackgroundAlphaColor(50);
    firstPlayerSelection->addButton(10, 10, 50, 380, "Computer", true);
    firstPlayerSelection->addButton(10, 70, 50, 380, "Human");
    firstPlayerSelection->addButton(10, 130, 50, 380, "Computer & Human");

    secondPlayerSelection = new WidgetButtonGroup(this->_width - 500, this->_height - 300, 190, 400);
    secondPlayerSelection->setBackgroundAlphaColor(50);
    secondPlayerSelection->addButton(10, 10, 50, 380, "Computer");
    secondPlayerSelection->addButton(10, 70, 50, 380, "Human", true);
    secondPlayerSelection->addButton(10, 130, 50, 380, "Computer & Human");

    widgets->push_back(firstPlayerSelection);
    widgets->push_back(secondPlayerSelection);
    widgets->push_back(*startButton);
}

void View::_freeStartWindowMemory(SDL_Texture *texture, std::vector<Widget *> widgets) {
    delete reinterpret_cast<WidgetButtonGroup *>(widgets[0]);
    delete reinterpret_cast<WidgetButtonGroup *>(widgets[1]);
    delete reinterpret_cast<WidgetButton *>(widgets[2]);
    SDL_DestroyTexture(texture);
}

bool	View::showStartWindowAndWaitForStart(const char *img_file_path, int *players) {
	SDL_Texture				*texture = nullptr;
	SDL_Event				event;
    WidgetButton    		*startButton;
    std::vector<Widget*>	widgets;

    event = SDL_Event{};
    this->_setStartWidgets(&widgets, &startButton);

	texture = this->_loadImage(img_file_path);
	if (texture == nullptr) {
		std::cout << "Empty texture." << std::endl;
		return false;
	}
	SDL_RenderCopy(this->_renderer, texture, NULL, NULL);
	SDL_RenderPresent(this->_renderer);

	while (this->isRunning()) {
        while (this->pullEvent(&event)) {
            if (startButton->isClicked()) {
            	players[FIRST_PLAYER_POSITION] =
            	        reinterpret_cast<WidgetButtonGroup*>(widgets[FIRST_PLAYER_POSITION])->getSelected() + 1;
            	players[SECOND_PLAYER_POSITION] =
                        reinterpret_cast<WidgetButtonGroup*>(widgets[SECOND_PLAYER_POSITION])->getSelected() + 1;
            	this->_freeStartWindowMemory(texture, widgets);
                return true;
            }
            for (auto *widget : widgets) {
                widget->checkEvent(&event);
            }
            SDL_RenderClear(this->_renderer);
            SDL_RenderCopy(this->_renderer, texture, NULL, NULL);
            for (auto *widget : widgets) {
                widget->render(this->_renderer);
            }
            startButton->render(this->_renderer);
            SDL_RenderPresent(this->_renderer);
        }
        SDL_Delay(this->_sleep_time);
	}
	this->_freeStartWindowMemory(texture, widgets);
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
	for (const auto &eventHandler : this->_eventHandlers)
		eventHandler(this, event);
	if (event->type == SDL_QUIT) {
		this->_running = false;
		return false;
	}
	return true;
}

bool View::showGameBoard(const char *img_file_path) {
	SDL_Event	event;

	this->_firstPlayerStoneTexture = new SDLTextureClass(CIRCLE_IMAGE_BLACK, nullptr, nullptr, this->_renderer);
	this->_secondPlayerStoneTexture = new SDLTextureClass(CIRCLE_IMAGE_WHITE, nullptr, nullptr, this->_renderer);
	this->_setBoardBackground(img_file_path);

	this->_firsPlayerHelperStoneTexture = new SDLTextureClass(HELPER_CIRCLE_IMAGE_BLACK,
															  nullptr, nullptr, this->_renderer);
	this->_secondPlayerHelperStoneTexture = new SDLTextureClass(HELPER_CIRCLE_IMAGE_BLACK,
																&BLACK_COLOR_SDL, &WHITE_COLOR_SDL, this->_renderer);
	this->_firsPlayerHelperStoneTexture->showOnRender(false);
	this->_secondPlayerHelperStoneTexture->showOnRender(false);

	while (this->pullEvent(&event));
	this->_debugMessage("First screen update.");
	this->updateGameScreen();
	return true;
}

void View::_renderBackgroundBoard() {
	int     firstCoordinate;
	int     lastCoordinate;
	int     textFirstCoordinate;
	char    numberMessage[3];
	char    charMessage[2];

	charMessage[1] = 0;
	firstCoordinate = this->_boardCoordinates[0];
	lastCoordinate = this->_boardCoordinates[this->_coordinatesLength - 1]; //todo check index
	textFirstCoordinate = firstCoordinate - this->_distance;
	for (int i = 0; i < this->_coordinatesLength; i++) {
		sprintf(numberMessage, "%d", i + 1);
		charMessage[0] = static_cast<char>('A' + i);
        this->_renderText(numberMessage, this->_font24, textFirstCoordinate, this->_boardCoordinates[i] - 20);
        this->_renderText(charMessage, this->_font24, this->_boardCoordinates[i], textFirstCoordinate);
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

	texture = playerNumber == FIRST_PLAYER_ON_MAP ? this->_firsPlayerHelperStoneTexture : this->_secondPlayerHelperStoneTexture;
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
	this->_menuWidget->render(this->_renderer);
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
	this->_boardTextureClass = new SDLTextureClass(boardTexture);
    this->_boardTextureClass->clearTexture(this->_renderer);
	boardBackgroundTexture = SDL_CreateTexture(this->_renderer, SDL_PIXELFORMAT_RGBA8888,
								SDL_TEXTUREACCESS_TARGET, this->_width, this->_height);

	this->_boardBackground = new SDLTextureClass(boardBackgroundTexture);
	this->_boardBackground->setAsRenderTarget(this->_renderer);
	imageTexture.renderTexture(this->_renderer);
	this->_renderBackgroundBoard();
	this->_addMenuPanel();
	SDL_SetRenderTarget(this->_renderer, NULL);
}


long View::_createValueOnMenu(std::string message, int y, const char *defaultValue) {
	long	widgetId;
	int		firstW;
	int		secondW;

	firstW = (this->_menuWidget->getW() / 3 * 2) - 10;
	widgetId = this->_menuWidget->addLabel(10, y, 30, firstW, message.c_str());
	if (widgetId < 0)
		return -1;
	this->_menuWidget->getWidgetById(widgetId)->
	setBackgroundColor(GREY_COLOR_SDL)->
	setBackgroundAlphaColor(150);

	if (!defaultValue or defaultValue[0] == 0)
        return -1;
	secondW = (this->_menuWidget->getW() / 3) - 20;
	widgetId = this->_menuWidget->addLabel(firstW + 20, y, 30, secondW, defaultValue);
	if (widgetId < 0)
		return -1;
	this->_menuWidget->getWidgetById(widgetId)->
			setBackgroundColor(GREY_COLOR_SDL)->
			setBackgroundAlphaColor(150);

	return widgetId;
}

void View::_addMenuPanel() {
    int                                     x;
    int                                     h;
    int				                        w;
    std::vector<std::vector<std::string>>   values;
    int							            insideY;
    long                                    widgetIg;

    this->_debugMessage("Adding menu panel.");
    insideY = 10;
    values = {
            {LAST_MOVE_MESSAGE, "0"},
			{MOVE_COUNTER_MESSAGE, "0"},
            {LAST_MOVE_TIME_MESSAGE, "0 s"},
            {"Captures", ""},
            {FIRST_PLAYER_CAPTURES_MESSAGE, "0"},
            {SECOND_PLAYER_CAPTURES_MESSAGE, "0"}
    };

    x = this->_boardCoordinates[this->_coordinatesLength - 1] + 50;
    h = this->_boardCoordinates[this->_coordinatesLength - 1] - this->_boardCoordinates[0];
    w =  this->_width - x - 50;

    this->_menuWidget = new WidgetMenuField(x, this->_boardCoordinates[0], h, w);
    this->_menuWidget->setBackgroundAlphaColor(50);

    this->_debugMessage("Adding values on menu.");
	for (const auto &value : values) {
        widgetIg = this->_createValueOnMenu(value[0], insideY, value[1].c_str());
        if (widgetIg >= 0)
            (*this->_menuValues)[value[0]] = widgetIg;
        insideY += 40;
    }
}

void View::putStoneOnBoard(SDL_Point indexPoint, int playerNumber) {
	SDLTextureClass	*texture;

	texture = playerNumber == FIRST_PLAYER_ON_MAP ? this->_firstPlayerStoneTexture : this->_secondPlayerStoneTexture;
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

void View::showWiningLine(const char *message, Move *winingMove) {
    SDL_Color   color;
    SDL_Event	event;

    this->_debugMessage("Showing winning window.");
    color = GREY_COLOR_SDL;
    color.a = 150;
	this->_textures[WIN_MESSAGE_TEXTURE]->clearTexture(this->_renderer, color);
	this->_textures[WIN_MESSAGE_TEXTURE]->setAsRenderTarget(this->_renderer);
	this->_renderText(message, this->_font46, 40, 40);

	for (auto coordinate : winingMove->coordinatesList)
	{
        this->_renderStone(coordinate);
        delete coordinate;
    }
	SDL_SetRenderTarget(this->_renderer, NULL);
	this->updateGameScreen();
	while (waitEvent(&event));
}

void View::updateAllBoard(GomokuMainBoard *board) {
	std::list<Coordinates>	            *coordinates;
	std::list<Coordinates>::iterator    iterator;

	this->_debugMessage("Updating all board.");
	coordinates = board->getPlacedCoordinates();
	this->_boardTextureClass->clearTexture(this->_renderer);

	for (auto coordinate : *coordinates)
		this->putStoneOnBoard(&coordinate);
	delete coordinates;
}

void View::putStoneOnBoard(Coordinates *coordinates) {
    SDL_Point   point;

    point.x = coordinates->getX();
    point.y = coordinates->getY();
    this->putStoneOnBoard(point, coordinates->getPlayer());
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

void View::addEventHandler(std::function<bool(View *view, SDL_Event *event)> eventHandler) {
	this->_eventHandlers.push_back(eventHandler);
}

void View::_renderStone(Coordinates *coordinates) {
	SDL_Point   	point;
	SDLTextureClass	*stoneTexture;

	point.x = coordinates->getX();
	point.y = coordinates->getY();
	stoneTexture = coordinates->getPlayer() == FIRST_PLAYER_ON_MAP
			? this->_firstPlayerStoneTexture : this->_secondPlayerStoneTexture;
	this->_placeTextureByIndexPoint(point, stoneTexture);
	stoneTexture->renderTexture(this->_renderer);
}

View *View::getInstance() {
	return View::_selfInstance;
}

void View::updateMove(Move &move) {
    for (auto coordinate : move.coordinatesList) {
    	if (coordinate->getPlayer() == EMPTY_CELL_ON_MAP) {
    	} else {
    		this->putStoneOnBoard(coordinate);
    	}
    	delete coordinate;
    }
}

void View::updateMenuValues(const Move &move) {
    char    value[100];

    sprintf(value, "%c.%d", move.coordinatesList[0]->getX() + 'A', move.coordinatesList[0]->getY() + 1);
    this->_updateTextInWidget(LAST_MOVE_MESSAGE, value);

	sprintf(value, "%d", move.moveCounter);
	this->_updateTextInWidget(MOVE_COUNTER_MESSAGE, value);

	sprintf(value, "%f s", move.moveTime);
	this->_updateTextInWidget(LAST_MOVE_TIME_MESSAGE, value);

	sprintf(value, "%i", move.capturePlayer_1);
	this->_updateTextInWidget(FIRST_PLAYER_CAPTURES_MESSAGE, value);

	sprintf(value, "%i", move.capturePlayer_2);
	this->_updateTextInWidget(SECOND_PLAYER_CAPTURES_MESSAGE, value);
}

void View::_updateTextInWidget(const char *widgetName, const char *newValue) {
	Widget	*label;

	label = this->_menuWidget->getWidgetById(this->_getIdFromWidgetValues(widgetName));
	if (label) {
		this->_debugMessage(widgetName);
		label->setText(newValue, BLACK_COLOR_SDL);
	}
}

long View::_getIdFromWidgetValues(const char *string) {
    if (this->_menuValues->find(string) != this->_menuValues->end()) {
        auto iterator = this->_menuValues->find(string);
        return iterator->second;
    }
    return -1;
}
