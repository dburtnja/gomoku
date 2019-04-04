//
// Created by mirexcool on 29.03.2019.
//

#include "../headers/ComputerPlayer.hpp"
#include "../headers/View.hpp"

ComputerPlayer::ComputerPlayer(int playerNumber, int playerSymbol) : APlayer(playerNumber, playerSymbol) {
}

Move ComputerPlayer::_makeMove(GomokuMainBoard &board, APlayer *otherPlayer) {
    Move                    move{};
    ArtificialIntelligence  *artificialIntelligence;

    artificialIntelligence = new ArtificialIntelligence;
    move = artificialIntelligence->runAI(board, this, otherPlayer);

    delete artificialIntelligence;
    return move;
}

//Move ComputerPlayer::makeMove(GomokuMainBoard &board, APlayer *otherPlayer) {
//    Move                    move;
//    ArtificialIntelligence  *artificialIntelligence;
//
//    artificialIntelligence = new ArtificialIntelligence;
//    move = artificialIntelligence->runAI(board, this, otherPlayer);
//    board.putStoneOnBoard(move.coordinatesList[0]->getX(), move.coordinatesList[0]->getY(), this->getPlayerSymbol(), BOARD_LINE_SIZE * BOARD_LINE_SIZE); //todo ask about depth in put stone on board;
//    board.check_for_capture(move.coordinatesList[0]->getX(), move.coordinatesList[0]->getY(), this, otherPlayer, true, move.coordinatesList);
//    delete artificialIntelligence;
//    return move;
//}
