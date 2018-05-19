#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"
<<<<<<< HEAD
#include "AssetManager.h"
#include <sstream>
=======
#include "AssetManager.h"
#include <sstream>
>>>>>>> c5a5f1b2a1081d9080148e41390823e47b8e4659

Map* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

<<<<<<< HEAD
SDL_Rect Game::camera = { 0,0,800,640 };

=======
SDL_Rect Game::camera = { 0,0,800,640 };

>>>>>>> c5a5f1b2a1081d9080148e41390823e47b8e4659
AssetManager* Game::assets = new AssetManager(&manager);

bool Game::isRunning = false;

auto& player(manager.addEntity());
<<<<<<< HEAD
auto& label(manager.addEntity());
=======
auto& label(manager.addEntity());


>>>>>>> c5a5f1b2a1081d9080148e41390823e47b8e4659

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
<<<<<<< HEAD
    
    if (TTF_Init() == -1) {
        std::cout << "ERROR : SDL_ttf" << std::endl;
    }
    
    assets->AddTexture("terrain", "assets/terrain_ss.png");
    assets->AddTexture("player", "assets/player_anims.png");
    assets->AddTexture("projectile", "assets/proj.png");
    
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
    
=======

	if (TTF_Init() == -1) {
		std::cout << "Error : SDL_TTF" << std::endl;
	}

	assets->addTexture("terrain", "assets/terrain_ss.png");
	assets->addTexture("player", "assets/player_anims.png");
	assets->addTexture("projectile", "assets/projectile.png");

	assets->addFont("times", "assets/times.ttf", 24);

	map = new Map("terrain", 2, 32);

	map->LoadMap("assets/map.map", 25, 20);

	player.addComponent<TransformComponent>(800,640,32,32,4);
	player.addComponent<SpriteComponent>("player", true);
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	player.addGroup(groupPlayers);

	SDL_Color white = { 255,255,255,255 };
	label.addComponent<UILabel>(10, 10, "Score", "times", white);

	assets->createProjectile(Vector2D(600, 600), Vector2D(2,0), 200, 2, "projectile");
	assets->createProjectile(Vector2D(600, 620), Vector2D(2, 0), 200, 2, "projectile");
	assets->createProjectile(Vector2D(400, 600), Vector2D(2, 1), 200, 2, "projectile");
	assets->createProjectile(Vector2D(600, 600), Vector2D(2, -1), 200, 2, "projectile");
	assets->createProjectile(Vector2D(600, 600), Vector2D(2, 3), 200, 2, "projectile");
	assets->createProjectile(Vector2D(600, 600), Vector2D(1, 2), 200, 2, "projectile");
}

auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& colliders(manager.getGroup(Game::groupColliders));
auto& projectiles(manager.getGroup(Game::groupProjectiles));

void Game::handleEvents()
{
	
	
>>>>>>> c5a5f1b2a1081d9080148e41390823e47b8e4659
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

<<<<<<< HEAD
void Game::update() {
    
    SDL_Rect playerCol = player.getComponent<ColliderComponent>().collider;
    Vector2D playerPos = player.getComponent<TransformComponent>().position;

    std::stringstream ss;
    ss << "Player position" << playerPos;
    label.getComponent<UILabel>().SetLabelText(ss.str(), "arial");
    
	manager.refresh();
	manager.update();

    for (auto& c : colliders) {
        SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
        if (Collision::AABB(cCol, playerCol)) {
            player.getComponent<TransformComponent>().position = playerPos;
        }
    }
    
    for (auto& p : projectiles) {
        if (Collision::AABB(player.getComponent<ColliderComponent>().collider, p->getComponent<ColliderComponent>().collider)) {
            std::cout << "Hit player." << std::endl;
            p->destroy();
        }
    }
    
=======
void Game::update()
{
	SDL_Rect playerCol = player.getComponent <ColliderComponent>().collider;
	Vector2D playerPos = player.getComponent<TransformComponent>().position;

	std::stringstream ss;
	ss << "Player position: " << playerPos;
	label.getComponent<UILabel>().setLabelText(ss.str(), "times");

	manager.refresh();
	manager.update();

	for (auto& c : colliders) {
		SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
		if (Collision::AABB(cCol, playerCol)) {
			std::cout << "hit" << std::endl;
			player.getComponent<TransformComponent>().position = playerPos;
		}
	}

	for (auto& p : projectiles) {
		if (Collision::AABB(player.getComponent<ColliderComponent>().collider, p->getComponent<ColliderComponent>().collider)) {
			std::cout << "Hit player!" << std::endl;
			p->destroy();
		}
	}
>>>>>>> c5a5f1b2a1081d9080148e41390823e47b8e4659
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
<<<<<<< HEAD
	}
    for (auto& c : colliders) {
        c->draw();
    }
	for (auto& p : players) {
		p->draw();
	}
    for (auto& p : projectiles) {
        p->draw();
    }
    
    label.draw();
    
=======
	}
	for (auto& c : colliders) {
		c->draw();
	}
	for (auto& p : players) {
		p->draw();
	}
	for (auto& p : projectiles) {
		p->draw();
	}
	label.draw();
>>>>>>> c5a5f1b2a1081d9080148e41390823e47b8e4659
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}
<<<<<<< HEAD

=======
>>>>>>> c5a5f1b2a1081d9080148e41390823e47b8e4659
