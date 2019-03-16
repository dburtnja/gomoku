

#include "../headers/MainHeader.hpp"

#include <algorithm>    // std::max


ArtificialIntelligence::ArtificialIntelligence() {
    patternsHashMap = {
            {"11111", 99999},
            {"22222", -99999},
            {"011110", 7000},
            {"022220", -7500},
            {"01111", 4000},
            {"02222", -4500},
            {"010111", 2000},
            {"020222", -2500},
            {"011011", 2000},
            {"022022", -2500},
            {"011101", 2000},
            {"022202", -2500},
            {"111010", 2000},
            {"222020", -2500},
            {"110110", 2000},
            {"220220", -2500},
            {"101110", 2000},
            {"202220", -2500},
            {"0111", 1500},
            {"0222", -1550},
            {"1110", 1500},
            {"2220", -1550},
            {"01101", 800},
            {"02202", -850},
            {"01011", 800},
            {"0202", -850},
            {"11010", 800},
            {"22020", -850},
            {"10110", 800},
            {"20220", -850},
            {"0110", 200},
            {"0220", -250},
    };
}

ArtificialIntelligence::~ArtificialIntelligence() {}

ArtificialIntelligence::ArtificialIntelligence(const ArtificialIntelligence &toCopy) {
    * this = toCopy;

}
ArtificialIntelligence& ArtificialIntelligence::operator=(const ArtificialIntelligence &rhs) {
    return  (* this);
}

AiMove ArtificialIntelligence::runAI(GomokuMainBoard & mainBoard, int player) {

    AiMove move{};
    clock_t start = clock();

    move = minmaxSearch(mainBoard, player);

    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("The time: %f seconds\n", seconds);

    mainBoard.putStoneOnBoard(move.x, move.y, player, 100);
    return move;
}

AiMove ArtificialIntelligence::minmaxSearch(GomokuMainBoard & mainBoard, int player) {
    AiMove move{};

    int value = INT_MIN;
    int x = -1;
    int y = -1;
    //int new_board[GOMOKU_BOARD_SIZE][GOMOKU_BOARD_SIZE];

    for (int i = 0; i < GOMOKU_BOARD_SIZE ; ++i) {
        for (int j = 0; j < GOMOKU_BOARD_SIZE; ++j) {
            if ( mainBoard.getValue(i,j) == 0 && adjacentPlaced(mainBoard.board, i, j))
            {
                int tmp = minimaxAlphaBeta (mainBoard, REC_DEPT, true, INT_MIN, INT_MAX, i, j);
                printf("x=%d, y=%d -> score = %d\n", x,y,tmp);
                if (value < tmp) {
                    value = tmp;
                    x = i;
                    y = j;
                }
            }

        }
    }
    if (x == -1 && y == -1)
    {
        x = GOMOKU_BOARD_SIZE /2;
        y = GOMOKU_BOARD_SIZE /2;
    }
//    std::vector<AvailableSpot *> tmp_vector;
//
//    tmp_vector = mainBoard.availablespots;
//
//    for(auto & element: tmp_vector) {
//        int x_cor = element->getX();
//        int y_cor = element->getY();
//
//        //mainBoard.putStoneOnBoard(x_cor, y_cor, AI_PLAYER, 100);
//        int tmp = minimaxAlphaBeta (mainBoard, REC_DEPT-1, true, INT_MIN, INT_MAX, x_cor,y_cor);
//        // mainBoard.clearStoneOnBoard(x_cor,y_cor);
//        //printf("x=%d, y=%d -> score = %d\n", x_cor,y_cor,tmp);
//        if (tmp > value )
//        {
//            value = tmp;
//            x = x_cor;
//            y = y_cor;
//        }
//        if (tmp == INT_MAX)
//            break ;
//    }
//    if (x == -1 && y == -1)
//    {
//        x = GOMOKU_BOARD_SIZE /2;
//        y = GOMOKU_BOARD_SIZE /2;
//    }
    move.x = x;
    move.y = y;

    printf("%ld", mainBoard.recs);
    return move;
}

int ArtificialIntelligence::minimaxAlphaBeta(GomokuMainBoard & mainBoard, int depth, bool isMax, int alpha, int beta, int x, int y)
{
    int c = isMax ?  AI_PLAYER  : HUMAN_PLAYER;

    int value = 0;
    mainBoard.recs++;
    mainBoard.putStoneOnBoard(x, y, c, depth);


    //mainBoard.printBoard();
    if (mainBoard.win(x,y)){
        //value = evaluation(mainBoard, player);
        //return value;
        //mainBoard.setValue(x,y,0);
        if (isMax){
            mainBoard.setValue(x,y, 0);
            return INT_MAX;
        }else {
            mainBoard.setValue(x,y, 0);
            return INT_MIN;
        }
    }
//    else
//        if (mainBoard.draw()){
//        return 0;
//    }
    if (depth == 0)
    {
        mainBoard.setValue(x,y, 0);

        return evaluation(mainBoard, isMax);
        if (checkVisitedBoard(mainBoard))
        {
            value = getEvaluation(mainBoard);
        }
        else
        {
            value = evaluation(mainBoard, isMax);
            //value = getScoreByPatterns(mainBoard,0,0,x,y);
            insertToHashMap(mainBoard, value);
        }
        return value;
    }

    std::vector<int> firstCoord;
    std::vector<int> secondCoord;
    for (int i = 0; i < GOMOKU_BOARD_SIZE; i++){
        for (int j = 0; j < GOMOKU_BOARD_SIZE; j++){

            if (mainBoard.getValue(i,j) == 0 && adjacentPlaced(mainBoard.board, i, j) ){
                firstCoord.push_back(i);
                secondCoord.push_back(j);
            }
        }
    }
    int len = (int) firstCoord.size();


    if (isMax)
    {
        for (int i = 0; i < len; ++i) {
           // mainBoard.setValue(firstCoord[i],secondCoord[i],c);
            alpha = std::max(alpha, minimaxAlphaBeta(mainBoard, depth - 1, false, alpha, beta, firstCoord[i], secondCoord[i]));

            if (alpha >= beta)
            {
                break ;
            }
        }
        mainBoard.setValue(x,y,0);

        //mainBoard.setValue(x,y,0);
        return alpha;
    }
    else
    {
        for (int i = 0; i < len; ++i) {
            beta = std::min(beta, (minimaxAlphaBeta(mainBoard, depth - 1, true, alpha, beta, firstCoord[i], secondCoord[i])));
            mainBoard.setValue(firstCoord[i],secondCoord[i],0);
            if (alpha >= beta)
            {
                break;
            }
        }
        mainBoard.setValue(x,y,0);

        // mainBoard.setValue(x,y,0);
        return beta;
    }
//    if (isMax == true)
//    {
//        std::vector<AvailableSpot *> tmp_vector;
//
//        tmp_vector = mainBoard.availablespots;
//        int m = INT_MAX;
//
//        for (auto & element: tmp_vector)
//        {
//            int x_cor = element->getX();
//            int y_cor = element->getY();
//
//            std::vector<AvailableSpot *> tmp_vector1;
//            tmp_vector1 = mainBoard.availablespots;
//
//            //mainBoard.putStoneOnBoard(x_cor, y_cor, player, depth);
////            alpha = std::max(minimaxAlphaBeta(mainBoard, depth - 1, false, alpha, beta, x_cor, y_cor), alpha);
//            int temp = minimaxAlphaBeta(mainBoard, depth - 1, false, alpha, beta, x_cor, y_cor);
//            if (m > temp)
//                m = temp;
//            if (beta > m)
//                beta = m;
//            //mainBoard.setValue(x_cor,y_cor, 0);
//            mainBoard.availablespots = tmp_vector1;
//
//            //mainBoard.clearStoneOnBoard(x_cor, y_cor);
//            if (alpha >= beta)
//            {
//                break ;
//            }
//        }
//        mainBoard.setValue(x,y, 0);
//        return m;
////        return alpha;
//    }
//    else
//    {
//        std::vector<AvailableSpot *> tmp_vector;
//
//        tmp_vector = mainBoard.availablespots;
//        int M = INT_MIN;
//        for (auto & element: tmp_vector)
//        {
//            int x_cor = element->getX();
//            int y_cor = element->getY();
//
//            std::vector<AvailableSpot *> tmp_vector1;
//            tmp_vector1 = mainBoard.availablespots;
//
//            //mainBoard.putStoneOnBoard(x_cor, y_cor, player, depth);
////            beta = std::min(minimaxAlphaBeta(mainBoard, depth - 1, true, alpha, beta, x_cor, y_cor), beta);
//            int temp = minimaxAlphaBeta(mainBoard, depth - 1, true, alpha, beta, x_cor, y_cor);
//            if (M < temp){
//                M = temp;
//            }
//            if (alpha < M){
//                alpha = M;
//            }
//            //mainBoard.setValue(x_cor,y_cor, 0);
//            mainBoard.availablespots = tmp_vector1;
//
//            //mainBoard.clearStoneOnBoard(x_cor, y_cor);
//            if (alpha >= beta)
//            {
//                break ;
//            }
//        }
//        mainBoard.setValue(x,y, 0);
//
//        return M;
//        return beta;
//    }
}



/*int ArtificialIntelligence::evaluation(GomokuMainBoard & mainBoard, int isMax)
{
    std::vector<int> computerPattern(POINTS_TO_WIN + 1,0);
    std::vector<int> playerPattern(POINTS_TO_WIN + 1,0);
    int sum = 0;
    for (int  i = 0 ; i < GOMOKU_BOARD_SIZE; i++)
    {
        for (int j = 0; j < GOMOKU_BOARD_SIZE ; j++)
        {
            if (mainBoard.getValue(i,j) != 0)
            {
                int c = mainBoard.getValue(i,j);
                bool needMax = c == AI_PLAYER;
                int sameSymbol = 1; // count same symbols in columns
                int k = 1;
                while (i- k >= 0 && mainBoard.getValue(i-k, j)  == c)
                {
                    sameSymbol++;
                    k++;
                }
                //consider value at i - k later to see if it's blocked or not
                int l = 1;
                while (i + l < GOMOKU_BOARD_SIZE && mainBoard.getValue(i+l, j) == c)
                {
                    sameSymbol++;
                    l++;
                }
                if (sameSymbol >= POINTS_TO_WIN)
                {
                    if (needMax)
                        computerPattern[POINTS_TO_WIN]++;
                    else
                        playerPattern[POINTS_TO_WIN]++;
                }
                else if (sameSymbol == POINTS_TO_WIN - 1 && (mainBoard.checkEmpty(i-k,j) || mainBoard.checkEmpty(i+l,j)))
                {
                    if (needMax)
                        computerPattern[POINTS_TO_WIN-1]++;
                    else
                        playerPattern[POINTS_TO_WIN-1]++;
                }
                else if (sameSymbol == POINTS_TO_WIN - 2 && (mainBoard.checkEmpty(i-k,j) || mainBoard.checkEmpty(i+l,j)))
                {
                    if (needMax)
                        computerPattern[POINTS_TO_WIN-2]++;
                    else
                        playerPattern[POINTS_TO_WIN-2]++;
                }
                else if (sameSymbol == POINTS_TO_WIN - 2 && (mainBoard.checkEmpty(i-k,j) && mainBoard.checkEmpty(i+l,j)))
                {
                    if (needMax)
                        computerPattern[POINTS_TO_WIN-3]++;
                    else
                        playerPattern[POINTS_TO_WIN-3]++;
                }
                else if (sameSymbol == POINTS_TO_WIN - 3 && mainBoard.checkEmpty(i-k,j) && mainBoard.checkEmpty(i+l,j))
                {
                    if (needMax)
                        computerPattern[POINTS_TO_WIN-4]++;
                    else
                        playerPattern[POINTS_TO_WIN-4]++;
                }
                sameSymbol = 1; // count same symbols in rows
                k = 1;
                while (j - k >= 0 && mainBoard.getValue(i, j-k)  == c)
                {
                    sameSymbol++;
                    k++;
                }
                //consider value at i - k later to see if it's blocked or not
                l = 1;
                while (j + l < GOMOKU_BOARD_SIZE && mainBoard.getValue(i, j+l) == c)
                {
                    sameSymbol++;
                    l++;
                }
                if (sameSymbol >= POINTS_TO_WIN)
                {
                    if (needMax)
                        computerPattern[POINTS_TO_WIN]++;
                    else
                        playerPattern[POINTS_TO_WIN]++;
                }
                else if (sameSymbol == POINTS_TO_WIN - 1 && (mainBoard.checkEmpty(i,j-k) || mainBoard.checkEmpty(i,j+l)))
                {
                    if (needMax)
                        computerPattern[POINTS_TO_WIN-1]++;
                    else
                        playerPattern[POINTS_TO_WIN-1]++;
                }
                else if (sameSymbol == POINTS_TO_WIN - 2 && (mainBoard.checkEmpty(i,j-k) || mainBoard.checkEmpty(i,j+l)))
                {
                    if (needMax)
                        computerPattern[POINTS_TO_WIN-2]++;
                    else
                        playerPattern[POINTS_TO_WIN-2]++;
                }
                else if (sameSymbol == POINTS_TO_WIN - 2 && (mainBoard.checkEmpty(i,j-k) && mainBoard.checkEmpty(i,j+l)))
                {
                    if (needMax) computerPattern[POINTS_TO_WIN-3]++;
                    else playerPattern[POINTS_TO_WIN-3]++;
                }
                else if (sameSymbol == POINTS_TO_WIN - 3 && mainBoard.checkEmpty(i,j-k) && mainBoard.checkEmpty(i,j+l))
                {
                    if (needMax) computerPattern[POINTS_TO_WIN-4]++;
                    else playerPattern[POINTS_TO_WIN-4]++;
                }
                sameSymbol = 1;// count same symbols in main diagnol
                k = 1;
                while (i - k >= 0 && j - k >= 0 && mainBoard.getValue(i-k, j- k)  == c)
                {
                    sameSymbol++;
                    k++;
                }
                //consider value at i - k later to see if it's blocked or not
                l = 1;
                while (i + l < GOMOKU_BOARD_SIZE && j + l < GOMOKU_BOARD_SIZE && mainBoard.getValue(i+l, j+l ) == c)
                {
                    sameSymbol++;
                    l++;
                }
                if (sameSymbol >= POINTS_TO_WIN)
                {
                    if (needMax)
                        computerPattern[POINTS_TO_WIN]++;
                    else
                        playerPattern[POINTS_TO_WIN]++;
                }
                else if (sameSymbol == POINTS_TO_WIN - 1 && (mainBoard.checkEmpty(i-k,j-k) || mainBoard.checkEmpty(i+l,j+l)))
                {
                    if (needMax)
                        computerPattern[POINTS_TO_WIN-1]++;
                    else
                        playerPattern[POINTS_TO_WIN-1]++;
                }
                else if (sameSymbol == POINTS_TO_WIN - 2 && (mainBoard.checkEmpty(i-k,j-k) || mainBoard.checkEmpty(i+l,j+l)))
                {
                    if (needMax)
                        computerPattern[POINTS_TO_WIN-2]++;
                    else
                        playerPattern[POINTS_TO_WIN-2]++;
                }
                else if (sameSymbol == POINTS_TO_WIN - 2 && (mainBoard.checkEmpty(i-k,j-k) && mainBoard.checkEmpty(i+l,j+l)))
                {
                    if (needMax)
                        computerPattern[POINTS_TO_WIN-3]++;
                    else
                        playerPattern[POINTS_TO_WIN-3]++;
                }
                else if (sameSymbol == POINTS_TO_WIN - 3 && mainBoard.checkEmpty(i-k,j-k) && mainBoard.checkEmpty(i+l,j+l))
                {
                    if (needMax)
                        computerPattern[POINTS_TO_WIN-4]++;
                    else
                        playerPattern[POINTS_TO_WIN-4]++;
                }
                //-----------------------------------------------------------------------
                sameSymbol = 1;// count same symbols in reverse diagnols
                k = 1;
                while (i - k >= 0 && j + k < GOMOKU_BOARD_SIZE && mainBoard.getValue(i-k, j+ k)  == c)
                {
                    sameSymbol++;
                    k++;
                }
                //consider value at i - k later to see if it's blocked or not
                l = 1;
                while (i + l < GOMOKU_BOARD_SIZE && j - l >= 0 && mainBoard.getValue(i+l, j-l ) == c)
                {
                    sameSymbol++;
                    l++;
                }
                if (sameSymbol >= POINTS_TO_WIN)
                {
                    if (needMax)
                        computerPattern[POINTS_TO_WIN]++;
                    else
                        playerPattern[POINTS_TO_WIN]++;
                }
                else if (sameSymbol == POINTS_TO_WIN - 1 && (mainBoard.checkEmpty(i-k,j+k) || mainBoard.checkEmpty(i+l,j-l)))
                {
                    if (needMax)
                        computerPattern[POINTS_TO_WIN-1]++;
                    else
                        playerPattern[POINTS_TO_WIN-1]++;
                }
                else if (sameSymbol == POINTS_TO_WIN - 2 && (mainBoard.checkEmpty(i-k,j+k) || mainBoard.checkEmpty(i+l,j-l)))
                {
                    if (needMax)
                        computerPattern[POINTS_TO_WIN-2]++;
                    else
                        playerPattern[POINTS_TO_WIN-2]++;
                }
                else if (sameSymbol == POINTS_TO_WIN - 2 && (mainBoard.checkEmpty(i-k,j+k) && mainBoard.checkEmpty(i+l,j-l)))
                {
                    if (needMax)
                        computerPattern[POINTS_TO_WIN-3]++;
                    else
                        playerPattern[POINTS_TO_WIN-3]++;
                }
                else if (sameSymbol == POINTS_TO_WIN - 3 && mainBoard.checkEmpty(i-k,j+k) && mainBoard.checkEmpty(i+l,j-l))
                {
                    if (needMax)
                        computerPattern[POINTS_TO_WIN-4]++;
                    else
                        playerPattern[POINTS_TO_WIN-4]++;
                }
            }
        }
    }
    if (computerPattern[POINTS_TO_WIN] > 0)
        return INT_MAX;
    if (playerPattern[POINTS_TO_WIN] > 0)
        return INT_MIN;
    int x = 1;
    sum += computerPattern[1];
    sum -= playerPattern[1] * 5;
    for (int i = 2 ; i < POINTS_TO_WIN ; i++)
    {
        x *= 100;
        sum += computerPattern[i] * x;
        sum -= playerPattern[i] * x*10 ;
    }
    return sum;
}*/
int ArtificialIntelligence::evaluation(GomokuMainBoard & mainBoard, int isMax){
//    clock_t start = clock();

    int M = 5;
    int N = GOMOKU_BOARD_SIZE;
    int sum = 0;
    std::vector<int> computerPattern(M+1,0);
    std::vector<int> playerPattern(M+1,0);

    for (int  i = 0 ; i < N; i++){
        for (int j = 0; j < N ; j++){
            if (mainBoard.getValue(i,j) != 0){
                int c = mainBoard.getValue(i,j);
                bool needMax = c == AI_PLAYER;



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
                }else if (sameSymbol == M - 2 && (mainBoard.checkEmpty(i-k,j) || mainBoard.checkEmpty(i+l,j)) ){
                    if (needMax) computerPattern[M-2]++;
                    else playerPattern[M-2]++;
                }else if (sameSymbol == M - 2 && (mainBoard.checkEmpty(i-k,j) && mainBoard.checkEmpty(i+l,j)) ){
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
                }else if (sameSymbol == M - 1 && (mainBoard.checkEmpty(i,j-k) || mainBoard.checkEmpty(i,j+l)) ){
                    if (needMax) computerPattern[M-1]++;
                    else playerPattern[M-1]++;
                }else if (sameSymbol == M - 2 && (mainBoard.checkEmpty(i,j-k) || mainBoard.checkEmpty(i,j+l)) ){
                    if (needMax) computerPattern[M-2]++;
                    else playerPattern[M-2]++;
                }else if (sameSymbol == M - 2 && (mainBoard.checkEmpty(i,j-k) && mainBoard.checkEmpty(i,j+l)) ){
                    if (needMax) computerPattern[M-3]++;
                    else playerPattern[M-3]++;
                }else if (sameSymbol == M - 3 && mainBoard.checkEmpty(i,j-k) && mainBoard.checkEmpty(i,j+l) ){
                    if (needMax) computerPattern[M-4]++;
                    else playerPattern[M-4]++;
                }

                //--------------------------------------------------------------

                sameSymbol = 1;// count same symbols in main diagnol
                k = 1;
                while (i - k >= 0 && j - k >= 0 && mainBoard.getValue(i-k, j- k)  == c){
                    sameSymbol++;
                    k++;
                }


                //consider value at i - k later to see if it's blocked or not
                l = 1;
                while (i + l <= N-1 && j + l <= N-1 && mainBoard.getValue(i+l, j+l ) == c){
                    sameSymbol++;
                    l++;
                }

                if (sameSymbol >= M){
                    if (needMax) computerPattern[M]++;
                    else playerPattern[M]++;
                }else if (sameSymbol == M - 1 && (mainBoard.checkEmpty(i-k,j-k) || mainBoard.checkEmpty(i+l,j+l))){
                    if (needMax) computerPattern[M-1]++;
                    else playerPattern[M-1]++;
                }else if (sameSymbol == M - 2 && (mainBoard.checkEmpty(i-k,j-k) || mainBoard.checkEmpty(i+l,j+l))){
                    if (needMax) computerPattern[M-2]++;
                    else playerPattern[M-2]++;
                }else if (sameSymbol == M - 2 && (mainBoard.checkEmpty(i-k,j-k) && mainBoard.checkEmpty(i+l,j+l))){
                    if (needMax) computerPattern[M-3]++;
                    else playerPattern[M-3]++;
                }else if (sameSymbol == M - 3 && mainBoard.checkEmpty(i-k,j-k) && mainBoard.checkEmpty(i+l,j+l)){
                    if (needMax) computerPattern[M-4]++;
                    else playerPattern[M-4]++;
                }



                //-----------------------------------------------------------------------


                sameSymbol = 1;// count same symbols in reverse diagnols
                k = 1;
                while (i - k >= 0 && j + k <= N-1 && mainBoard.getValue(i-k, j+ k)  == c){
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
                }else if (sameSymbol == M - 2 && (mainBoard.checkEmpty(i-k,j+k) || mainBoard.checkEmpty(i+l,j-l))){
                    if (needMax) computerPattern[M-2]++;
                    else playerPattern[M-2]++;
                }else if (sameSymbol == M - 2 && (mainBoard.checkEmpty(i-k,j+k) && mainBoard.checkEmpty(i+l,j-l))){
                    if (needMax) computerPattern[M-3]++;
                    else playerPattern[M-3]++;
                }else if (sameSymbol == M - 3 && mainBoard.checkEmpty(i-k,j+k) && mainBoard.checkEmpty(i+l,j-l)){
                    if (needMax) computerPattern[M-4]++;
                    else playerPattern[M-4]++;
                }


            }
        }
    }
    if (computerPattern[M] > 0) return INT_MAX;
    if (playerPattern[M] > 0) return INT_MIN;
    int x = 1;
    sum += computerPattern[1];
    sum -= playerPattern[1] * 5 ;
    for (int i = 2 ; i < M ; i++){
        x *= 100;
        sum += computerPattern[i] * x;
        sum -= playerPattern[i] * x * 10  ;
    }
//    clock_t end = clock();
//    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
//    printf("The time: %f seconds\n", seconds);
    return sum;
}


bool ArtificialIntelligence::adjacentPlaced(int (& board)[GOMOKU_BOARD_SIZE][GOMOKU_BOARD_SIZE] , int x, int y)
{
    // if(board[x][y] == 0 and x == GOMOKU_BOARD_SIZE / 2 and y == GOMOKU_BOARD_SIZE /2)
    //    return true;
    bool value = false;
    if (board[x][y] != 0)
        return false;
    std::vector<std::vector<int>> adjacent = {{-1,-1},{-1,0}, {-1,1},{0,1},{0,-1},{1,-1},{1,0},{1,1}};

    for (auto d:adjacent){

        if (x+d[0] >=0 && y+d[1]>=0 && x+d[0] <= GOMOKU_BOARD_SIZE-1 && y + d[1] <= GOMOKU_BOARD_SIZE-1){
            value = value || (board[x+d[0]][y+d[1]] != 0);
        }
    }
    return value;
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

int ArtificialIntelligence::getScoreByPatterns(GomokuMainBoard & board, int captured_nb, int player, int x, int y) {
    std::string pattern = "";
    //char pattern[9];
    int total_weight = 0;
    //memset(pattern, 111 ,9);

    //1 діагональ
    for (int i = -4; i < 5; ++i) {
        if (x + i >= 0 and y + i >= 0 and x + i < GOMOKU_BOARD_SIZE and y + i < GOMOKU_BOARD_SIZE)
        {
            if (board.getValue(x + i,y + i) == 0)
                pattern+= '0';
            else
                pattern+= '0' + board.getValue(x + i,y + i);
        }

    }
    total_weight += checkPatternWeight(pattern,captured_nb, player);
    pattern = "";
    for (int i = -4; i < 5; ++i) {
        if (x + i >= 0 and y - i >= 0 and x - i < GOMOKU_BOARD_SIZE and y + i < GOMOKU_BOARD_SIZE)
        {
            if (board.getValue(x + i,y - i) == 0)
                pattern+= '0';
            else
                pattern+= '0' + char(board.getValue(x + i,y + i));
        }
    }
    total_weight += checkPatternWeight(pattern,captured_nb, player);
    pattern = "";

    //вертикаль
    for (int i = -4; i < 5; ++i) {
        if (x + i >= 0 and x + i < GOMOKU_BOARD_SIZE)
        {
            if (board.getValue(x + i,y) == 0)
                pattern+= '0';
            else
                pattern+= '0' + char(board.getValue(x + i,y));
        }
    }
    total_weight += checkPatternWeight(pattern,captured_nb, player);
    pattern = "";

    //горизонталь
    for (int i = -4; i < 5; ++i) {
        if (y + i >= 0 and y + i < GOMOKU_BOARD_SIZE)
        {
            if (board.getValue(x,y + i) == 0)
                pattern+= '0';
            else
                pattern+= '0' + board.getValue(x,y + i);
        }
    }
    total_weight += checkPatternWeight(pattern,captured_nb, player);

    return total_weight;
}

int ArtificialIntelligence::checkPatternWeight(std::string pattern, int player, int captured_nb) {
    int ret = 0;
    std::string toFind;

    for( auto it = patternsHashMap.begin(); it != patternsHashMap.end(); ++it)
    {
        toFind = it->first;
        if (pattern.find(toFind) != -1)
            ret = it->second;
    }
    return ret;
}