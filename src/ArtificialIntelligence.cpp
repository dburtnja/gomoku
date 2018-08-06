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
    AiMove move{};

    move = minmaxSearch(mainBoard);
    mainBoard->putStoneOnBoard(move.x, move.y, player);
}

int ArtificialIntelligence::checkVictory(int (& board)[GOMOKU_BOARD_SIZE][GOMOKU_BOARD_SIZE], int player) {
    int victory = -1;

    for(int i = 0; i < GOMOKU_BOARD_SIZE; i++){
        for (int j = 0; j < GOMOKU_BOARD_SIZE; j++)
        {
            if (board[i][j] == board[i][j + 1] && board[i][j + 1] == board[i][j + 2] && board[i][j] != 0 and j+2 < GOMOKU_BOARD_SIZE)
            {
                victory = board[i][j];
                return victory;
            }

            if (board[i][j] == board[i+1][j] && board[i+1][j] == board[i+2][j] && board[i][j] != 0 and i+2 < GOMOKU_BOARD_SIZE)
            {
                victory = board[i][j];
                return victory;
            }
            if (board[i][j] == board[i+1][j+1] && board[i+2][j+2] == board[i][j] && board[i][j] != 0 and i+2 <GOMOKU_BOARD_SIZE and j+2 <GOMOKU_BOARD_SIZE  )
            {
                victory = board[i][j];
                return victory;
            }
            if (board[i][j] == board[i-1][j+1] && board[i-1][j+1] == board[i-2][j+2] && board[i][j] != 0 and i - 2 >= 0 and j + 2 < GOMOKU_BOARD_SIZE)
            {
                victory = board[i][j];
                return victory;
            }
            else victory = 0;
        }
    }

    if (victory == 0)
        for (int i = 0; i < GOMOKU_BOARD_SIZE; ++i) {
            for (int j = 0; j <GOMOKU_BOARD_SIZE ; ++j) {
                if (board[i][j] == 0)
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
    std::vector<AvailableSpot *> tmp_vector;

    tmp_vector = mainBoard->availablespots;

        for(auto & element: tmp_vector) {
            int x = element->getX();
            int y = element->getY();


            //mainBoard->board[x][y] = AI_PLAYER;
            mainBoard->putStoneOnBoard(x, y, AI_PLAYER);
            int temp = maxSearch(mainBoard, 0);

            std::cout << x << "|" <<y<<"||" << temp << "\n";
            fflush(stdout);
            if (temp < score) {
                score = temp;
                move.x = x;
                move.y = y;
            }
            mainBoard->availablespots=tmp_vector;
            mainBoard->board[x][y] = 0;
            //mainBoard->availablespots.push_back(new AvailableSpot(x,y));

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
//                int temp = maxSearch(mainBoard,0);
//                std::cout << i << "|" <<j<<"||" << temp << "\n";
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

//int ArtificialIntelligence::maxSearch(GomokuMainBoard * mainBoard, int depth) {
//    int victory = this->checkVictory(mainBoard->board, AI_PLAYER);
//
//    if (victory == HUMAN_PLAYER)
//        return {100};
//    else if (victory == AI_PLAYER)
//        return {-100};
//    else if (victory == 0 or depth > REC_DEPT)
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
//                score = std::max(score, minSearch(mainBoard, depth + 1));
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
    else if (victory == 0  or depth > REC_DEPT)
        return {0};

    int score = -1000000;

    std::vector<AvailableSpot *> tmp_vector;

    tmp_vector = mainBoard->availablespots;
    for(auto & element: tmp_vector) {
        int x = element->getX();
        int y = element->getY();

        mainBoard->putStoneOnBoard(x, y, HUMAN_PLAYER);
        //mainBoard->board[x][y] = HUMAN_PLAYER;

        score = std::max(score, minSearch(mainBoard, depth + 1));
        mainBoard->clearStoneOnBoard(x,y);
        mainBoard->availablespots.push_back(new AvailableSpot(x,y));
    }

    return score;
}

//int ArtificialIntelligence::minSearch(GomokuMainBoard * mainBoard, int depth) {
//    int victory = this->checkVictory(mainBoard->board, HUMAN_PLAYER);
//
//    if (victory == HUMAN_PLAYER)
//        return {100};
//    else if (victory == AI_PLAYER)
//        return {-100};
//    else if (victory == 0  or depth > REC_DEPT)
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
//                score = std::min(score, maxSearch(mainBoard, depth + 1));
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
    else if (victory == 0  or depth > REC_DEPT)
        return {0};

    int score = 1000000;

    std::vector<AvailableSpot *> tmp_vector;

    tmp_vector = mainBoard->availablespots;
    for(auto element: tmp_vector) {
        int x = element->getX();
        int y = element->getY();

        mainBoard->putStoneOnBoard(x, y, AI_PLAYER);
        //0mainBoard->board[x][y] = AI_PLAYER;

        score = std::min(score, maxSearch(mainBoard, depth + 1));
        mainBoard->clearStoneOnBoard(x, y);
        mainBoard->availablespots.push_back(new AvailableSpot(x,y));
    }

    return score;
}