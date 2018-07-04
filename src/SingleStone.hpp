//
// Created by mirex on 04.07.2018.
//

#ifndef GOMOKU_SingleStone_HPP
#define GOMOKU_SingleStone_HPP

class SingleStone {
public:
    SingleStone();
    SingleStone(unsigned int Player, unsigned int CordX, unsigned int CordY);
    SingleStone(const SingleStone & toCopy);
    ~SingleStone();
    SingleStone & operator =(const SingleStone & rhs);

protected:
    unsigned int _Player;
    unsigned int getCordX( void );
    unsigned int getCordY( void );
    unsigned int getPlayer( void );
    void setCordX ( unsigned int X );
    void setCordY ( unsigned int Y ) ;

private:
    unsigned    int _xCord;
    unsigned    int _yCord;
};


#endif //GOMOKU_SingleStone_HPP
