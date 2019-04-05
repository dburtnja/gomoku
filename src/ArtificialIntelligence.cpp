
#include "../headers/ArtificialIntelligence.hpp"

#include <algorithm>

ArtificialIntelligence::ArtificialIntelligence()
{

}

ArtificialIntelligence::~ArtificialIntelligence()
{

}

ArtificialIntelligence::ArtificialIntelligence(const ArtificialIntelligence &toCopy)
{
    * this = toCopy;
}

ArtificialIntelligence& ArtificialIntelligence::operator=(const ArtificialIntelligence &rhs)
{
    this->hashMap = rhs.hashMap;
    return  (* this);
}

bool mySortPlayer1(const AvailableSpot *a, const AvailableSpot *b )
{
    return abs(a->p1_score) > abs(b->p1_score);
}

bool mySortPlayer2(const AvailableSpot *a, const AvailableSpot *b )
{
    return abs(a->p2_score) > abs(b->p2_score);
}

Move ArtificialIntelligence::runAI(GomokuMainBoard & mainBoard, APlayer * player_1, APlayer * player_2)
{
    Move move{};
    clock_t start = clock();
    srand(time(NULL));

    if (player_1->getPlayerSymbol() == FIRST_PLAYER_ON_MAP)
        std::sort(mainBoard.availablespots.begin(), mainBoard.availablespots.end(), mySortPlayer1);
    else
        std::sort(mainBoard.availablespots.begin(), mainBoard.availablespots.end(), mySortPlayer2);

    move = minmaxSearch(mainBoard, player_1, player_2);

    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    //printf("The time: %f seconds\n", player_1->getTimeLastMove());
    std::cout << move.coordinatesList[0]->getX() << " " << move.coordinatesList[0]->getY();

    return move;
}



Move ArtificialIntelligence::minmaxSearch(GomokuMainBoard & mainBoard, APlayer * player_1, APlayer * player_2)
{
    Move move{};

    clock_t start = clock();
    double seconds = 0;

    int value = INT_MIN;
    int x = -1;
    int y = -1;

    std::vector<AvailableSpot *> tmp_vector;

    tmp_vector = mainBoard.availablespots;

    for(auto & element: tmp_vector) {
        int x_cor = element->getX();
        int y_cor = element->getY();

        int tmp = minimaxAlphaBeta (mainBoard, REC_DEPT - 1, true, INT_MIN, INT_MAX, x_cor, y_cor, player_1, player_2);

        mainBoard.setValue(x_cor, y_cor, player_1->getPlayerSymbol());
        int capture = mainBoard.check_for_capture(x_cor, y_cor, player_1, player_2, false, move.coordinatesList);
        mainBoard.setValue(x_cor, y_cor, EMPTY_CELL_ON_MAP);

        //if (capture !=0)
            //printf("Computer capture = %d\n", capture);

        if (tmp > 0)
            tmp += capture;
        mainBoard.setValue(x_cor, y_cor, player_2->getPlayerSymbol());
        capture = mainBoard.check_for_capture(x_cor, y_cor, player_2, player_1, false, move.coordinatesList);
        mainBoard.setValue(x_cor, y_cor, EMPTY_CELL_ON_MAP);

        //if (capture !=0)
            //printf("Oponent capture = %d\n", capture);
        if (tmp > 0)
            tmp += capture * 2;
        //printf("x=%d, y=%d -> score = %d\n", x_cor,y_cor,tmp);


        if (tmp > value )
        {
            value = tmp;
            x = x_cor;
            y = y_cor;
        }

        if (player_1->getPlayerSymbol() == FIRST_PLAYER_ON_MAP)
            element->p1_score = tmp;
        else
            element->p2_score = tmp;

        clock_t end = clock();
        seconds = (double)(end - start) / CLOCKS_PER_SEC;
        if (tmp == INT_MAX || seconds > 0.4999)
            break ;
    }
    if (x == -1 && y == -1 )
    {
        x = GOMOKU_BOARD_SIZE /2;
        y = GOMOKU_BOARD_SIZE /2;
    }
    move.x = x;
    move.y = y;

    mainBoard.availablespots.erase(mainBoard.availablespots.begin(), mainBoard.availablespots.end());
    mainBoard.availablespots = tmp_vector;

    move.coordinatesList.push_back(new Coordinates(x, y, player_1->getPlayerSymbol()));
    player_1->setTimeLastMove(seconds);
    return move;
}

void ArtificialIntelligence::deleteAvaibleSpotsVector(std::vector<AvailableSpot *> old, std::vector<AvailableSpot *> availablespots ) {

    //for (auto & element: availablespots)

}

int ArtificialIntelligence::minimaxAlphaBeta(GomokuMainBoard & mainBoard, int depth, bool isMax, int alpha, int beta,
        int x, int y, APlayer * player_1, APlayer * player_2)

        {
    std::vector<AvailableSpot*> tmp_vector_old;
    int c = isMax ? player_1->getPlayerSymbol()  : player_2->getPlayerSymbol();
    int value = 0;
    Move move{};


    tmp_vector_old = mainBoard.availablespots;
    mainBoard.putStoneOnBoard(x, y, c, depth);

    if (mainBoard.win(x,y))
    {
        mainBoard.setValue(x, y, EMPTY_CELL_ON_MAP);
        mainBoard.availablespots.erase(mainBoard.availablespots.begin(), mainBoard.availablespots.end());

        mainBoard.availablespots = tmp_vector_old;

        if (isMax)
            return INT_MAX - REC_DEPT + depth;
        else
            return INT_MIN + REC_DEPT - depth;
    }

    if (depth == 0)
    {

        int capture_value = 0;

        if (isMax)
            capture_value = mainBoard.check_for_capture(x, y, player_1, player_2, false, move.coordinatesList);
        else
            capture_value = mainBoard.check_for_capture(x, y, player_2, player_1, false, move.coordinatesList) * 2;

        value = evaluation(mainBoard, isMax, player_1->getPlayerSymbol());

        if (value > 0)
            value+=capture_value;
        //mainBoard.clearStoneOnBoard(x,y);
        mainBoard.setValue(x, y, EMPTY_CELL_ON_MAP);

        mainBoard.availablespots.erase(mainBoard.availablespots.begin(), mainBoard.availablespots.end());

        mainBoard.availablespots = tmp_vector_old;
        return value;
    }

    if (isMax)
    {
        std::vector<AvailableSpot *> tmp_vector;

        tmp_vector = mainBoard.availablespots;
        int m = INT_MAX;

        /*if (player_1->getPlayerSymbol() == FIRST_PLAYER_ON_MAP)
            std::sort(mainBoard.availablespots.begin(), mainBoard.availablespots.end(), mySortPlayer1);
        else
            std::sort(mainBoard.availablespots.begin(), mainBoard.availablespots.end(), mySortPlayer2);*/


        for (auto & element: tmp_vector)
        {
            int x_cor = element->getX();
            int y_cor = element->getY();

            int temp = minimaxAlphaBeta(mainBoard, depth - 1, false, alpha, beta, x_cor, y_cor, player_1, player_2);

            if (m > temp)
                m = temp;
            if (beta > m)
                beta = m;

            if (alpha >= beta)
            {
                break ;
            }
        }
        tmp_vector.erase(tmp_vector.begin(), tmp_vector.end());

        //mainBoard.availablespots = tmp_vector;

        mainBoard.setValue(x,y, EMPTY_CELL_ON_MAP);
        return m;
    }
    else
    {
        std::vector<AvailableSpot *> tmp_vector;

        tmp_vector = mainBoard.availablespots;
        int M = INT_MIN;

        /*if (player_1->getPlayerSymbol() == FIRST_PLAYER_ON_MAP)
            std::sort(mainBoard.availablespots.begin(), mainBoard.availablespots.end(), mySortPlayer1);
        else
            std::sort(mainBoard.availablespots.begin(), mainBoard.availablespots.end(), mySortPlayer2);*/
        for (auto & element: tmp_vector)
        {
            int x_cor = element->getX();
            int y_cor = element->getY();

            int temp = minimaxAlphaBeta(mainBoard, depth - 1, true, alpha, beta, x_cor, y_cor, player_1, player_2);

            if (M < temp){
                M = temp;
            }
            if (alpha < M){
                alpha = M;
            }

            if (alpha >= beta)
            {
                break ;
            }
        }
        tmp_vector.erase(tmp_vector.begin(), tmp_vector.end());

        //mainBoard.availablespots = tmp_vector;

        mainBoard.setValue(x,y, EMPTY_CELL_ON_MAP);

        return M;
    }

}

int ArtificialIntelligence::evaluation(GomokuMainBoard &mainBoard, int isMax, int player_1)
{
    int M = 5;
    int N = GOMOKU_BOARD_SIZE;
    int sum = 0;
    std::vector<int> firstPlayerrPattern(M + 1, 0);
    std::vector<int> secondPlayerPattern(M + 1, 0);

    for (int  i = 0 ; i < N; i++){
        for (int j = 0; j < N ; j++){
            if (mainBoard.getValue(i,j) != 0){
                int c = mainBoard.getValue(i,j);
                bool needMax = c == player_1;

                int sameSymbol = 1; // count same symbols in columns
                int k = 1;
                while (i - k >= 0 && mainBoard.getValue(i - k, j)  == c){
                    sameSymbol++;
                    k++;
                }


                //consider value at i - k later to see if it's blocked or not
                int l = 1;
                while (i + l <= N-1 && mainBoard.getValue(i+l, j) == c){
                    sameSymbol++;
                    l++;
                }

                if (sameSymbol >= M){
                    if (needMax) firstPlayerrPattern[M]++;
                    else secondPlayerPattern[M]++;
                }else if (sameSymbol == M - 1 && (mainBoard.checkEmpty(i-k,j) || mainBoard.checkEmpty(i+l,j)) ){
                    if (needMax) firstPlayerrPattern[M-1]++;
                    else secondPlayerPattern[M-1]++;
                }
                else if (sameSymbol == M - 2 && (mainBoard.checkEmpty(i-k,j) && mainBoard.checkEmpty(i+l,j)) )
                {
                    if (needMax)
                        firstPlayerrPattern[M-2] ++;
                    else
                        secondPlayerPattern[M-2] ++;
                }
                else if (sameSymbol == M - 2 && (mainBoard.checkEmpty(i-k,j) || mainBoard.checkEmpty(i+l,j)) ){
                    if (needMax) firstPlayerrPattern[M-3]++;
                    else secondPlayerPattern[M-3]++;
                }else if (sameSymbol == M - 3 && mainBoard.checkEmpty(i-k,j) && mainBoard.checkEmpty(i+l,j) ){
                    if (needMax) firstPlayerrPattern[M-4]++;
                    else secondPlayerPattern[M-4]++;
                }

                //-------------------------------------------------------------------------------
                sameSymbol = 1; // count same symbols in rows
                k = 1;
                while (j - k >= 0 && mainBoard.getValue(i, j-k)  == c){
                    sameSymbol++;
                    k++;
                }


                //consider value at i - k later to see if it's blocked or not
                l = 1;
                while (j + l <= N-1 && mainBoard.getValue(i, j+l) == c){
                    sameSymbol++;
                    l++;
                }

                if (sameSymbol >= M){
                    if (needMax) firstPlayerrPattern[M]++;
                    else secondPlayerPattern[M]++;
                }
                else if (sameSymbol == M - 1 && (mainBoard.checkEmpty(i,j-k) || mainBoard.checkEmpty(i,j+l)) )
                {
                    if (needMax) firstPlayerrPattern[M-1]++;
                    else secondPlayerPattern[M-1]++;
                }
                else if (sameSymbol == M - 2 && (mainBoard.checkEmpty(i,j-k) && mainBoard.checkEmpty(i,j+l)) )
                {
                    if (needMax)
                        firstPlayerrPattern[M-2] ++;
                    else
                        secondPlayerPattern[M-2] ++;
                }
                else if (sameSymbol == M - 2 && (mainBoard.checkEmpty(i,j-k) || mainBoard.checkEmpty(i,j+l)) )
                {
                    if (needMax) firstPlayerrPattern[M-3]++;
                    else secondPlayerPattern[M-3]++;
                }
                else if (sameSymbol == M - 3 && mainBoard.checkEmpty(i,j-k) && mainBoard.checkEmpty(i,j+l) )
                {
                    if (needMax) firstPlayerrPattern[M-4]++;
                    else secondPlayerPattern[M-4]++;
                }

                //--------------------------------------------------------------

                sameSymbol = 1;// count same symbols in main diagnol
                k = 1;
                while (i - k >= 0 && j - k >= 0 && mainBoard.getValue(i - k, j- k)  == c){
                    sameSymbol++;
                    k++;
                }


                //consider value at i - k later to see if it's blocked or not
                l = 1;
                while (i + l < N && j + l < N && mainBoard.getValue(i + l, j + l ) == c){
                    sameSymbol++;
                    l++;
                }

                if (sameSymbol >= M){
                    if (needMax) firstPlayerrPattern[M]++;
                    else secondPlayerPattern[M]++;
                }else if (sameSymbol == M - 1 && (mainBoard.checkEmpty(i-k,j-k) || mainBoard.checkEmpty(i+l,j+l))){
                    if (needMax) firstPlayerrPattern[M-1]++;
                    else secondPlayerPattern[M-1]++;
                }else if (sameSymbol == M - 2 && (mainBoard.checkEmpty(i - k,j - k) && mainBoard.checkEmpty(i + l,j + l)))
                {
                    if (needMax)
                        firstPlayerrPattern[M - 2] ++;
                    else
                        secondPlayerPattern[M - 2] ++;
                }
                else if (sameSymbol == M - 2 && (mainBoard.checkEmpty(i-k,j-k) || mainBoard.checkEmpty(i+l,j+l))){
                    if (needMax) firstPlayerrPattern[M-3]++;
                    else secondPlayerPattern[M-3]++;
                }else if (sameSymbol == M - 3 && mainBoard.checkEmpty(i-k,j-k) && mainBoard.checkEmpty(i+l,j+l)){
                    if (needMax) firstPlayerrPattern[M-4]++;
                    else secondPlayerPattern[M-4]++;
                }

                //-----------------------------------------------------------------------


                sameSymbol = 1;// count same symbols in reverse diagnols
                k = 1;
                while (i - k >= 0 && j + k < N && mainBoard.getValue(i - k, j + k)  == c){
                    sameSymbol++;
                    k++;
                }


                //consider value at i - k later to see if it's blocked or not
                l = 1;
                while (i + l <= N-1 && j - l >= 0 && mainBoard.getValue(i+l, j-l ) == c){
                    sameSymbol++;
                    l++;
                }

                if (sameSymbol >= M){
                    if (needMax) firstPlayerrPattern[M]++;
                    else secondPlayerPattern[M]++;
                }else if (sameSymbol == M - 1 && (mainBoard.checkEmpty(i-k,j+k) || mainBoard.checkEmpty(i+l,j-l))){
                    if (needMax) firstPlayerrPattern[M-1]++;
                    else secondPlayerPattern[M-1]++;
                }
                else if (sameSymbol == M - 2 && (mainBoard.checkEmpty(i-k,j+k) && mainBoard.checkEmpty(i+l,j-l)))
                {
                    if (needMax)
                        firstPlayerrPattern[M-2]++;
                    else
                        secondPlayerPattern[M-2]++;
                }
                else if (sameSymbol == M - 2 && (mainBoard.checkEmpty(i-k,j+k) || mainBoard.checkEmpty(i+l,j-l))){
                    if (needMax) firstPlayerrPattern[M-3]++;
                    else secondPlayerPattern[M-3]++;
                }else if (sameSymbol == M - 3 && mainBoard.checkEmpty(i-k,j+k) && mainBoard.checkEmpty(i+l,j-l)){
                    if (needMax) firstPlayerrPattern[M-4]++;
                    else secondPlayerPattern[M-4]++;
                }

            }
        }
    }
    if (firstPlayerrPattern[M] > 0)
        return INT_MAX - 0;
    if (secondPlayerPattern[M] > 0)
       return INT_MIN + 0;

    int x = 1;
    sum += firstPlayerrPattern[1] * rand() % 5;
    sum -= secondPlayerPattern[1] * 5 * rand() % 5  ;
    for (int i = 2 ; i < M ; i++){
        x *= 100;
        sum += firstPlayerrPattern[i] * x;
        sum -= secondPlayerPattern[i] * x * 10;
    }
    return sum;
}


void ArtificialIntelligence::insertToHashMap(GomokuMainBoard &board, int value) {
    std::string s = board.toString();
    hashMap[s] = value;
    return ;
}

bool ArtificialIntelligence::checkVisitedBoard(GomokuMainBoard &board) {
    std::string s = board.toString();
    if (hashMap.find(s) != hashMap.end())
        return true;
    return false;
}

int ArtificialIntelligence::getEvaluation(GomokuMainBoard &board) {
    return hashMap[board.toString()];
}
