//
// Created by denys on 03.04.19.
//

#include "../headers/WidgetMenuField.hpp"
#include "../headers/WidgetLabel.hpp"
#include "../headers/View.hpp"

WidgetMenuField::WidgetMenuField(int x, int y, int h, int w) : Widget(x, y, h, w) {

}

WidgetMenuField::~WidgetMenuField() {
    for (auto widget : this->_widgets)
        delete widget;
}

long WidgetMenuField::addLabel(int x, int y, int h, int w, const char *message) {
    WidgetLabel *label;

    label = new WidgetLabel(this->_rect.x + x, this->_rect.y + y, h, w);
    label->setBackgroundColor(WHITE_COLOR_SDL);
    label->setText(message, BLACK_COLOR_SDL);
    this->_widgets.push_back(label);
    return this->_widgets.size() - 1;
}

void WidgetMenuField::render(SDL_Renderer *render) {
    Widget::render(render);
    for (auto widget : this->_widgets)
        widget->render(render);
}

Widget *WidgetMenuField::getWidgetById(long id) {
    if ((long) this->_widgets.size() > id and id >= 0)
        return this->_widgets[id];
    return nullptr;
}
