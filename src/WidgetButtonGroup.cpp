//
// Created by denys on 30.03.19.
//

#include "../headers/WidgetButtonGroup.hpp"
#include "../headers/WidgetButton.hpp"
#include "../headers/View.hpp"

WidgetButtonGroup::WidgetButtonGroup(int x, int y, int h, int w) : Widget(x, y, h, w) {
    this->_selected = -1;
    this->addEventHandler([](Widget *buttonGroup, SDL_Event *event){
        if (buttonGroup->visibleCoordinates(event->motion.x, event->motion.y)) {
            for (auto *button : ((WidgetButtonGroup*)buttonGroup)->_buttons)
                button->checkEvent(event);
            return true;
        }
        return false;
    });
}

WidgetButtonGroup::~WidgetButtonGroup() {
    for (auto *button : this->_buttons)
        delete button;
}

void WidgetButtonGroup::addButton(int x, int y, int h, int w, char const *name) {
    WidgetButton    *button;

    if (this->_selected == -1)
        this->_selected = 0;
    button = new WidgetButton(this->_rect.x + x, this->_rect.y + y, h, w);
    button->setBackgroundColor(WHITE_COLOR_SDL);
    button->setText(name, BLACK_COLOR_SDL);
    this->_buttons.push_back(button);
}

int WidgetButtonGroup::getSelected() {
    return this->_selected;
}

void WidgetButtonGroup::render(SDL_Renderer *render) {
    Widget::render(render);
    for (auto *button : this->_buttons)
        button->render(render);
}