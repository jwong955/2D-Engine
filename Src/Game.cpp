#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include "AssetManager.h"
#include <sstream>

Map* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

SDL_Rect Game::camera = { 0,0,800,640 };

AssetManager* Game::assets = new AssetManager(&manager);

bool Game::isRunning = false;

auto& player(manager.addEntity());
auto& label(manager.addEntity());

Game::Game()
{}

Game::~Game()
{}

void Game::init(const char* title, int width, int height, bool fullscreen)
{
    int flags = 0;
    
    if (fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        }
        
        isRunning = true;
    }
    
    if (TTF_Init() == -1) {
        std::cout << "ERROR : SDL_ttf" << std::endl;
    }
    
    assets->AddTexture("terrain", "assets/terrain_ss.png");
    assets->AddTexture("player", "assets/player_anims.png");
    assets->AddTexture("projectile", "assets/projectile.png");
    
    assets->AddFont("arial", "assets/arial.ttf", 16);
    
    map = new Map("terrain", 2, 32);
    
    // ECS implementation
    
    map->LoadMap("assets/map.txt", 25, 20);
    
    player.addComponent<TransformComponent>(4);
    player.addComponent<SpriteComponent>("player", true);
    player.addComponent<KeyboardController>();
    player.addComponent<ColliderComponent>("player");
    player.addGroup(groupPlayers);
    
    SDL_Color white = {255, 255, 255, 255};
    label.addComponent<UILabel>(10, 10, "", "arial", white);
    
    assets->CreateProjectile(Vector2D(600, 600), Vector2D(2, 0), 200, 2, "projectile");
    assets->CreateProjectile(Vector2D(600, 400), Vector2D(2, 1), 200, 2, "projectile");
    assets->CreateProjectile(Vector2D(400, 500), Vector2D(2, -1), 200, 2, "projectile");
    assets->CreateProjectile(Vector2D(500, 550), Vector2D(2, 0), 200, 2, "projectile");
    
    
}

auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& colliders(manager.getGroup(Game::groupColliders));
auto& projectiles(manager.getGroup(Game::groupProjectiles));

void Game::handleEvents() {
    
    SDL_PollEvent(&event);
    
    switch (event.type)
    {
        case SDL_QUIT :
            isRunning = false;
            break;
        default:
            break;
    }
}

void Game::update() {
    
    SDL_Rect playerOldCol = player.getComponent<ColliderComponent>().collider;
    Vector2D playerOldPos = player.getComponent<TransformComponent>().position;
    
    std::stringstream ss;
    ss << "Player position" << playerOldPos;
    label.getComponent<UILabel>().SetLabelText(ss.str(), "arial");
    
    manager.refresh();
    manager.update();
    
    SDL_Rect playerNewCol = player.getComponent<ColliderComponent>().collider;
    Vector2D playerNewPos = player.getComponent<TransformComponent>().position;

    for (auto& c : colliders) {
        SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
        if ((playerNewPos.x <= cCol.x + cCol.w + 3) && !(playerOldPos.x <= cCol.x + cCol.w) && // Left-collision
            (playerNewPos.y >= cCol.y) && (playerNewPos.y <= cCol.y + cCol.h)) {
            player.getComponent<TransformComponent>().position.x = playerOldPos.x;
        }
        if ((playerNewPos.y <= cCol.y + cCol.h + 3) && !(playerOldPos.y <= cCol.y + cCol.h) && // Top-collision
            (playerNewPos.x >= cCol.x) && (playerNewPos.x <= cCol.x + cCol.w)) {
            player.getComponent<TransformComponent>().position.y = playerOldPos.y;
        }
        if ((playerNewPos.x + playerNewCol.w + 3 >= cCol.x) && !(playerOldPos.x + playerOldCol.w >= cCol.x) && // Right-collision
            (playerNewPos.y >= cCol.y) && (playerNewPos.y <= cCol.y + cCol.h)) {
            player.getComponent<TransformComponent>().position.x = playerOldPos.x;
        }
        if ((playerNewPos.y + playerNewCol.h + 3 >= cCol.y) && !(playerOldPos.y + playerOldCol.h >= cCol.y) &&
            (playerNewPos.x >= cCol.x) && (playerNewPos.x <= cCol.x + cCol.w)) {
            player.getComponent<TransformComponent>().position.y = playerOldPos.y;
        }
    }
    
    for (auto& p : projectiles) {
        if (Collision::AABB(player.getComponent<ColliderComponent>().collider, p->getComponent<ColliderComponent>().collider)) {
            std::cout << "Hit player." << std::endl;
            p->destroy();
        }
    }
    
    camera.x = player.getComponent<TransformComponent>().position.x - 400;
    camera.y = player.getComponent<TransformComponent>().position.y - 320;
    
    if (camera.x < 0) {
        camera.x = 0;
    }
    if (camera.y < 0) {
        camera.y = 0;
    }
    if (camera.x > camera.w) {
        camera.x = camera.w;
    }
    if (camera.y > camera.h) {
        camera.y = camera.h;
    }
    
}


void Game::render()
{
    SDL_RenderClear(renderer);
    for (auto& t : tiles) {
        t->draw();
    }
    for (auto& c : colliders) {
        //c->draw();
    }
    for (auto& p : players) {
        p->draw();
    }
    for (auto& p : projectiles) {
        //p->draw();
    }
    
    label.draw();
    
    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}
