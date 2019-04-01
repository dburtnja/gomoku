//
// Created by mirexcool on 29.03.2019.
//

#include "../headers/ComputerPlayer.hpp"

ComputerPlayer::ComputerPlayer(int playerNumber, int playerSymbol ) :
            APlayer(playerNumber, playerSymbol){}



ComputerPlayer::ComputerPlayer() {}

ComputerPlayer::~ComputerPlayer() {}

//AIPlayer::AIPlayer(AIPlayer & toCopy){}

//AIPlayer& AIPlayer::operator=(AIPlayer const &rhs) {}

Move ComputerPlayer::makeMove(GomokuMainBoard &bord, View *, APlayer *player_1, APlayer *player_2) {
    ArtificialIntelligence * AI = new ArtificialIntelligence;


    return AI->runAI(bord, player_1, player_2);
}
