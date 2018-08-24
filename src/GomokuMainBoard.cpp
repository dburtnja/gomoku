//
// Created by mirex on 04.07.2018.
//

#include "../headers/MainHeader.hpp"

GomokuMainBoard::GomokuMainBoard() :
        _boardSize (GOMOKU_BOARD_SIZE)
{
    int x;
    int y;

    for (x = 0; x < GOMOKU_BOARD_SIZE; x++)
    {
        for (y = 0; y < GOMOKU_BOARD_SIZE; y++)
        {
            board[x][y] = 0;
        }
    }
}

GomokuMainBoard::GomokuMainBoard(const GomokuMainBoard & toCopy) {
    * this = toCopy;
}

GomokuMainBoard & GomokuMainBoard::operator = (const GomokuMainBoard & rhs) {
    this->_boardSize = rhs._boardSize;
    return (* this);
}

//void GomokuMainBoard::putStoneOnBoard(SingleStone * newStone) {
////    std::cout << newStone->getCordY();
//    board[newStone->getCordX()][newStone->getCordY()] = newStone->getPlayer();
//}

void GomokuMainBoard::putStoneOnBoard(int x, int y, int plyaer) {
//    std::cout << newStone->getCordY();
    board[x][y] = plyaer;
    this->addNewSpots(x, y);
}

void GomokuMainBoard::addNewSpots(int x, int y) {
    for (int i = -1; i<= 1; i++)
    {
        for (int j = -1; j<= 1; j++)
        {
            if (i == 0 && j == 0)
                continue;
            if ((x + i >= 0 and x + i < GOMOKU_BOARD_SIZE) and (y + j >= 0 and y + j < GOMOKU_BOARD_SIZE)
                and checkForSameSpot(x + i,y + j) and this->board[x + i][y + j] == 0)
                this->availablespots.push_back(new AvailableSpot(x + i, y + j));
        }
    }

    deleteUsedSpot(x, y);
}

void GomokuMainBoard::clearStoneOnBoard(int x, int y) {


    this->dellOldSpots(x,y);
    board[x][y] = 0;

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
            std::cout << board[x][y] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";

}

//int ArtificialIntelligence::checkVictory(int (& Board)[GOMOKU_BOARD_SIZE][GOMOKU_BOARD_SIZE]) {
//    int victory = -1;
//
//    for (int i=0; i < GOMOKU_BOARD_SIZE; i++)
//    {
//        if (Board[i][0] == Board[i][1] && Board[i][1] == Board[i][2] && Board[i][0] != 0)
//        {
//            victory = Board[i][0];
//            break;
//        }
//        if (Board[0][i] == Board[1][i] && Board[1][i] == Board[2][i] && Board[0][i] != 0)
//        {
//            victory = Board[0][i];
//            break;
//        }
//        if (Board[0][0] == Board[1][1] && Board[2][2] == Board[0][0] && Board[0][0] != 0)
//        {
//            victory = Board[0][0];
//            break;
//        }
//        if (Board[0][2] == Board[1][1] && Board[2][0] == Board[0][2] && Board[0][2] != 0)
//        {
//            victory = Board[0][2];
//            break;
//        }
//        else victory = 0;
//    }
//    if (victory == 0)
//        for (int i = 0; i < GOMOKU_BOARD_SIZE; ++i) {
//            for (int j = 0; j <GOMOKU_BOARD_SIZE ; ++j) {
//                if (Board[i][j] == 0)
//                    victory = -1;
//            }
//        }
//    return victory;
//}
