//
// Created by denys on 30.03.19.
//

#ifndef GOMOKU_WIDGET_HPP
#define GOMOKU_WIDGET_HPP


#include <SDL2/SDL.h>
#include <functional>
#include <list>

class Widget {
public:
    Widget(int x, int y, int h, int w);
    virtual ~Widget();

    bool checkEvent(SDL_Event *event);

    virtual void render(SDL_Renderer *render);

    Widget * setBackgroundColor(SDL_Color color);
    void    setBackgroundAlphaColor(unsigned char alpha);
    void    setText(const char *message, SDL_Color textColor);
    void    setDisableValue(bool disable);

    void    addEventHandler(std::function<bool(Widget*, SDL_Event*)>);
    bool    visibleCoordinates(int x, int y);
    bool    isDisabled();
    int     getW();


protected:
    SDL_Rect                                    _rect;
    SDL_Color                                   _currentBackgroundColor;
    SDL_Color                                   _originalBackgroundColor;

private:
    std::list<std::function<bool(Widget*, SDL_Event*)>> _eventHandlers;
    SDL_Surface                                         *_messageSurface;
    bool                                                _disabled;

    void _showMessage(SDL_Renderer *renderer);
};


#endif //GOMOKU_WIDGET_HPP
