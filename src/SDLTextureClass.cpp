//
// Created by denys on 20.03.19.
//

#include "../headers/SDLTextureClass.hpp"
#include "../headers/View.hpp"

SDLTextureClass::SDLTextureClass(SDL_Texture *texture) {
	if (!texture)
		throw "Both value are required.";
	this->_setProperties(texture);
	this->_name = "";
}

SDLTextureClass::~SDLTextureClass() {
	std::cout << "Texture " << this->_name << " destroyed." << std::endl;
	SDL_DestroyTexture(this->_texture);
}

void SDLTextureClass::renderTexture(SDL_Renderer *renderer) {
	if (this->_showOnRender) {
		SDL_RenderCopy(renderer, this->_texture,
					   this->_srcExist ? &(this->_srcrect) : NULL,
					   this->_dstExist ? &(this->_dstrect) : NULL);
	}
}

void SDLTextureClass::setDstRenderRect(SDL_Rect *rect) {
	if (rect) {
		this->_dstExist = true;
		memcpy(&(this->_dstrect), rect, sizeof(SDL_Rect));
	} else {
		this->_dstExist = false;
	}
}

void SDLTextureClass::showOnRender(bool show) {
	this->_showOnRender = show;
}

SDLTextureClass::SDLTextureClass(const char *img_file_path, const SDL_Color *srcColor, const SDL_Color *destColor,
								 SDL_Renderer *renderer) {
	this->_name = img_file_path;
	SDL_Surface	*loadedImage = nullptr;
	SDL_Texture	*texture = nullptr;

	if (!img_file_path || !renderer)
		throw  ("SDL error: Can't find image or renderer.");
	loadedImage = IMG_Load(img_file_path);
	if (loadedImage == nullptr) {
		throw  ("SDL error: Can not load image.");
	}
	if (srcColor && destColor)
		this->_changeColor(loadedImage, *srcColor, *destColor);
	texture = SDL_CreateTextureFromSurface(renderer, loadedImage);
	SDL_FreeSurface(loadedImage);
	this->_setProperties(texture);
}

void SDLTextureClass::_changeColor(SDL_Surface *surface, const SDL_Color srcColor, const SDL_Color dstColor) {
	Uint32	*pixels;

	pixels = (Uint32 *) surface->pixels;
	for (int i = 0; i < surface->w * surface->h; i++) {
		if (pixels[i] == SDL_MapRGB(surface->format, srcColor.r, srcColor.g, srcColor.b))
			pixels[i] = (Uint32) SDL_MapRGB(surface->format, dstColor.r, dstColor.g, dstColor.b);
	}
}

void SDLTextureClass::_setProperties(SDL_Texture *texture) {
	this->_srcrect = SDL_Rect{};
	this->_dstrect = SDL_Rect{};
	this->_texture = texture;
	this->_srcExist = false;
	this->_dstExist = false;
	this->_showOnRender = true;
}

int SDLTextureClass::setAsRenderTarget(SDL_Renderer *renderer) {
	if (SDL_SetRenderTarget(renderer, this->_texture) == -1) {
		std::cout << "WARNING: Can't set " << this->_name << " texture as render targer." << std::endl;
		return false;
	}
	return true;
}

void SDLTextureClass::clearTexture(SDL_Renderer *renderer) {
	SDL_Color	color;

	color = {0, 0, 0, 0};
	this->clearTexture(renderer, color);
}

void SDLTextureClass::clearTexture(SDL_Renderer *renderer, SDL_Color color) {
	this->setAsRenderTarget(renderer);
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(renderer);
	SDL_SetRenderTarget(renderer, NULL);
}