//
// Created by mirex on 04.07.2018.
//

#include "../headers/MainHeader.hpp"
#include "../headers/GomokuMainBoard.hpp"

GomokuMainBoard::GomokuMainBoard() :
        _boardSize (GOMOKU_BOARD_SIZE)
{
    int x;
    int y;

    this->_players[0] = AI_PLAYER;
    this->_players[1] = HUMAN_PLAYER;
    this->_move = 0;
    for (x = 0; x < GOMOKU_BOARD_SIZE; x++)
    {
        for (y = 0; y < GOMOKU_BOARD_SIZE; y++)
        {
            board[x][y] = EMPTY_CELL;
        }
    }
}

GomokuMainBoard::GomokuMainBoard(const GomokuMainBoard & toCopy)
{
    * this = toCopy;
}

GomokuMainBoard & GomokuMainBoard::operator = (const GomokuMainBoard & rhs)
        {
    this->_boardSize = rhs._boardSize;
    return (* this);
}

bool GomokuMainBoard::putStoneOnBoard(int x, int y, int plyaer, int depth)
{

	if (board[x][y] != EMPTY_CELL)
        return false;
    board[x][y] = plyaer;
    (this->_move)++;

    this->addNewSpots(x, y, depth);
    return true;
}

void GomokuMainBoard::addNewSpots(int x, int y, int depth) {
    if (depth >= GOMOKU_BOARD_SIZE * GOMOKU_BOARD_SIZE - 2)
    {
        for (int i = -2; i<= 2; i++)
        {
            for (int j = -2; j<= 2; j++)
            {
                if (i == 0 && j == 0)
                    continue;
                if ((x + i >= 0 and x + i < GOMOKU_BOARD_SIZE) and (y + j >= 0 and y + j < GOMOKU_BOARD_SIZE)
                    and checkForSameSpot(x + i,y + j)
                    and this->board[x + i][y + j] == 0)
                    this->availablespots.push_back(new AvailableSpot(x + i, y + j));
                    //this->availablespots.insert(this->availablespots.begin(),  new AvailableSpot(x + i, y + j));
            }
        }
    }
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
                    and this->board[x + i][y + j] == 0)
                    this->availablespots.push_back(new AvailableSpot(x + i, y + j));
                    //this->availablespots.insert(this->availablespots.begin(),new AvailableSpot(x + i, y + j));
            }
        }
    }
    deleteUsedSpot(x, y);
}

void GomokuMainBoard::clearStoneOnBoard(int x, int y) {


    this->dellOldSpots(x,y);
    board[x][y] = 0;
    this->availablespots.push_back(new AvailableSpot(x,y));

}

void GomokuMainBoard::dellOldSpots(int x, int y) {
    for (int i = -1; i<= 1; i++)
    {
        for (int j = -1; j<= 1; j++)
        {
            if (i == 0 && j == 0)
                continue;
            if ((x + i >= 0 and x + i < GOMOKU_BOARD_SIZE) and (y + j >= 0 and y + j < GOMOKU_BOARD_SIZE))
                deleteUsedSpot(x + i , y + j);
        }
    }
}

void GomokuMainBoard::deleteUsedSpot(int x, int y) {
    int i = 0;
    for (auto & element: this->availablespots){
        if (element->getX() == x and element->getY() == y)
            this->availablespots.erase(this->availablespots.begin() + i);
        i++;
    }

}

bool GomokuMainBoard::checkForSameSpot(int x, int y) {
    for (auto & element: this->availablespots)
        if (element->getX() == x and element->getY() == y)
            return false;
    return true;
}

void GomokuMainBoard::printBoard() {
    int x;
    int y = -1;

    for (x = 0; x < GOMOKU_BOARD_SIZE; x++)
    {
        if (y == -1)
        {
            std::cout << "  |";
            for (y = 0; y < GOMOKU_BOARD_SIZE; y++)
            {
                std::cout << y;
                if (y < 10)
                    std::cout << " ";
            }
            std::cout << "\n";
            for (y = 0; y < GOMOKU_BOARD_SIZE; y++)
            {
                std::cout << "---";
            }
            std::cout << "\n";
        }
        std::cout.width(2);
        std::cout << x << "|";

        for (y = 0; y < GOMOKU_BOARD_SIZE; y++)
        {
            std::cout << board[y][x] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";

}

int checker(int (& element)[GOMOKU_BOARD_SIZE][GOMOKU_BOARD_SIZE], int (& board)[GOMOKU_BOARD_SIZE][GOMOKU_BOARD_SIZE])
{

    for (int i = 0; i < GOMOKU_BOARD_SIZE; ++i) {
        for (int j = 0; j < GOMOKU_BOARD_SIZE; ++j) {
            if (element[i][j] != board[i][j])
                return 1;
        }
    }
    return 0;
}


int GomokuMainBoard::getValue(int x, int y) {
    return (this->board[x][y]);
}

bool GomokuMainBoard::checkEmpty(int x, int y) {
    if (x < 0 || x > GOMOKU_BOARD_SIZE)
        return false;
    if (y < 0 || y > GOMOKU_BOARD_SIZE)
        return false;
    return this->board[x][y] == EMPTY_CELL;
}

void GomokuMainBoard::setValue(int x, int y, int c) {
    this->board[x][y] = c;
}

bool GomokuMainBoard::rowOfFive(int x, int y){
    //check for rows
    int temp = 1;
    int i = 1;
    //bool five = false;

    while (y - i >= 0 && board[x][y - i] == board[x][y]){
        temp++;
        i++;
    }
    i = 1;

    while (y + i <= GOMOKU_BOARD_SIZE-1 && board[x][y+i] == board[x][y]){
        temp++;
        i++;
    }

    return (temp >= POINTS_TO_WIN);

}

bool GomokuMainBoard::columnOfFive(int x, int y){
    //check for columns
    int temp = 1;
    int i = 1;
    //bool five = false;

    while (x-i >= 0 && board[x-i][y] == board[x][y]){
        temp++;
        i++;
    }
    i = 1;

    while (x + i <= GOMOKU_BOARD_SIZE-1 && board[x+i][y] == board[x][y]){
        temp++;
        i++;
    }
    return (temp >= POINTS_TO_WIN);
}

bool GomokuMainBoard::mainDiagnolOfFive(int x, int y){
    //check for main diagnol
    int temp = 1;
    int i = 1;
    //bool five = false;

    while (x-i >= 0 && y - i >= 0 && board[x-i][y-i] == board[x][y]){
        temp++;
        i++;
    }
    i = 1;

    while (x + i < GOMOKU_BOARD_SIZE && y + i < GOMOKU_BOARD_SIZE && board[x+i][y+i] == board[x][y]){
        temp++;
        i++;
    }
    return (temp >= POINTS_TO_WIN);
}

bool GomokuMainBoard::reverseDiagnolOfFive(int x, int y){
    //check for reverse diagnol
    int temp = 1;
    int i = 1;
    //bool five = false;

    while (x-i >= 0 && y + i < GOMOKU_BOARD_SIZE && board[x-i][y+i] == board[x][y]){
        temp++;
        i++;
    }
    i = 1;
//    if (temp >=5)
//        five = true;
//    temp = 1;
    while (x + i < GOMOKU_BOARD_SIZE && y - i >= 0 && board[x+i][y-i] == board[x][y]){
        temp++;
        i++;
    }
    return (temp >= POINTS_TO_WIN);
}

bool GomokuMainBoard::win(int x, int y){
    return rowOfFive(x,y) || columnOfFive(x,y) || mainDiagnolOfFive(x,y) || reverseDiagnolOfFive(x,y);
}


bool GomokuMainBoard::rowOfTwo(int x, int y, int attack, int feed, bool needToRemove, std::vector<Coordinates*> & coordinatesList)
{
    if (getValue(x,y) == attack and getValue(x,y - 1) == feed and getValue(x,y - 2) == feed and getValue(x,y - 3) == attack) {
        if (needToRemove)
        {
            setValue(x, y - 1, 0);
            setValue(x, y - 2, 0);
            availablespots.push_back(new AvailableSpot(x, y - 1));
            coordinatesList.push_back(new Coordinates(x, y - 1, EMPTY_CELL));
            availablespots.push_back(new AvailableSpot(x, y - 2));
            coordinatesList.push_back(new Coordinates(x, y - 2, EMPTY_CELL));

        }

        return true;
    }
    else if (getValue(x,y) == attack and getValue(x,y + 1) == feed and getValue(x,y + 2) == feed and getValue(x,y + 3) == attack)
    {
        if (needToRemove)
        {
            setValue(x, y + 1, 0);
            setValue(x, y + 2, 0);
            availablespots.push_back(new AvailableSpot(x, y + 1));
            coordinatesList.push_back(new Coordinates(x, y + 1, EMPTY_CELL));

            availablespots.push_back(new AvailableSpot(x, y + 2));
            coordinatesList.push_back(new Coordinates(x, y + 2, EMPTY_CELL));

        }
        return true;
    }

    return false;}

bool GomokuMainBoard::columnOfTwo(int x, int y, int attack, int feed, bool needToRemove, std::vector<Coordinates*> & coordinatesList)
{
    if (getValue(x,y) == attack and getValue(x - 1,y) == feed and getValue(x - 2,y) == feed and getValue(x - 3, y) == attack)
    {
        if (needToRemove)
        {
            setValue(x - 1, y, 0);
            setValue(x - 2, y, 0);
            availablespots.push_back(new AvailableSpot(x - 1, y));
            coordinatesList.push_back(new Coordinates(x - 1, y, EMPTY_CELL));
            availablespots.push_back(new AvailableSpot(x - 2, y));
            coordinatesList.push_back(new Coordinates(x - 2, y, EMPTY_CELL));

        }
        return true;
    }
    else if (getValue(x, y) == attack and getValue(x + 1, y) == feed and getValue(x + 2, y) == feed and getValue(x + 3,y) == attack)
    {
        if (needToRemove)
        {
            setValue(x + 1, y, 0);
            setValue(x + 2, y, 0);
            availablespots.push_back(new AvailableSpot(x + 1, y));
            coordinatesList.push_back(new Coordinates(x + 1, y, EMPTY_CELL));

            availablespots.push_back(new AvailableSpot(x + 2, y));
            coordinatesList.push_back(new Coordinates(x + 2, y, EMPTY_CELL));

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
            setValue(x - 1, y - 1, 0);
            setValue(x - 2, y - 2, 0);
            availablespots.push_back(new AvailableSpot(x - 1, y - 1));
            coordinatesList.push_back(new Coordinates(x - 1, y - 1, EMPTY_CELL));

            availablespots.push_back(new AvailableSpot(x - 2, y - 2));
            coordinatesList.push_back(new Coordinates(x - 2, y - 2, EMPTY_CELL));

        }
        return true;
    }
    else if (getValue(x, y) == attack and getValue(x + 1, y + 1) == feed and getValue(x + 2, y + 2) == feed and getValue(x + 3, y + 3) == attack)
    {
        if (needToRemove)
        {
            setValue(x + 1, y + 1, 0);
            setValue(x + 2, y + 2, 0);
            availablespots.push_back(new AvailableSpot(x + 1, y + 1));
            coordinatesList.push_back(new Coordinates(x + 1, y + 1, EMPTY_CELL));

            availablespots.push_back(new AvailableSpot(x + 2, y + 2));
            coordinatesList.push_back(new Coordinates(x + 2, y + 2, EMPTY_CELL));

        }
        return true;
    }
    return false;}

bool GomokuMainBoard::reverseDiagnolOfTwo(int x, int y, int attack, int feed, bool needToRemove, std::vector<Coordinates*> & coordinatesList)
{
    if (getValue(x, y) == attack and getValue(x + 1, y - 1) == feed and getValue(x + 2, y - 2) == feed and getValue(x + 3, y - 3) == attack)
    {
        if (needToRemove)
        {
            setValue(x + 1, y - 1, 0);
            setValue(x + 2, y - 2, 0);
            availablespots.push_back(new AvailableSpot(x + 1, y - 1));
            coordinatesList.push_back(new Coordinates(x + 1, y - 1, EMPTY_CELL));

            availablespots.push_back(new AvailableSpot(x + 2, y - 2));
            coordinatesList.push_back(new Coordinates(x + 2, y - 2, EMPTY_CELL));

        }
        return true;
    }
    else if (getValue(x, y) == attack and getValue(x - 1, y + 1) == feed and getValue(x - 2, y + 2) == feed and getValue(x - 3, y + 3) == attack)
    {
        if (needToRemove)
        {
            setValue(x - 1, y + 1, 0);
            setValue(x - 2, y + 2, 0);
            availablespots.push_back(new AvailableSpot(x - 1, y + 1));
            coordinatesList.push_back(new Coordinates(x - 1, y + 1, EMPTY_CELL));

            availablespots.push_back(new AvailableSpot(x - 2, y + 2));
            coordinatesList.push_back(new Coordinates(x - 2, y + 2, EMPTY_CELL));

        }
        return true;
    }

    return false;
}

int GomokuMainBoard::check_for_capture(int x, int y, int attack, int feed, bool needToRemove, std::vector<Coordinates*> & coordinatesList)
{
    bool ready_for_capture = rowOfTwo(x,y, attack, feed, needToRemove, coordinatesList) || columnOfTwo(x,y, attack, feed, needToRemove, coordinatesList)
            || mainDiagnolOfTwo(x,y, attack, feed, needToRemove ,coordinatesList) || reverseDiagnolOfTwo(x,y, attack, feed, needToRemove ,coordinatesList);
    if (ready_for_capture && needToRemove == true)
    {
        if (attack == AI_PLAYER)
            ai_capture++;
        else
            player_capture++;
    }
    else if (ready_for_capture)
    {
        //printf("CAPTURE %d, %d \n", x, y);
       // if (attack == AI_PLAYER)
            return 2500000 * (ai_capture + 1) + (int) std::pow(8, ai_capture);
        //else
            //return -(30000 * (ai_capture + 1) + (int) std::pow(8, ai_capture));
    }
    return 0;
}

bool GomokuMainBoard::draw(){
    if (count == GOMOKU_BOARD_SIZE*GOMOKU_BOARD_SIZE){
        return true;
    }
    return false;
}

std::string GomokuMainBoard::toString() {
    std::string s = "";
    for (int i = 0; i < GOMOKU_BOARD_SIZE; i++){
        for (int j = 0 ; j < GOMOKU_BOARD_SIZE; j++){
            s+= getValue(i, j) + '0';
        }
    }
    return s;
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
            if (value != EMPTY_CELL)
                coordinates->push_back(Coordinates(x, y, value));
        }
    }
    return coordinates;
}

