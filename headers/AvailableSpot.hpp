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

private:
        int _x;
        int _y;
};


#endif //GOMOKU_AVAIBLESPOT_HPP
