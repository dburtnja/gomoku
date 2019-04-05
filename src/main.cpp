
#include "../headers/GomokuGame.hpp"

int main()
{
    GomokuGame  *gomokuGame;

    try {
        gomokuGame = new GomokuGame;
    } catch (std::string &error) {
        std::cout << error << std::endl;
        return -1;
    }

    gomokuGame->start();
    delete gomokuGame;
    return 0;
}