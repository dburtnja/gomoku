//
// Created by Mirex on 31.07.2018.
//

#ifndef GOMOKU_AVAIBLESPOT_HPP
#define GOMOKU_AVAIBLESPOT_HPP

#include "MainHeader.hpp"

class AvailableSpot {
    public:
        AvailableSpot();
        ~AvailableSpot();
        AvailableSpot(int x, int y);

        AvailableSpot (const AvailableSpot & toCopy);
        AvailableSpot &operator = (const AvailableSpot & rhs);

        int  getX( void );
        int  getY( void );
        void setX(int x);
        void setY(int y);

        int p1_score = 0;
        int p2_score = 0;

private:
        int _x;
        int _y;

};


#endif //GOMOKU_AVAIBLESPOT_HPP
