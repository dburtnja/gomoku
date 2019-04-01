//
// Created by denys on 30.03.19.
//

#ifndef GOMOKU_WIDGETBUTTON_HPP
#define GOMOKU_WIDGETBUTTON_HPP


#include "Widget.hpp"

class WidgetButton : public Widget {
public:
    WidgetButton(int x, int y, int h, int w);
    ~WidgetButton();

    bool isClicked();
    void setClicked();
    void onHover(std::function<void(WidgetButton*, SDL_Event*)> function);

private:
    bool            _clicked;

    void setUnclicked();
};


#endif //GOMOKU_WIDGETBUTTON_HPP
