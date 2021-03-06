#pragma once

#ifdef __APPLE__
#include "SDL2_ttf/SDL_ttf.h"
#elif _WIN32
#include "SDL_ttf.h"
#endif

#include <map>
#include <string>
#include "TextureManager.h"
#include "Vector2D.h"
#include "ECS/ECS.h"

class AssetManager {
public:
    AssetManager(Manager* man);
    ~AssetManager();
    
    // Game Objects...
    
    //void CreateProjectile(Vector2D pos, Vector2D vel, int range, int speed, std::string id);
    
    
    // Texture management...
    void AddTexture(std::string id, const char* path);
    SDL_Texture* GetTexture(std::string id);
    
    void AddFont(std::string id, std::string path, int fontSize = 16);
    TTF_Font* GetFont(std::string id);
private:
    Manager* manager;
    std::map<std::string, SDL_Texture*> textures;
    std::map<std::string, TTF_Font*> fonts;
};
