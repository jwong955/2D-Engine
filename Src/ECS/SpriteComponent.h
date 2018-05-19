#pragma once


#ifdef __APPLE__
#include "SDL2/SDL.h"
#elif _WIN32
#include "SDL.h"
#endif

#include "Components.h"
#include "../TextureManager.h"
#include "Animation.h"
<<<<<<< HEAD
#include <map>
#include "AssetManager.h"
=======
#include <map>
#include "..\AssetManager.h"
>>>>>>> c5a5f1b2a1081d9080148e41390823e47b8e4659

class SpriteComponent : public Component {
private:
	TransformComponent *transform;
	SDL_Texture *texture;
	SDL_Rect srcRect, destRect;

	bool animated = false;
	int frames = 0;
	int speed = 100;

public:

	int animIndex = 0;

	std::map<const char*, Animation> animations;

	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

	SpriteComponent() = default;
<<<<<<< HEAD
    SpriteComponent(std::string id) {
		setTex(id);
	}
    SpriteComponent(std::string id, bool isAnimated) {
=======
	SpriteComponent(std::string id) {
		setTex(id);
	}
	SpriteComponent(std::string id, bool isAnimated) {
>>>>>>> c5a5f1b2a1081d9080148e41390823e47b8e4659
		animated = isAnimated;

		Animation idle = Animation(0, 3, 100);
		Animation walk = Animation(1, 8, 100);

		animations.emplace("Idle", idle);
		animations.emplace("Walk", walk);

		play("Idle");
		setTex(id);
	}
	~SpriteComponent() {
		
	}

<<<<<<< HEAD
    void setTex(std::string id) {
		texture = Game::assets->GetTexture(id);
=======
	void setTex(std::string id) {
		texture = Game::assets->getTexture(id);
>>>>>>> c5a5f1b2a1081d9080148e41390823e47b8e4659
	}
	void init() override {

		transform = &entity->getComponent<TransformComponent>();

		srcRect.x = srcRect.y = 0;
		srcRect.w = transform->width;
		srcRect.h = transform->height;
	}

	void update() override {
		if (animated) {
			srcRect.x = srcRect.w*static_cast<int>((SDL_GetTicks() / speed) % frames);
		}
		srcRect.y = animIndex * transform->height;
		destRect.x = static_cast<int>(transform->position.x) - Game::camera.x;
		destRect.y = static_cast<int>(transform->position.y) - Game::camera.y;
		destRect.w = transform->width*transform->scale;
		destRect.h = transform->height*transform->scale;
	}
	
	void draw() override {
		TextureManager::Draw(texture, srcRect, destRect,spriteFlip);
	}

	void play(const char* animName) {
		frames = animations[animName].frames;
		animIndex = animations[animName].index;
		speed = animations[animName].speed;
	}
};
