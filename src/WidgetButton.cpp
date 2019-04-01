//
// Created by denys on 30.03.19.
//

#include <iostream>
#include "../headers/WidgetButton.hpp"
#include "../headers/MainHeader.hpp"

WidgetButton::WidgetButton(int x, int y, int h, int w) : Widget(x, y, h, w) {
    this->_clicked = false;
    this->addEventHandler([](Widget *button, SDL_Event *event){
        if (event->type == SDL_MOUSEMOTION) {
            if (button->visibleCoordinates(event->motion.x, event->motion.y)) {
                ((WidgetButton*)button)->_currentBackgroundColor = {
                        (Uint8)(((WidgetButton*)button)->_originalBackgroundColor.r),
                        (Uint8)(((WidgetButton*)button)->_originalBackgroundColor.g),
                        (Uint8)(((WidgetButton*)button)->_originalBackgroundColor.b),
                        (Uint8)(((WidgetButton*)button)->_originalBackgroundColor.r - 50)
                };
            } else {
                ((WidgetButton*)button)->_currentBackgroundColor = ((WidgetButton*)button)->_originalBackgroundColor;
            }
        } else
        if (event->type == SDL_MOUSEBUTTONDOWN and button->visibleCoordinates(event->motion.x, event->motion.y)) {
            ((WidgetButton*)button)->setClicked();
            return true;
        }
        if (event->type == SDL_MOUSEBUTTONUP and button->visibleCoordinates(event->motion.x, event->motion.y)) {
            ((WidgetButton*)button)->setUnclicked();
            return true;
        }
        return false;
    });
}

WidgetButton::~WidgetButton() {
}

bool WidgetButton::isClicked() {
    return this->_clicked;
}

void WidgetButton::onHover(std::function<void(WidgetButton*, SDL_Event*)> function) {
    this->addEventHandler([&function](Widget *button, SDL_Event *event){
        if (event->type == SDL_MOUSEMOTION) {
            if (button->visibleCoordinates(event->motion.x, event->motion.y)) {
                function((WidgetButton *) button, event);
                return true;
            }
        }
        return false;
    });
}

void WidgetButton::setClicked() {
    this->_clicked = true;
    this->_currentBackgroundColor = {
            (Uint8)(this->_originalBackgroundColor.r / 2),
            (Uint8)(this->_originalBackgroundColor.g / 2),
            (Uint8)(this->_originalBackgroundColor.b / 2),
            this->_originalBackgroundColor.r
    };
}

void WidgetButton::setUnclicked() {
    this->_clicked = false;
    this->_currentBackgroundColor = this->_originalBackgroundColor;
}
