#include "headers/MainHeader.hpp"

int main() {
    AiMove move{};
    GomokuMainBoard * mainBoard = new GomokuMainBoard;

    ArtificialIntelligence * AI = new ArtificialIntelligence;

    //mainBoard->availablespots.push_back(new AvailableSpot(GOMOKU_BOARD_SIZE / 2, GOMOKU_BOARD_SIZE / 2));

    int i = 0;
    while(1) {
        if (i % 2   == AI_PLAYER)
        {
            move = AI->runAI(*mainBoard, AI_PLAYER );
            if (mainBoard->win(move.x, move.y))
            {
                std::cout << " AI_PLAYER WON !!! \n";
                break;
            }
            mainBoard->printBoard();
//            int x;
//            int y;
//            std::cout <<"Enter x: ";
//            std::cin >> x;
//            std::cout <<"Enter y: ";
//            std::cin >> y;
//            mainBoard->putStoneOnBoard(x,y,AI_PLAYER, 100);

//            mainBoard->printBoard();
//            if (mainBoard->win(x, y))
//            {
//                std::cout << " HUMAN_PLAYER WON !!! \n";
//                break;
//            }
        }
        else
        {
            int x;
            int y;
            std::cout <<"Enter x: ";
            std::cin >> x;
            std::cout <<"Enter y: ";
            std::cin >> y;
            mainBoard->putStoneOnBoard(x,y,HUMAN_PLAYER, 100);

            mainBoard->printBoard();
            if (mainBoard->win(x, y))
            {
                std::cout << " HUMAN_PLAYER WON !!! \n";
                break;
            }
//            move = AI->runAI(*mainBoard, HUMAN_PLAYER );
//            if (mainBoard->win(move.x, move.y))
//            {
//                std::cout << " HUMEN_PYAYER WON !!! \n";
//                break;
//            }
//            mainBoard->printBoard();
        }
//        int score = AI->evaluation(*mainBoard, AI_PLAYER);
//        printf("SCORE 1 = %d\n", score);
//        score = AI->evaluation(*mainBoard, HUMAN_PLAYER);
//        printf("SCORE 2 = %d\n", score);
        i++;
        mainBoard->count++;
    }
    mainBoard->printBoard();
    return 0;
}
