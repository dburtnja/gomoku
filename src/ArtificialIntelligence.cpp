
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

bool mySortPlayer1(const AvailableSpot a, const AvailableSpot b )
{
    return abs(a.p1_score) > abs(b.p1_score);
}

Move ArtificialIntelligence::runAI(GomokuMainBoard & mainBoard, APlayer * player_1, APlayer * player_2)
{
    Move move{};
    srand(time(NULL));

        std::sort(mainBoard.availablespots.begin(), mainBoard.availablespots.end(), mySortPlayer1);
    move = minmaxSearch(mainBoard, player_1, player_2);
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
    int timeCprrection = 1;

    std::vector<AvailableSpot > tmp_vector;
    tmp_vector = mainBoard.availablespots;

    for(auto & element: tmp_vector) {
        int x_cor = element.getX();
        int y_cor = element.getY();
        int tmp = minimaxAlphaBeta (mainBoard, REC_DEPT - timeCprrection, true, INT_MIN, INT_MAX, x_cor, y_cor, player_1, player_2);
        //printf("SCORE = %d\n", tmp);
        mainBoard.setValue(x_cor, y_cor, player_1->getPlayerSymbol());
        int capture = mainBoard.check_for_capture(x_cor, y_cor, player_1, player_2, false, move.coordinatesList);
        mainBoard.setValue(x_cor, y_cor, EMPTY_CELL_ON_MAP);
        if (tmp > 0 && tmp < INT_MAX)
            tmp += capture;
        mainBoard.setValue(x_cor, y_cor, player_2->getPlayerSymbol());
        capture = mainBoard.check_for_capture(x_cor, y_cor, player_2, player_1, false, move.coordinatesList);
        mainBoard.setValue(x_cor, y_cor, EMPTY_CELL_ON_MAP);
        if (tmp > 0 && tmp < INT_MAX)
            tmp += capture * 2;
        if (tmp > value)
        {
            value = tmp;
            x = x_cor;
            y = y_cor;
        }

        if (player_1->getPlayerSymbol() == FIRST_PLAYER_ON_MAP)
            element.p1_score = tmp;
        else
            element.p2_score = tmp;
        clock_t end = clock();
        seconds = (double)(end - start) / CLOCKS_PER_SEC;
        if (tmp == INT_MAX || seconds > 0.48)
            break ;
        if (seconds >= 0.43)
            timeCprrection = 10;
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

int ArtificialIntelligence::minimaxAlphaBeta(GomokuMainBoard & mainBoard, int depth, bool isMax, int alpha, int beta,
                                                int x, int y, APlayer * player_1, APlayer * player_2){
    std::vector<AvailableSpot> tmp_vector_old;
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
    if (depth <= 0)
    {
        int capture_value = 0;

        if (isMax)
            capture_value = mainBoard.check_for_capture(x, y, player_1, player_2, false, move.coordinatesList);
        else
            capture_value = mainBoard.check_for_capture(x, y, player_2, player_1, false, move.coordinatesList) * 2;

        value = evaluation(mainBoard, player_1->getPlayerSymbol());
        if (value > 0)
            value+=capture_value;
        mainBoard.setValue(x, y, EMPTY_CELL_ON_MAP);
        mainBoard.availablespots.erase(mainBoard.availablespots.begin(), mainBoard.availablespots.end());
        mainBoard.availablespots = tmp_vector_old;
        return value;
    }

    if (isMax)
    {
        int m = INT_MAX;
        std::vector<AvailableSpot> tmp_vector;
        tmp_vector = mainBoard.availablespots;

        std::sort(mainBoard.availablespots.begin(), mainBoard.availablespots.end(), mySortPlayer1);
        for (auto & element: tmp_vector)
        {
            int x_cor = element.getX();
            int y_cor = element.getY();

            int temp = minimaxAlphaBeta(mainBoard, depth - 1, false, alpha, beta, x_cor, y_cor, player_1, player_2);

            if (m > temp)
                m = temp;
            if (beta > m)
                beta = m;
            if (alpha >= beta)
                break ;
        }
        mainBoard.availablespots.erase(mainBoard.availablespots.begin(), mainBoard.availablespots.end());
        mainBoard.availablespots = tmp_vector;
        mainBoard.setValue(x,y, EMPTY_CELL_ON_MAP);
        return m;
    }
    else
    {
        int M = INT_MIN;
        std::vector<AvailableSpot > tmp_vector;
        tmp_vector = mainBoard.availablespots;

        std::sort(mainBoard.availablespots.begin(), mainBoard.availablespots.end(), mySortPlayer1);
        for (auto & element: tmp_vector)
        {
            int x_cor = element.getX();
            int y_cor = element.getY();
            int temp = minimaxAlphaBeta(mainBoard, depth - 1, true, alpha, beta, x_cor, y_cor, player_1, player_2);

            if (M < temp)
                M = temp;
            if (alpha < M)
                alpha = M;
            if (alpha >= beta)
                break ;
        }
        mainBoard.availablespots.erase(mainBoard.availablespots.begin(), mainBoard.availablespots.end());
        mainBoard.availablespots = tmp_vector;
        mainBoard.setValue(x,y, EMPTY_CELL_ON_MAP);
        return M;
    }
}

void ArtificialIntelligence::checkSymbolsInColomns(GomokuMainBoard &mainBoard, int i, int j, int c, bool needMax,
                                                    std::vector<int> & firstPlayerPattern, std::vector<int> &secondPlayerPattern) {
    int sameSymbol = 1;
    int k = 1;

    while (i - k >= 0 && mainBoard.getValue(i - k, j)  == c){
        sameSymbol++;
        k++;
    }

    //consider value at i - k later to see if it's blocked or not
    int l = 1;
    while (i + l < GOMOKU_BOARD_SIZE && mainBoard.getValue(i + l, j) == c){
        sameSymbol++;
        l++;
    }

    if (sameSymbol >= POINTS_TO_WIN){
        if (needMax)
            firstPlayerPattern[POINTS_TO_WIN]++;
        else
            secondPlayerPattern[POINTS_TO_WIN]++;
    }
    else if (sameSymbol == POINTS_TO_WIN - 1 && (mainBoard.checkEmpty(i-k,j) || mainBoard.checkEmpty(i+l,j)) ){
        if (needMax)
            firstPlayerPattern[POINTS_TO_WIN-1]++;
        else
            secondPlayerPattern[POINTS_TO_WIN-1]++;
    }
    else if (sameSymbol == POINTS_TO_WIN - 2 && (mainBoard.checkEmpty(i-k,j) && mainBoard.checkEmpty(i+l,j)) )
    {
        if (needMax)
            firstPlayerPattern[POINTS_TO_WIN-2] ++;
        else
            secondPlayerPattern[POINTS_TO_WIN-2] ++;
    }
    else if (sameSymbol == POINTS_TO_WIN - 2 && (mainBoard.checkEmpty(i-k,j) || mainBoard.checkEmpty(i+l,j)) ){
        if (needMax)
            firstPlayerPattern[POINTS_TO_WIN-3]++;
        else
            secondPlayerPattern[POINTS_TO_WIN-3]++;
    }
    else if (sameSymbol == POINTS_TO_WIN - 3 && mainBoard.checkEmpty(i-k,j) && mainBoard.checkEmpty(i+l,j) ){
        if (needMax)
            firstPlayerPattern[POINTS_TO_WIN-4]++;
        else
            secondPlayerPattern[POINTS_TO_WIN-4]++;
    }
}
void ArtificialIntelligence::checkSymbolsInRows(GomokuMainBoard &mainBoard, int i, int j, int c, bool needMax,
                                                std::vector<int> &firstPlayerPattern,
                                                std::vector<int> &secondPlayerPattern) {
    int sameSymbol = 1;
    int k = 1;
    while (j - k >= 0 && mainBoard.getValue(i, j-k)  == c){
        sameSymbol++;
        k++;
    }
    //consider value at i - k later to see if it's blocked or not
    int l = 1;
    while (j + l < GOMOKU_BOARD_SIZE && mainBoard.getValue(i, j+l) == c){
        sameSymbol++;
        l++;
    }

    if (sameSymbol >= POINTS_TO_WIN){
        if (needMax)
            firstPlayerPattern[POINTS_TO_WIN]++;
        else
            secondPlayerPattern[POINTS_TO_WIN]++;
    }
    else if (sameSymbol == POINTS_TO_WIN - 1 && (mainBoard.checkEmpty(i, j - k) || mainBoard.checkEmpty(i, j + l)) )
    {
        if (needMax)
            firstPlayerPattern[POINTS_TO_WIN - 1]++;
        else
            secondPlayerPattern[POINTS_TO_WIN - 1]++;
    }
    else if (sameSymbol == POINTS_TO_WIN - 2 && (mainBoard.checkEmpty(i,j-k) && mainBoard.checkEmpty(i,j + l)) )
    {
        if (needMax)
            firstPlayerPattern[POINTS_TO_WIN - 2] ++;
        else
            secondPlayerPattern[POINTS_TO_WIN - 2] ++;
    }
    else if (sameSymbol == POINTS_TO_WIN - 2 && (mainBoard.checkEmpty(i,j-k) || mainBoard.checkEmpty(i,j + l)) )
    {
        if (needMax)
            firstPlayerPattern[POINTS_TO_WIN - 3]++;
        else
            secondPlayerPattern[POINTS_TO_WIN - 3]++;
    }
    else if (sameSymbol == POINTS_TO_WIN - 3 && mainBoard.checkEmpty(i, j - k) && mainBoard.checkEmpty(i, j + l) )
    {
        if (needMax)
            firstPlayerPattern[POINTS_TO_WIN - 4]++;
        else
            secondPlayerPattern[POINTS_TO_WIN - 4]++;
    }
}
void ArtificialIntelligence::checkSymbolsInMainDiaginal(GomokuMainBoard &mainBoard, int i, int j, int c, bool needMax,
                                                        std::vector<int> &firstPlayerPattern,
                                                        std::vector<int> &secondPlayerPattern) {
    int sameSymbol = 1;
    int k = 1;
    while (i - k >= 0 && j - k >= 0 && mainBoard.getValue(i - k, j- k)  == c){
        sameSymbol++;
        k++;
    }
    //consider value at i - k later to see if it's blocked or not
    int l = 1;
    while (i + l < GOMOKU_BOARD_SIZE && j + l < GOMOKU_BOARD_SIZE && mainBoard.getValue(i + l, j + l ) == c){
        sameSymbol++;
        l++;
    }
    if (sameSymbol >= POINTS_TO_WIN){
        if (needMax)
            firstPlayerPattern[POINTS_TO_WIN]++;
        else
            secondPlayerPattern[POINTS_TO_WIN]++;
    }else if (sameSymbol == POINTS_TO_WIN - 1 && (mainBoard.checkEmpty(i-k,j-k) || mainBoard.checkEmpty(i+l,j+l))){
        if (needMax)
            firstPlayerPattern[POINTS_TO_WIN - 1]++;
        else
            secondPlayerPattern[POINTS_TO_WIN - 1]++;
    }else if (sameSymbol == POINTS_TO_WIN - 2 && (mainBoard.checkEmpty(i - k,j - k) && mainBoard.checkEmpty(i + l,j + l)))
    {
        if (needMax)
            firstPlayerPattern[POINTS_TO_WIN - 2] ++;
        else
            secondPlayerPattern[POINTS_TO_WIN - 2] ++;
    }
    else if (sameSymbol == POINTS_TO_WIN - 2 && (mainBoard.checkEmpty(i-k,j-k) || mainBoard.checkEmpty(i+l,j+l))){
        if (needMax)
            firstPlayerPattern[POINTS_TO_WIN-3]++;
        else
            secondPlayerPattern[POINTS_TO_WIN - 3]++;
    }else if (sameSymbol == POINTS_TO_WIN - 3 && mainBoard.checkEmpty(i-k,j-k) && mainBoard.checkEmpty(i+l,j+l)){
        if (needMax)
            firstPlayerPattern[POINTS_TO_WIN - 4]++;
        else
            secondPlayerPattern[POINTS_TO_WIN - 4]++;
    }
}
void ArtificialIntelligence::checkSymbolsInReverseDiaginal(GomokuMainBoard &mainBoard, int i, int j, int c,
                                                           bool needMax, std::vector<int> &firstPlayerPattern,
                                                           std::vector<int> &secondPlayerPattern) {
    int sameSymbol = 1;
    int k = 1;
    while (i - k >= 0 && j + k < GOMOKU_BOARD_SIZE && mainBoard.getValue(i - k, j + k)  == c){
        sameSymbol++;
        k++;
    }
    int l = 1;
    while (i + l <= GOMOKU_BOARD_SIZE && j - l >= 0 && mainBoard.getValue(i+l, j-l ) == c){
        sameSymbol++;
        l++;
    }
    if (sameSymbol >= POINTS_TO_WIN){
        if (needMax)
            firstPlayerPattern[POINTS_TO_WIN]++;
        else
            secondPlayerPattern[POINTS_TO_WIN]++;
    }else if (sameSymbol == POINTS_TO_WIN - 1 && (mainBoard.checkEmpty(i-k,j+k) || mainBoard.checkEmpty(i+l,j-l))){
        if (needMax)
            firstPlayerPattern[POINTS_TO_WIN - 1]++;
        else
            secondPlayerPattern[POINTS_TO_WIN - 1]++;
    }
    else if (sameSymbol == POINTS_TO_WIN - 2 && (mainBoard.checkEmpty(i-k,j+k) && mainBoard.checkEmpty(i+l,j-l)))
    {
        if (needMax)
            firstPlayerPattern[POINTS_TO_WIN - 2]++;
        else
            secondPlayerPattern[POINTS_TO_WIN - 2]++;
    }
    else if (sameSymbol == POINTS_TO_WIN - 2 && (mainBoard.checkEmpty(i-k,j+k) || mainBoard.checkEmpty(i+l,j-l))){
        if (needMax)
            firstPlayerPattern[POINTS_TO_WIN - 3]++;
        else secondPlayerPattern[POINTS_TO_WIN - 3]++;
    }else if (sameSymbol == POINTS_TO_WIN - 3 && mainBoard.checkEmpty(i-k,j+k) && mainBoard.checkEmpty(i+l,j-l)){
        if (needMax)
            firstPlayerPattern[POINTS_TO_WIN - 4]++;
        else secondPlayerPattern[POINTS_TO_WIN - 4]++;
    }
}

int ArtificialIntelligence::evaluation(GomokuMainBoard &mainBoard, int player_1)
{
    int sum = 0;
    std::vector<int> firstPlayerPattern(POINTS_TO_WIN + 1, 0);
    std::vector<int> secondPlayerPattern(POINTS_TO_WIN + 1, 0);

    for (int  i = 0 ; i < GOMOKU_BOARD_SIZE; i++){
        for (int j = 0; j < GOMOKU_BOARD_SIZE ; j++){
            if (mainBoard.getValue(i,j) != 0){
                int c = mainBoard.getValue(i,j);
                bool needMax = c == player_1;

                checkSymbolsInReverseDiaginal(mainBoard, i, j, c, needMax, firstPlayerPattern, secondPlayerPattern);
                checkSymbolsInColomns(mainBoard, i, j, c, needMax, firstPlayerPattern, secondPlayerPattern);
                checkSymbolsInRows(mainBoard, i, j, c, needMax, firstPlayerPattern, secondPlayerPattern);
                checkSymbolsInMainDiaginal(mainBoard, i, j, c, needMax, firstPlayerPattern, secondPlayerPattern);
            }
        }
    }
    if (firstPlayerPattern[POINTS_TO_WIN] > 0)
        return INT_MAX - 100;
    if (secondPlayerPattern[POINTS_TO_WIN] > 0)
       return INT_MIN + 100;

    int x = 1;
    sum += firstPlayerPattern[1] + rand() % 3;
    sum -= secondPlayerPattern[1] * 5 + rand() % 3  ;
    for (int i = 2 ; i < POINTS_TO_WIN ; i++){
        x *= 100;
        sum += firstPlayerPattern[i] * x;
        sum -= secondPlayerPattern[i] * x * 20;
    }
    return sum;
}