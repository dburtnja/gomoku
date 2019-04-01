//
// Created by denys on 30.03.19.
//

#ifndef GOMOKU_WIDGETBUTTONGROUP_HPP
#define GOMOKU_WIDGETBUTTONGROUP_HPP


#include "Widget.hpp"
#include "WidgetButton.hpp"

class WidgetButtonGroup : public Widget {
public:
    WidgetButtonGroup(int x, int y, int h, int w);
    ~WidgetButtonGroup();

    void    addButton(int x, int y, int h, int w, char const *name);
    void    addButton(int x, int y, int h, int w, char const *name, bool setAsDefault);
    int     getSelected();
    void    render(SDL_Renderer *render) override;

private:
    std::list<WidgetButton*>    _buttons;
    int                         _selected;
};


#endif //GOMOKU_WIDGETBUTTONGROUP_HPP
