//
// Created by denys on 03.04.19.
//

#ifndef GOMOKU_WIDGETMENUFIELD_HPP
#define GOMOKU_WIDGETMENUFIELD_HPP


#include <vector>
#include "Widget.hpp"

class WidgetMenuField : public Widget {
public:
    WidgetMenuField(int x, int y, int h, int w);
    ~WidgetMenuField();

    long addLabel(int x, int y, int h, int w, const char *message);
    void render(SDL_Renderer *renderer);

    Widget *getWidgetById(long id);

private:
    std::vector<Widget*>    _widgets;
};


#endif //GOMOKU_WIDGETMENUFIELD_HPP
