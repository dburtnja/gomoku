//
// Created by mirexcool on 29.03.2019.
//

#include "../headers/ComputerPlayer.hpp"
#include "../headers/View.hpp"

ComputerPlayer::ComputerPlayer(int playerNumber, int playerSymbol) : APlayer(playerNumber, playerSymbol) {
}

Move ComputerPlayer::makeMove(GomokuMainBoard &bord, APlayer *otherPlayer) {
    ArtificialIntelligence * AI = new ArtificialIntelligence;

    return AI->runAI(bord, this, otherPlayer);
}
