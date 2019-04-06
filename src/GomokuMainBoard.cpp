//
// Created by mirex on 04.07.2018.
//

#include "../headers/GomokuMainBoard.hpp"
#include "../headers/APlayer.hpp"
class APlayer;

GomokuMainBoard::GomokuMainBoard() :
        _boardSize (GOMOKU_BOARD_SIZE)
{
    int x;
    int y;

    this->_players[0] = FIRST_PLAYER_ON_MAP;
    this->_players[1] = SECOND_PLAYER_ON_MAP;
    this->_move = 0;
    for (x = 0; x < GOMOKU_BOARD_SIZE; x++)
    {
        for (y = 0; y < GOMOKU_BOARD_SIZE; y++)
        {
            board[x][y] = EMPTY_CELL_ON_MAP;
        }
    }
}

GomokuMainBoard::GomokuMainBoard(const GomokuMainBoard & toCopy)
{
    * this = toCopy;
}

GomokuMainBoard::~GomokuMainBoard() {}

GomokuMainBoard & GomokuMainBoard::operator = (const GomokuMainBoard & rhs){
    this->_boardSize = rhs._boardSize;
    return (* this);
}

bool GomokuMainBoard::putStoneOnBoard(int x, int y, int plyaer, int depth)
{
	if (board[x][y] != EMPTY_CELL_ON_MAP)
        return false;
    board[x][y] = plyaer;
    (this->_move)++;
    this->addNewSpots(x, y, depth);
    return true;
}

void GomokuMainBoard::addNewSpots(int x, int y, int depth) {
    if (depth > 0)
    {
        for (int i = -1; i<= 1; i++)
        {
            for (int j = -1; j<= 1; j++)
            {
                if (i == 0 && j == 0)
                    continue;
                if ((x + i >= 0 and x + i < GOMOKU_BOARD_SIZE) and (y + j >= 0 and y + j < GOMOKU_BOARD_SIZE)
                    and checkForSameSpot(x + i,y + j)
                    and this->board[x + i][y + j] == EMPTY_CELL_ON_MAP)
                {
                    AvailableSpot newSpot;
                    newSpot.setX(x + i);
                    newSpot.setY(y + j);
                    this->availablespots.push_back(newSpot);
                }
            }
        }
    }
    deleteUsedSpot(x, y);
}

void GomokuMainBoard::deleteUsedSpot(int x, int y) {
    int i = 0;

    for (auto & element: this->availablespots){
        if (element.getX() == x and element.getY() == y)
            this->availablespots.erase(this->availablespots.begin() + i);
        i++;
    }
}

bool GomokuMainBoard::checkForSameSpot(int x, int y) {
    for (auto & element: this->availablespots)
        if (element.getX() == x and element.getY() == y)
            return false;
    return true;
}

int GomokuMainBoard::getValue(int x, int y) {
    return (this->board[x][y]);
}

bool GomokuMainBoard::checkEmpty(int x, int y) {
    if (x < 0 || x > GOMOKU_BOARD_SIZE || y < 0 || y > GOMOKU_BOARD_SIZE)
        return false;
    return this->board[x][y] == EMPTY_CELL_ON_MAP;
}

void GomokuMainBoard::setValue(int x, int y, int c) {
    this->board[x][y] = c;
}

bool GomokuMainBoard::rowOfFive(int x, int y, Move *move){
    int temp = 1;
    int i = 1;
    bool five;

    while (y + i <= GOMOKU_BOARD_SIZE-1 && board[x][y+i] == board[x][y]){
        if (move)
            move->coordinatesList.push_back(new Coordinates(x, y + i, board[x][y]));
        temp++;
        i++;
    }
    i = 1;
    while (y - i >= 0 && board[x][y - i] == board[x][y]){
        if (move)
            move->coordinatesList.push_back(new Coordinates(x, y - i, board[x][y]));
        temp++;
        i++;
    }
    five = temp >= POINTS_TO_WIN;
    if (move and !five)
        this->_clearMove(move);
    return (five);
}

bool GomokuMainBoard::columnOfFive(int x, int y, Move *move){
    int temp = 1;
    int i = 1;
    bool five;

    while (x + i <= GOMOKU_BOARD_SIZE-1 && board[x+i][y] == board[x][y]){
        if (move)
            move->coordinatesList.push_back(new Coordinates(x+i, y, board[x][y]));
        temp++;
        i++;
    }
    i = 1;
    while (x-i >= 0 && board[x-i][y] == board[x][y]){
        if (move)
            move->coordinatesList.push_back(new Coordinates(x-i, y, board[x][y]));
        temp++;
        i++;
    }
    five = temp >= POINTS_TO_WIN;
    if (move and !five)
        this->_clearMove(move);
    return (five);
}

bool GomokuMainBoard::mainDiagnolOfFive(int x, int y, Move *move){
    int temp = 1;
    int i = 1;
    bool five;

    while (x + i < GOMOKU_BOARD_SIZE && y + i < GOMOKU_BOARD_SIZE && board[x+i][y+i] == board[x][y]){
        if (move)
            move->coordinatesList.push_back(new Coordinates(x+i, y+i, board[x][y]));
        temp++;
        i++;
    }
    i = 1;
    while (x-i >= 0 && y - i >= 0 && board[x-i][y-i] == board[x][y]){
        if (move)
            move->coordinatesList.push_back(new Coordinates(x-i, y-i, board[x][y]));
        temp++;
        i++;
    }
    five = temp >= POINTS_TO_WIN;
    if (move and !five)
        this->_clearMove(move);
    return (five);
}

bool GomokuMainBoard::reverseDiagnolOfFive(int x, int y, Move *move){
    int temp = 1;
    int i = 1;
    bool five;

    while (x + i < GOMOKU_BOARD_SIZE && y - i >= 0 && board[x+i][y-i] == board[x][y]){
        if (move)
            move->coordinatesList.push_back(new Coordinates(x+i, y-i, board[x][y]));
        temp++;
        i++;
    }
    i = 1;
    while (x-i >= 0 && y + i < GOMOKU_BOARD_SIZE && board[x-i][y+i] == board[x][y]){
        if (move)
            move->coordinatesList.push_back(new Coordinates(x-i, y+i, board[x][y]));
        temp++;
        i++;
    }
    five = temp >= POINTS_TO_WIN;
    if (move and !five)
        this->_clearMove(move);
    return (five);
}

bool GomokuMainBoard::win(int x, int y) {
    return rowOfFive(x,y, nullptr) || columnOfFive(x,y, nullptr) ||
    mainDiagnolOfFive(x,y, nullptr) || reverseDiagnolOfFive(x,y, nullptr);
}

bool GomokuMainBoard::win(int x, int y, Move *move){
    Move    tempMove{};

    if (rowOfFive(x,y, &tempMove) || columnOfFive(x,y, &tempMove) ||
    mainDiagnolOfFive(x,y, &tempMove) || reverseDiagnolOfFive(x,y, &tempMove)) {
        for (auto coordinate : tempMove.coordinatesList) {
            move->coordinatesList.push_back(coordinate);
        }
        return true;
    }
    return false;
}

void GomokuMainBoard::_clearMove(Move *move) {
    if (move) {
        for (auto coordinate : move->coordinatesList) {
            delete coordinate;
        }
        move->coordinatesList.clear();
    }
}

void GomokuMainBoard::setValueAndAddNewSpot(int x, int y, int symbol) {
    AvailableSpot newSpot;

    this->board[x][y] = symbol;
    newSpot.setX(x);
    newSpot.setY(y);
    this->availablespots.push_back(newSpot);
}

bool GomokuMainBoard::rowOfTwo(int x, int y, int attack, int feed, bool needToRemove, std::vector<Coordinates*> & coordinatesList)
{
    if (getValue(x,y) == attack and getValue(x,y - 1) == feed and getValue(x,y - 2) == feed and getValue(x,y - 3) == attack) {
        if (needToRemove)
        {
            setValueAndAddNewSpot(x, y - 1, EMPTY_CELL_ON_MAP);
            setValueAndAddNewSpot(x, y - 2, EMPTY_CELL_ON_MAP);
            coordinatesList.push_back(new Coordinates(x, y - 1, EMPTY_CELL_ON_MAP));
            coordinatesList.push_back(new Coordinates(x, y - 2, EMPTY_CELL_ON_MAP));
        }

        return true;
    }
    else if (getValue(x,y) == attack and getValue(x,y + 1) == feed and getValue(x,y + 2) == feed and getValue(x,y + 3) == attack)
    {
        if (needToRemove)
        {
            setValueAndAddNewSpot(x, y + 1, EMPTY_CELL_ON_MAP);
            setValueAndAddNewSpot(x, y + 2, EMPTY_CELL_ON_MAP);
            coordinatesList.push_back(new Coordinates(x, y + 1, EMPTY_CELL_ON_MAP));
            coordinatesList.push_back(new Coordinates(x, y + 2, EMPTY_CELL_ON_MAP));
        }
        return true;
    }
    return false;
}

bool GomokuMainBoard::columnOfTwo(int x, int y, int attack, int feed, bool needToRemove, std::vector<Coordinates*> & coordinatesList)
{
    if (getValue(x,y) == attack and getValue(x - 1,y) == feed and getValue(x - 2,y) == feed and getValue(x - 3, y) == attack)
    {
        if (needToRemove)
        {
            setValueAndAddNewSpot(x - 1, y, EMPTY_CELL_ON_MAP);
            setValueAndAddNewSpot(x - 2, y, EMPTY_CELL_ON_MAP);
            coordinatesList.push_back(new Coordinates(x - 1, y, EMPTY_CELL_ON_MAP));
            coordinatesList.push_back(new Coordinates(x - 2, y, EMPTY_CELL_ON_MAP));
        }
        return true;
    }
    else if (getValue(x, y) == attack and getValue(x + 1, y) == feed and getValue(x + 2, y) == feed and getValue(x + 3,y) == attack)
    {
        if (needToRemove)
        {
            setValueAndAddNewSpot(x + 1, y, EMPTY_CELL_ON_MAP);
            setValueAndAddNewSpot(x + 2, y, EMPTY_CELL_ON_MAP);
            coordinatesList.push_back(new Coordinates(x + 1, y, EMPTY_CELL_ON_MAP));
            coordinatesList.push_back(new Coordinates(x + 2, y, EMPTY_CELL_ON_MAP));
        }
        return true;
    }
    return false;
}

bool GomokuMainBoard::mainDiagnolOfTwo(int x, int y, int attack, int feed, bool needToRemove, std::vector<Coordinates*> & coordinatesList)
{

    if (getValue(x, y) == attack and getValue(x - 1, y - 1) == feed and getValue(x - 2, y - 2) == feed and getValue(x - 3, y - 3) == attack)
    {
        if (needToRemove)
        {
            setValueAndAddNewSpot(x - 1, y - 1, EMPTY_CELL_ON_MAP);
            setValueAndAddNewSpot(x - 2, y - 2, EMPTY_CELL_ON_MAP);
            coordinatesList.push_back(new Coordinates(x - 1, y - 1, EMPTY_CELL_ON_MAP));
            coordinatesList.push_back(new Coordinates(x - 2, y - 2, EMPTY_CELL_ON_MAP));
        }
        return true;
    }
    else if (getValue(x, y) == attack and getValue(x + 1, y + 1) == feed and getValue(x + 2, y + 2) == feed and getValue(x + 3, y + 3) == attack)
    {
        if (needToRemove)
        {
            setValueAndAddNewSpot(x + 1, y + 1, EMPTY_CELL_ON_MAP);
            setValueAndAddNewSpot(x + 2, y + 2, EMPTY_CELL_ON_MAP);
            coordinatesList.push_back(new Coordinates(x + 1, y + 1, EMPTY_CELL_ON_MAP));
            coordinatesList.push_back(new Coordinates(x + 2, y + 2, EMPTY_CELL_ON_MAP));
        }
        return true;
    }
    return false;
}

bool GomokuMainBoard::reverseDiagnolOfTwo(int x, int y, int attack, int feed, bool needToRemove, std::vector<Coordinates*> & coordinatesList)
{
    if (getValue(x, y) == attack and getValue(x + 1, y - 1) == feed and getValue(x + 2, y - 2) == feed and getValue(x + 3, y - 3) == attack)
    {
        if (needToRemove)
        {
            setValueAndAddNewSpot(x + 1, y - 1, EMPTY_CELL_ON_MAP);
            setValueAndAddNewSpot(x + 2, y - 2, EMPTY_CELL_ON_MAP);
            coordinatesList.push_back(new Coordinates(x + 1, y - 1, EMPTY_CELL_ON_MAP));
            coordinatesList.push_back(new Coordinates(x + 2, y - 2, EMPTY_CELL_ON_MAP));
        }
        return true;
    }
    else if (getValue(x, y) == attack and getValue(x - 1, y + 1) == feed and getValue(x - 2, y + 2) == feed and getValue(x - 3, y + 3) == attack)
    {
        if (needToRemove)
        {
            setValueAndAddNewSpot(x - 1, y + 1, EMPTY_CELL_ON_MAP);
            setValueAndAddNewSpot(x - 2, y + 2, EMPTY_CELL_ON_MAP);
            coordinatesList.push_back(new Coordinates(x - 1, y + 1, EMPTY_CELL_ON_MAP));
            coordinatesList.push_back(new Coordinates(x - 2, y + 2, EMPTY_CELL_ON_MAP));
        }
        return true;
    }
    return false;
}

int GomokuMainBoard::check_for_capture(int x, int y, APlayer * attack, APlayer * feed, bool needToRemove, std::vector<Coordinates*> & coordinatesList)
{
    bool ready_for_capture =
            rowOfTwo(x,y, attack->getPlayerSymbol(), feed->getPlayerSymbol(), needToRemove, coordinatesList)
            || columnOfTwo(x,y, attack->getPlayerSymbol(), feed->getPlayerSymbol(), needToRemove, coordinatesList)
            || mainDiagnolOfTwo(x,y, attack->getPlayerSymbol(), feed->getPlayerSymbol(), needToRemove ,coordinatesList)
            || reverseDiagnolOfTwo(x,y, attack->getPlayerSymbol(), feed->getPlayerSymbol(), needToRemove ,coordinatesList);
    if (ready_for_capture && needToRemove == true)
        attack->increaseCapture(2);
    else if (ready_for_capture)
    {
        if (attack->getPlayerCapture() >= 10)
            return INT_MAX;
        if (attack->getPlayerCapture() >= 8)
            return INT_MAX - 1000;
        return 2500000 * (attack->getPlayerCapture() + 1) + (int) std::pow(25, attack->getPlayerCapture());
    }
    return 0;
}

bool GomokuMainBoard::draw(){
    for (int i = 0; i < GOMOKU_BOARD_SIZE; i++){
        for (int j = 0 ; j < GOMOKU_BOARD_SIZE; j++){
            if (board[i][j] == EMPTY_CELL_ON_MAP)
                return false;
        }
    }
    return true;
}

int GomokuMainBoard::getBoardSize() {
    return this->_boardSize;
}

int GomokuMainBoard::getPlayer() {
    return this->_players[this->_move % 2];
}

int GomokuMainBoard::getPlayer(int move) {
    return this->_players[move % 2];
}

void GomokuMainBoard::setMoveCounter(int move)
{
    _move = move;
}

std::list<Coordinates> * GomokuMainBoard::getPlacedCoordinates() {
    std::list<Coordinates> *coordinates;
    int                     value;

    coordinates = new std::list<Coordinates>;
    for (unsigned int x = 0; x < this->_boardSize; x++) {
        for (unsigned int y = 0; y < this->_boardSize; y++) {
            value = this->getValue(x, y);
            if (value != EMPTY_CELL_ON_MAP)
                coordinates->push_back(Coordinates(x, y, value));
        }
    }
    return coordinates;
}



