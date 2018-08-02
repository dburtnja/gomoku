//
// Created by Mirex on 30.07.2018.
//

#include <limits>
#include "../headers/MainHeader.hpp"



ArtificialIntelligence::ArtificialIntelligence() {}

ArtificialIntelligence::~ArtificialIntelligence() {}

ArtificialIntelligence::ArtificialIntelligence(const ArtificialIntelligence &toCopy) {
    * this = toCopy;

}
ArtificialIntelligence& ArtificialIntelligence::operator=(const ArtificialIntelligence &rhs) {
    return  (* this);
}

void ArtificialIntelligence::runAI(GomokuMainBoard * mainBoard, int player) {
    AiMove move;
    std::vector<AvailableSpot*> temp;

    temp = mainBoard->availablespots;
    move = minmaxSearch(mainBoard);
    mainBoard->availablespots = temp;
    mainBoard->putStoneOnBoard(move.x, move.y, player);
}

int ArtificialIntelligence::checkVictory(int (& Board)[GOMOKU_BOARD_SIZE][GOMOKU_BOARD_SIZE], int player) {
    int victory = -1;

    for (int i=0; i < GOMOKU_BOARD_SIZE; i++)
    {
        if (Board[i][0] == Board[i][1] && Board[i][1] == Board[i][2] && Board[i][0] != 0)
        {
            victory = Board[i][0];
            break;
        }
        if (Board[0][i] == Board[1][i] && Board[1][i] == Board[2][i] && Board[0][i] != 0)
        {
            victory = Board[0][i];
            break;
        }
        if (Board[0][0] == Board[1][1] && Board[2][2] == Board[0][0] && Board[0][0] != 0)
        {
            victory = Board[0][0];
            break;
        }
        if (Board[0][2] == Board[1][1] && Board[2][0] == Board[0][2] && Board[0][2] != 0)
        {
            victory = Board[0][2];
            break;
        }
        else victory = 0;
    }
    if (victory == 0)
        for (int i = 0; i < GOMOKU_BOARD_SIZE; ++i) {
            for (int j = 0; j <GOMOKU_BOARD_SIZE ; ++j) {
                if (Board[i][j] == 0)
                    victory = -1;
            }
        }
    return victory;
}

void ArtificialIntelligence::printBoard(int (& Board)[GOMOKU_BOARD_SIZE][GOMOKU_BOARD_SIZE]) {
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
        }
        std::cout.width(2);
        std::cout << x << "|";

        for (y = 0; y < GOMOKU_BOARD_SIZE; y++)
        {
            std::cout << Board[x][y] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

AiMove ArtificialIntelligence::minmaxSearch(GomokuMainBoard * mainBoard) {
    int score = 1000000;

    AiMove move{};

        for(auto & element: mainBoard->availablespots) {
            int x = element->getX();
            int y = element->getY();

           //mainBoard->board[x][y] = AI_PLAYER;
            mainBoard->putStoneOnBoard(x, y, AI_PLAYER);
            int temp = maxSearch(mainBoard, 0);

            if (temp < score) {
                score = temp;
                move.x = x;
                move.y = y;
            }
            mainBoard->board[x][y] = 0;
        }
        return move;
}

//AiMove ArtificialIntelligence::minmaxSearch(GomokuMainBoard * mainBoard) {
//    int score = 1000000;
//
//    AiMove move{};
//    for (unsigned int i = 0; i < GOMOKU_BOARD_SIZE; i++) {
//        for (unsigned int j = 0; j < GOMOKU_BOARD_SIZE; j++) {
//            if (mainBoard->board[i][j] == 0) {
//                mainBoard->board[i][j] = AI_PLAYER;
//
//                int temp = maxSearch(mainBoard);
//                std::cout << i << "|" <<j<<"||" << score << "\n";
//                fflush(stdout);
//                if (temp < score) {
//                    score = temp;
//                    move.x = i;
//                    move.y = j;
//                }
//            mainBoard->board[i][j] = 0;
//            }
//        }
//    }
//
//    return move;
//}

//int ArtificialIntelligence::maxSearch(GomokuMainBoard * mainBoard) {
//    int victory = this->checkVictory(mainBoard->board, AI_PLAYER);
//
//    if (victory == HUMAN_PLAYER)
//        return {100};
//    else if (victory == AI_PLAYER)
//        return {-100};
//    else if (victory == 0)
//        return {0};
//
//    int score = -1000000;
//    for (unsigned int i = 0; i < GOMOKU_BOARD_SIZE; i++)
//    {
//        for (unsigned int j = 0; j < GOMOKU_BOARD_SIZE; j++)
//        {
//            if (mainBoard->board[i][j] == 0)
//            {
//                mainBoard->board[i][j] = HUMAN_PLAYER;
//                score = std::max(score, minSearch(mainBoard));
//                mainBoard->board[i][j] = 0;
//            }
//        }
//    }
//
//    return score;
//}

int ArtificialIntelligence::maxSearch(GomokuMainBoard * mainBoard, int depth) {
    int victory = this->checkVictory(mainBoard->board, AI_PLAYER);

    if (victory == HUMAN_PLAYER)
        return {100};
    else if (victory == AI_PLAYER)
        return {-100};
    else if (victory == 0 or depth > 1)
        return {0};

    int score = -1000000;
    for(auto & element: mainBoard->availablespots) {
        int x = element->getX();
        int y = element->getY();

        mainBoard->putStoneOnBoard(x, y, HUMAN_PLAYER);
        score = std::max(score, minSearch(mainBoard, ++depth));
        mainBoard->clearStoneOnBoard(x,y);
        //mainBoard->board[x][y] = 0;
        }

    return score;
}

//int ArtificialIntelligence::minSearch(GomokuMainBoard * mainBoard) {
//    int victory = this->checkVictory(mainBoard->board, HUMAN_PLAYER);
//
//    if (victory == HUMAN_PLAYER)
//        return {100};
//    else if (victory == AI_PLAYER)
//        return {-100};
//    else if (victory == 0)
//        return {0};
//
//    int score = 1000000;
//    for (unsigned int i = 0; i < GOMOKU_BOARD_SIZE; i++)
//    {
//        for (unsigned int j = 0; j < GOMOKU_BOARD_SIZE; j++)
//        {
//            if (mainBoard->board[i][j] == 0)
//            {
//                mainBoard->board[i][j] = AI_PLAYER;
//                score = std::min(score, maxSearch(mainBoard));
//                mainBoard->board[i][j] = 0;
//            }
//        }
//    }
//
//    return score;
//}

int ArtificialIntelligence::minSearch(GomokuMainBoard * mainBoard, int depth) {
    int victory = this->checkVictory(mainBoard->board, AI_PLAYER);

    if (victory == HUMAN_PLAYER)
        return {100};
    else if (victory == AI_PLAYER)
        return {-100};
    else if (victory == 0 or depth > 1)
        return {0};

    int score = 1000000;
    for(auto & element: mainBoard->availablespots) {
        if (element) {
            int x = element->getX();
            int y = element->getY();

            mainBoard->putStoneOnBoard(x, y, AI_PLAYER);
            score = std::min(score, maxSearch(mainBoard, ++depth));
            mainBoard->clearStoneOnBoard(x, y);
        }
    }

    return score;
}