
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
    return a->p1_score > b->p1_score;
}

bool mySortPlayer2(const AvailableSpot *a, const AvailableSpot *b )
{
    return a->p2_score > b->p2_score;
}

Move ArtificialIntelligence::runAI(GomokuMainBoard & mainBoard, APlayer * player_1, APlayer * player_2)
{
    Move move{};
    clock_t start = clock();
    srand(time(NULL));

    if (player_1->getplayerSymbol() == FIRST_PLAYER)
        std::sort(mainBoard.availablespots.begin(), mainBoard.availablespots.end(), mySortPlayer1);
    else
        std::sort(mainBoard.availablespots.begin(), mainBoard.availablespots.end(), mySortPlayer2);

    move = minmaxSearch(mainBoard, player_1, player_2);

    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("The time: %f seconds\n", player_1->getTimeLastMove());


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

        int tmp = minimaxAlphaBeta (mainBoard, REC_DEPT - 1, true, INT_MIN, INT_MAX, x_cor,y_cor, player_1, player_2);

        mainBoard.setValue(x_cor, y_cor, player_1->getplayerSymbol());
        int capture = mainBoard.check_for_capture(x_cor, y_cor, player_1, player_2, false, move.coordinatesList);
        mainBoard.setValue(x_cor, y_cor, EMPTY_CELL_ON_MAP);

        //if (capture !=0)
       //     printf("Computer capture = %d\n", capture);

        if (tmp > 0)
            tmp += capture;
        mainBoard.setValue(x_cor, y_cor, player_2->getplayerSymbol());
        capture = mainBoard.check_for_capture(x_cor, y_cor, player_2, player_1, false, move.coordinatesList);
        mainBoard.setValue(x_cor, y_cor, EMPTY_CELL_ON_MAP);

        //if (capture !=0)
           // printf("Oponent capture = %d\n", capture);
        if (tmp > 0)
            tmp += capture * 2;
        printf("x=%d, y=%d -> score = %d\n", x_cor,y_cor,tmp);


        if (tmp > value )
        {
            value = tmp;
            x = x_cor;
            y = y_cor;
        }

        if (player_1->getplayerSymbol() == FIRST_PLAYER)
            element->p1_score = tmp;
        else
            element->p2_score = tmp;

        clock_t end = clock();
        seconds = (double)(end - start) / CLOCKS_PER_SEC;
        if (tmp == INT_MAX)// || seconds > 0.4999)
            break ;
        //printf("TIME = %f\n", seconds);
    }
    if (x == -1 && y == -1 )
    {
        x = GOMOKU_BOARD_SIZE /2;
        y = GOMOKU_BOARD_SIZE /2;
    }
    move.x = x;
    move.y = y;


    mainBoard.availablespots = tmp_vector;
    printf("x=%d, y=%d -> score = %d\n", x,y,value);
    //printf("time = %d\n", seconds);

    move.coordinatesList.push_back(new Coordinates(x, y, player_1->getplayerSymbol()));
    player_1->setTimeLastMove(seconds);
    return move;
}

int ArtificialIntelligence::minimaxAlphaBeta(GomokuMainBoard & mainBoard, int depth, bool isMax, int alpha, int beta, int x, int y, APlayer * player_1, APlayer * player_2)
{
    std::vector<AvailableSpot *> tmp_vector_old;
    int c = isMax ?  player_1->getplayerSymbol()  : player_2->getplayerSymbol();
    int value = 0;
    Move move{};


    tmp_vector_old = mainBoard.availablespots;
    mainBoard.putStoneOnBoard(x, y, c, depth);


    if (mainBoard.win(x,y))
    {
        mainBoard.availablespots = tmp_vector_old;

        mainBoard.setValue(x,y, EMPTY_CELL_ON_MAP);

        if (isMax)
        {
            return INT_MAX - REC_DEPT + depth;
        }
        else
            {
                return INT_MIN + REC_DEPT - depth;
            }
    }
//    else
//        if (mainBoard.draw()){
//        return 0;
//    }
    if (depth == 0)
    {

        int capture_value = 0;

        if (isMax)
            capture_value = mainBoard.check_for_capture(x, y, player_1, player_2, false, move.coordinatesList);
        else
            capture_value = mainBoard.check_for_capture(x, y, player_2, player_1, false, move.coordinatesList) * 2;

        value = evaluation(mainBoard, isMax, player_1->getplayerSymbol(), player_2->getplayerSymbol());

        if (value > 0)
            value+=capture_value;

        mainBoard.setValue(x,y, EMPTY_CELL);

        mainBoard.availablespots = tmp_vector_old;
        return value;
        /*if (checkVisitedBoard(mainBoard))
        {
            value = getEvaluation(mainBoard);
        }
        else
        {
            value = evaluation(mainBoard, isMax);
            //value = getScoreByPatterns(mainBoard,0,0,x,y);
            insertToHashMap(mainBoard, value);
        }
        return value;*/
    }



    if (isMax)
    {
        std::vector<AvailableSpot *> tmp_vector;

        tmp_vector = mainBoard.availablespots;
        int m = INT_MAX;


        for (auto & element: tmp_vector)
        {
            int x_cor = element->getX();
            int y_cor = element->getY();

            std::vector<AvailableSpot *> tmp_vector1;
            tmp_vector1 = mainBoard.availablespots;

            int temp = minimaxAlphaBeta(mainBoard, depth - 1, false, alpha, beta, x_cor, y_cor, player_1, player_2);
            if (m > temp)
                m = temp;
            if (beta > m)
                beta = m;
            mainBoard.availablespots = tmp_vector1;

            if (alpha >= beta)
            {
                break ;
            }
        }
        mainBoard.availablespots = tmp_vector_old;

        mainBoard.setValue(x,y, EMPTY_CELL_ON_MAP);
        return m;
    }
    else
    {
        std::vector<AvailableSpot *> tmp_vector;

        tmp_vector = mainBoard.availablespots;
        int M = INT_MIN;

       /* if (player_1->getplayerSymbol() == FIRST_PLAYER)
            std::sort(tmp_vector.begin(), tmp_vector.end(), mySortPlayer1);
        else
            std::sort(tmp_vector.begin(), tmp_vector.end(), mySortPlayer2);*/
        for (auto & element: tmp_vector)
        {
            int x_cor = element->getX();
            int y_cor = element->getY();

            std::vector<AvailableSpot *> tmp_vector1;
            tmp_vector1 = mainBoard.availablespots;
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
        mainBoard.availablespots = tmp_vector_old;
        mainBoard.setValue(x,y, EMPTY_CELL_ON_MAP);

        return M;
    }
}

int ArtificialIntelligence::evaluation(GomokuMainBoard &mainBoard, int isMax, int player_1)
{
    int M = 5;
    int N = GOMOKU_BOARD_SIZE;
    int sum = 0;
    std::vector<int> computerPattern(M + 1, 0);
    std::vector<int> playerPattern(M + 1, 0);
    isMax = false;

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
                    if (needMax) computerPattern[M]++;
                    else playerPattern[M]++;
                }else if (sameSymbol == M - 1 && (mainBoard.checkEmpty(i-k,j) || mainBoard.checkEmpty(i+l,j)) ){
                    if (needMax) computerPattern[M-1]++;
                    else playerPattern[M-1]++;
                }
                else if (sameSymbol == M - 2 && (mainBoard.checkEmpty(i-k,j) && mainBoard.checkEmpty(i+l,j)) )
                {
                    if (needMax)
                        computerPattern[M-2] ++;
                    else
                        playerPattern[M-2] ++;
                }
                else if (sameSymbol == M - 2 && (mainBoard.checkEmpty(i-k,j) || mainBoard.checkEmpty(i+l,j)) ){
                    if (needMax) computerPattern[M-3]++;
                    else playerPattern[M-3]++;
                }else if (sameSymbol == M - 3 && mainBoard.checkEmpty(i-k,j) && mainBoard.checkEmpty(i+l,j) ){
                    if (needMax) computerPattern[M-4]++;
                    else playerPattern[M-4]++;
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
                    if (needMax) computerPattern[M]++;
                    else playerPattern[M]++;
                }
                else if (sameSymbol == M - 1 && (mainBoard.checkEmpty(i,j-k) || mainBoard.checkEmpty(i,j+l)) )
                {
                    if (needMax) computerPattern[M-1]++;
                    else playerPattern[M-1]++;
                }
                else if (sameSymbol == M - 2 && (mainBoard.checkEmpty(i,j-k) && mainBoard.checkEmpty(i,j+l)) )
                {
                    if (needMax)
                        computerPattern[M-2] ++;
                    else
                        playerPattern[M-2] ++;
                }
                else if (sameSymbol == M - 2 && (mainBoard.checkEmpty(i,j-k) || mainBoard.checkEmpty(i,j+l)) )
                {
                    if (needMax) computerPattern[M-3]++;
                    else playerPattern[M-3]++;
                }
                else if (sameSymbol == M - 3 && mainBoard.checkEmpty(i,j-k) && mainBoard.checkEmpty(i,j+l) )
                {
                    if (needMax) computerPattern[M-4]++;
                    else playerPattern[M-4]++;
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
                    if (needMax) computerPattern[M]++;
                    else playerPattern[M]++;
                }else if (sameSymbol == M - 1 && (mainBoard.checkEmpty(i-k,j-k) || mainBoard.checkEmpty(i+l,j+l))){
                    if (needMax) computerPattern[M-1]++;
                    else playerPattern[M-1]++;
                }else if (sameSymbol == M - 2 && (mainBoard.checkEmpty(i - k,j - k) && mainBoard.checkEmpty(i + l,j + l)))
                {
                    if (needMax)
                        computerPattern[M - 2] ++;
                    else
                        playerPattern[M - 2] ++;
                }
                else if (sameSymbol == M - 2 && (mainBoard.checkEmpty(i-k,j-k) || mainBoard.checkEmpty(i+l,j+l))){
                    if (needMax) computerPattern[M-3]++;
                    else playerPattern[M-3]++;
                }else if (sameSymbol == M - 3 && mainBoard.checkEmpty(i-k,j-k) && mainBoard.checkEmpty(i+l,j+l)){
                    if (needMax) computerPattern[M-4]++;
                    else playerPattern[M-4]++;
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
                    if (needMax) computerPattern[M]++;
                    else playerPattern[M]++;
                }else if (sameSymbol == M - 1 && (mainBoard.checkEmpty(i-k,j+k) || mainBoard.checkEmpty(i+l,j-l))){
                    if (needMax) computerPattern[M-1]++;
                    else playerPattern[M-1]++;
                }
                else if (sameSymbol == M - 2 && (mainBoard.checkEmpty(i-k,j+k) && mainBoard.checkEmpty(i+l,j-l)))
                {
                    if (needMax)
                        computerPattern[M-2]++;
                    else
                        playerPattern[M-2]++;
                }
                else if (sameSymbol == M - 2 && (mainBoard.checkEmpty(i-k,j+k) || mainBoard.checkEmpty(i+l,j-l))){
                    if (needMax) computerPattern[M-3]++;
                    else playerPattern[M-3]++;
                }else if (sameSymbol == M - 3 && mainBoard.checkEmpty(i-k,j+k) && mainBoard.checkEmpty(i+l,j-l)){
                    if (needMax) computerPattern[M-4]++;
                    else playerPattern[M-4]++;
                }

            }
        }
    }
    if (computerPattern[M] > 0)
        return INT_MAX - 0;
    if (playerPattern[M] > 0)
       return INT_MIN + 0;

    int x = 1;
    sum += computerPattern[1] * rand() % 5;
    sum -= playerPattern[1] * 5 * rand() % 5  ;
    for (int i = 2 ; i < M ; i++){
        x *= 100;
        sum += computerPattern[i] * x;
        sum -= playerPattern[i] * x * 10;
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
