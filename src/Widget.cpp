//
// Created by denys on 30.03.19.
//

#include "../headers/Widget.hpp"
#include "../headers/View.hpp"

Widget::Widget(int x, int y, int h, int w) {
    this->_disabled = false;
    this->_messageSurface = nullptr;
    this->_rect.x = x;
    this->_rect.y = y;
    this->_rect.h = h;
    this->_rect.w = w;
    this->_currentBackgroundColor = GREY_COLOR_SDL;
}

Widget::~Widget() {
    SDL_FreeSurface(this->_messageSurface);
}

bool Widget::checkEvent(SDL_Event *event) {
    bool    eventChecked;

    if (this->isDisabled())
        return false;
    eventChecked = false;
    for (const auto &eventHandler : this->_eventHandlers) {
        if (eventHandler(this, event))
            eventChecked = true;
    }
    return eventChecked;
}

void Widget::render(SDL_Renderer *render) {
    if (!render)
        return;
    SDL_SetRenderDrawColor(render,
            this->_currentBackgroundColor.r,
            this->_currentBackgroundColor.g,
            this->_currentBackgroundColor.b,
            this->_currentBackgroundColor.a);
    SDL_SetRenderDrawBlendMode(render, SDL_BLENDMODE_BLEND);
    SDL_RenderFillRect(render, &(this->_rect));
    if (this->_messageSurface)
        this->_showMessage(render);
}

void Widget::_showMessage(SDL_Renderer *renderer) {
    SDL_Texture     *texture;
    SDL_Rect        messageRect;

    messageRect = this->_rect;
    texture = SDL_CreateTextureFromSurface(renderer, this->_messageSurface);
    SDL_QueryTexture(texture, NULL, NULL, &(messageRect.w), &(messageRect.h));
    messageRect.x = CENTER(this->_rect.w, messageRect.w) + this->_rect.x;
    messageRect.y = CENTER(this->_rect.h, messageRect.h) + this->_rect.y;
    SDL_RenderCopy(renderer, texture, NULL, &messageRect);
    SDL_DestroyTexture(texture);
}

void Widget::setBackgroundColor(SDL_Color color) {
    this->_currentBackgroundColor = color;
    this->_originalBackgroundColor = color;
}

void Widget::setBackgroundAlphaColor(unsigned char alpha) {
    this->_currentBackgroundColor.a = alpha;
    this->_originalBackgroundColor.a = alpha;
}

void Widget::addEventHandler(std::function<bool(Widget*, SDL_Event*)> eventHandler) {
    this->_eventHandlers.push_back(eventHandler);
}

bool Widget::visibleCoordinates(int x, int y) {
    return this->_rect.x < x && x < (this->_rect.x + this->_rect.w) &&
    this->_rect.y < y && y < (this->_rect.y + this->_rect.h);
}

void Widget::setText(const char *message, SDL_Color textColor) {
    TTF_Font        *font;

    font = TTF_OpenFont(FONT_FILE, this->_rect.h / 2);
    this->_messageSurface = TTF_RenderText_Solid(font, message, textColor);
    TTF_CloseFont(font);
}

bool Widget::isDisabled() {
    return this->_disabled;
}

void Widget::setDisableValue(bool disable) {
    this->_disabled = disable;
    if (disable) {
        this->_currentBackgroundColor = {
                (Uint8) (this->_originalBackgroundColor.r / 2),
                (Uint8) (this->_originalBackgroundColor.g / 2),
                (Uint8) (this->_originalBackgroundColor.b / 2),
                this->_originalBackgroundColor.r
        };
    } else {
        this->_currentBackgroundColor = this->_originalBackgroundColor;
    }
}
