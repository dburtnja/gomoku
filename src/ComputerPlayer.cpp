//
// Created by mirexcool on 29.03.2019.
//

#include "../headers/ComputerPlayer.hpp"

ComputerPlayer::ComputerPlayer(int playerNumber) : APlayer(playerNumber, AI_PLAYER) {
}

Move ComputerPlayer::makeMove(GomokuMainBoard &bord, APlayer *player_1, APlayer *player_2) {
    ArtificialIntelligence * AI = new ArtificialIntelligence;

    return AI->runAI(bord, player_1, player_2);
}
