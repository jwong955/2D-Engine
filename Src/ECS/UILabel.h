<<<<<<< HEAD
#ifdef __APPLE__
#include "SDL2/SDL.h"
#include "SDL2_ttf/SDL_ttf.h"
#elif _WIN32
#include "SDL.h"
#include "SDL_ttf.h"
#endif

#include "ECS.h"
#include "AssetManager.h"
#include "Game.h"
#include <string>


class UILabel : public Component {
public:
    UILabel(int xpos, int ypos, std::string text, std::string font, SDL_Color& color) : labelText(text), labelFont(font), textColor(color) {
        position.x = xpos;
        position.y = ypos;
        
        SetLabelText(labelText, labelFont);
    }
    
    ~UILabel() {
        
    }
    
    void SetLabelText(std::string text, std::string font) {
        SDL_Surface* surf = TTF_RenderText_Blended(Game::assets->GetFont(font), text.c_str(), textColor);
        labelTexture = SDL_CreateTextureFromSurface(Game::renderer, surf);
        SDL_FreeSurface(surf);
        
        SDL_QueryTexture(labelTexture, nullptr, nullptr, &position.w, &position.h);
    }
    
    void draw() override {
        SDL_RenderCopy(Game::renderer, labelTexture, nullptr, &position);
    }
private:
    SDL_Rect position;
    std::string labelText;
    std::string labelFont;
    SDL_Color textColor;
    SDL_Texture* labelTexture;
};
=======
#pragma once


#include "ECS.h"
#include "../AssetManager.h"
#include "../TextureManager.h"
#include "../Game.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class UILabel : public Component {
public:
	UILabel(int xpos, int ypos, std::string text, std::string font, SDL_Color& color) :
		labelText(text), labelFont(font), textColor(color){
		position.x = xpos;
		position.y = ypos;

		setLabelText(labelText, labelFont);
	}
	~UILabel() {

	}

	void setLabelText(std::string text, std::string font) {
		SDL_Surface* surf = TTF_RenderText_Blended(Game::assets->getFont(font), text.c_str(), textColor);
		labelTexture = SDL_CreateTextureFromSurface(Game::renderer, surf);
		SDL_FreeSurface(surf);

		SDL_QueryTexture(labelTexture, nullptr, nullptr, &position.w, &position.h);
	}

	void draw() override {
		SDL_RenderCopy(Game::renderer, labelTexture, nullptr, &position);
	}

private:
	SDL_Rect position;
	std::string labelText;
	std::string labelFont;
	SDL_Color textColor;
	SDL_Texture* labelTexture;
};
>>>>>>> c5a5f1b2a1081d9080148e41390823e47b8e4659
