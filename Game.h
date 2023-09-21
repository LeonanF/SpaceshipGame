#pragma once

#include <map>
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"

class Game
{
private:

	//Janela
	RenderWindow* window;
	
	//Recursos
	std::map<std::string, Texture*> textures;
	std::vector<Bullet*> bullets;
	Texture backgroundTexture;
	Sprite backgroundSprite;

	//Adicionar Player
	Player* player;

	//Adicionar Enemy
	Enemy* enemy;

	//Funções privadas
	void initWindow();
	void initTextures();
	void initPlayer();
	void initEnemy();
	void initSprite();

public:
	Game();
	virtual ~Game();

	//Funções públicas
	void run();

	void pollEvents();
	void updateInput();
	void updateBullets();
	void update();
	void render();
};