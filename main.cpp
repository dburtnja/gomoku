#include "headers/MainHeader.hpp"

int main() {
    AiMove move{};
    GomokuMainBoard * mainBoard = new GomokuMainBoard;

    ArtificialIntelligence * AI = new ArtificialIntelligence;


    int i = 0;
    while(1) {
        if (i % 2 + 1  == AI_PLAYER)
        {
            move = AI->runAI(*mainBoard, AI_PLAYER );
            if (mainBoard->win(move.x, move.y))
            {
                std::cout << " AI_PLAYER WON !!! \n";
                break;
            }
            mainBoard->printBoard();
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
        i++;
        mainBoard->count++;
    }
    mainBoard->printBoard();
    return 0;
}
