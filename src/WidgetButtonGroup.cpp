//
// Created by denys on 30.03.19.
//

#include "../headers/WidgetButtonGroup.hpp"
#include "../headers/WidgetButton.hpp"
#include "../headers/View.hpp"

WidgetButtonGroup::WidgetButtonGroup(int x, int y, int h, int w) : Widget(x, y, h, w) {
    this->_selected = -1;
    this->addEventHandler([](Widget *buttonGroup, SDL_Event *event){
        int i;

        i = 0;
        if (buttonGroup->visibleCoordinates(event->motion.x, event->motion.y)) {
            for (auto *button : ((WidgetButtonGroup*)buttonGroup)->_buttons) {
                if (event->type == SDL_MOUSEBUTTONDOWN) {
                    if (button->checkEvent(event) && button->isClicked()) {
                        for (auto *tmpButton : ((WidgetButtonGroup*)buttonGroup)->_buttons) {
                                tmpButton->setDisableValue(false);
                        }
                        button->setDisableValue(true);
                        ((WidgetButtonGroup*)buttonGroup)->_selected = i;
                    }
                    i++;
                }
            }
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
    this->addButton(x, y, h, w, name, false);
}

void WidgetButtonGroup::addButton(int x, int y, int h, int w, char const *name, bool setAsDefault) {
    WidgetButton    *button;

    if (this->_selected == -1)
        this->_selected = 0;
    button = new WidgetButton(this->_rect.x + x, this->_rect.y + y, h, w);
    button->setBackgroundColor(WHITE_COLOR_SDL);
    button->setText(name, BLACK_COLOR_SDL);
    if (setAsDefault) {
        button->setDisableValue(true);
        this->_selected = static_cast<int>(this->_buttons.size());
    }
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
