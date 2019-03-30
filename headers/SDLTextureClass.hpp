//
// Created by denys on 20.03.19.
//

#ifndef GOMOKU_SDLTEXTURECLASS_HPP
#define GOMOKU_SDLTEXTURECLASS_HPP

#include "MainHeader.hpp"


class SDLTextureClass {
public:
	explicit SDLTextureClass(SDL_Texture *texture);

	SDLTextureClass(const char *img_file_path, const SDL_Color *srcColor, const SDL_Color *destColor,
						SDL_Renderer *renderer);

	~SDLTextureClass();

	void renderTexture(SDL_Renderer *renderer);


	void setDstRenderRect(SDL_Rect *rect);

	void showOnRender(bool show);

	int setAsRenderTarget(SDL_Renderer *renderer);

    void clearTexture(SDL_Renderer *renderer);
    void clearTexture(SDL_Renderer *renderer, SDL_Color color);

private:
	SDL_Texture	*_texture;
	SDL_Rect	_srcrect;
	SDL_Rect	_dstrect;
	bool		_srcExist;
	bool		_dstExist;
	bool		_showOnRender;
	const char 	*_name;


	void _changeColor(SDL_Surface *surface, const SDL_Color srcColor, const SDL_Color dstColor);

	void _setProperties(SDL_Texture *texture);

};


#endif //GOMOKU_SDLTEXTURECLASS_HPP
