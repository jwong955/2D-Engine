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
double score=0;
int health=100;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

SDL_Rect Game::camera = { 0,0,800,640 };

AssetManager* Game::assets = new AssetManager(&manager);

bool Game::isRunning = false;

auto& player(manager.addEntity());
auto& pScore(manager.addEntity());
auto& enemy1(manager.addEntity());
auto& enemy2(manager.addEntity());
auto& enemy3(manager.addEntity());
auto& enemy4(manager.addEntity());
auto& enemy5(manager.addEntity());
auto& enemy6(manager.addEntity());
auto& enemy7(manager.addEntity());
auto& enemy8(manager.addEntity());
auto& enemy9(manager.addEntity());
auto& enemy10(manager.addEntity());
auto& pHealth(manager.addEntity());

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
		std::cout << "Error : SDL_TTF" << std::endl;
	}

	assets->addTexture("terrain", "assets/terrain_ss.png");
	assets->addTexture("player", "assets/player_anims.png");
	assets->addTexture("enemy", "assets/enemy.png");

	assets->addFont("arcade", "assets/ARCADECLASSIC.ttf", 30);

	map = new Map("terrain", 2, 32);

	map->LoadMap("assets/map.map", 25, 20);

	player.addComponent<TransformComponent>(800,640,32,32,4);
	player.addComponent<SpriteComponent>("player", true);
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	player.addGroup(groupPlayers);

	enemy1.addComponent<TransformComponent>(600, 600, 32, 32, 4);
	enemy1.addComponent<SpriteComponent>("enemy", true);
	enemy1.addComponent<ColliderComponent>("enemy");
	enemy1.addGroup(groupEnemies);

	enemy2.addComponent<TransformComponent>(400, 600, 32, 32, 4);
	enemy2.addComponent<SpriteComponent>("enemy", true);
	enemy2.addComponent<ColliderComponent>("enemy");
	enemy2.addGroup(groupEnemies);

	enemy3.addComponent<TransformComponent>(300,600, 32, 32, 4);
	enemy3.addComponent<SpriteComponent>("enemy", true);
	enemy3.addComponent<ColliderComponent>("enemy");
	enemy3.addGroup(groupEnemies);

	enemy4.addComponent<TransformComponent>(1000,550, 32, 32, 4);
	enemy4.addComponent<SpriteComponent>("enemy", true);
	enemy4.addComponent<ColliderComponent>("enemy");
	enemy4.addGroup(groupEnemies);

	enemy5.addComponent<TransformComponent>(900, 700, 32, 32, 4);
	enemy5.addComponent<SpriteComponent>("enemy", true);
	enemy5.addComponent<ColliderComponent>("enemy");
	enemy5.addGroup(groupEnemies);

	enemy6.addComponent<TransformComponent>(100, 100, 32, 32, 4);
	enemy6.addComponent<SpriteComponent>("enemy", true);
	enemy6.addComponent<ColliderComponent>("enemy");
	enemy6.addGroup(groupEnemies);

	enemy7.addComponent<TransformComponent>(100, 700, 32, 32, 4);
	enemy7.addComponent<SpriteComponent>("enemy", true);
	enemy7.addComponent<ColliderComponent>("enemy");
	enemy7.addGroup(groupEnemies);

	enemy8.addComponent<TransformComponent>(200, 300, 32, 32, 4);
	enemy8.addComponent<SpriteComponent>("enemy", true);
	enemy8.addComponent<ColliderComponent>("enemy");
	enemy8.addGroup(groupEnemies);

	enemy9.addComponent<TransformComponent>(1200, 600, 32, 32, 4);
	enemy9.addComponent<SpriteComponent>("enemy", true);
	enemy9.addComponent<ColliderComponent>("enemy");
	enemy9.addGroup(groupEnemies);

	enemy10.addComponent<TransformComponent>(400, 300, 32, 32, 4);
	enemy10.addComponent<SpriteComponent>("enemy", true);
	enemy10.addComponent<ColliderComponent>("enemy");
	enemy10.addGroup(groupEnemies);

	SDL_Color white = { 255,255,255,255 };
	SDL_Color red = { 255,0,0,0 };
	pScore.addComponent<UILabel>(10, 10, "Score", "arcade", white);
	pHealth.addComponent<UILabel>(10, 50, "Health", "arcade", red);
}

auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& colliders(manager.getGroup(Game::groupColliders));
auto& enemies(manager.getGroup(Game::groupEnemies));

void Game::handleEvents()
{
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

void Game::update()
{
	SDL_Rect playerOldCol = player.getComponent <ColliderComponent>().collider;
	Vector2D playerOldPos = player.getComponent<TransformComponent>().position;
	int tempScore = score;

	std::stringstream sc;
	sc << "Score : " << tempScore;
	pScore.getComponent<UILabel>().setLabelText(sc.str(), "arcade");
	score += .05;

	std::stringstream hp;
	hp << "Health : " << health;
	pHealth.getComponent<UILabel>().setLabelText(hp.str(), "arcade");

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
		if ((playerNewPos.y + playerNewCol.h + 3 >= cCol.y) && !(playerOldPos.y + playerOldCol.h >= cCol.y) && //Bottom-collision
			(playerNewPos.x >= cCol.x) && (playerNewPos.x <= cCol.x + cCol.w)) {
			player.getComponent<TransformComponent>().position.y = playerOldPos.y;
		}
	}

	for (auto& e : enemies) {
		if (Collision::AABB(player.getComponent<ColliderComponent>().collider, e->getComponent<ColliderComponent>().collider)) {
			std::cout << "Hit enemy" << std::endl;
			player.getComponent<TransformComponent>().velocity= player.getComponent<TransformComponent>().velocity * -1;
			e->destroy();
			health -= 30;
		}
		if (player.getComponent<TransformComponent>().position.x > e->getComponent<TransformComponent>().position.x) {
			e->getComponent<TransformComponent>().position.x += 2;
		}
		if(player.getComponent<TransformComponent>().position.x < e->getComponent<TransformComponent>().position.x) {
			e->getComponent<TransformComponent>().position.x -= 2;
		}
		if (player.getComponent<TransformComponent>().position.y > e->getComponent<TransformComponent>().position.y) {
			e->getComponent<TransformComponent>().position.y += 2;
		}
		if (player.getComponent<TransformComponent>().position.y < e->getComponent<TransformComponent>().position.y) {
			e->getComponent<TransformComponent>().position.y -= 2;
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
	for (auto& p : players) {
		p->draw();
	}
	for (auto& e : enemies) {
		e->draw();
	}
	pScore.draw();
	pHealth.draw();
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}
