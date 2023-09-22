#pragma once

#include <map>
#include "Player.h"
#include "Bullet.h"
#include "GameOverScreen.h"

class Game
{
private:

	//Janela
	RenderWindow* window;
	
	Clock clock;
	float segundos;
	int cooldownNitroPlayer1;
	int cooldownNitroPlayer2;

	//Recursos
	bool gameOver=false;
	map<std::string, Texture*> textures;
	vector<Bullet*> bullets;
	GameOverScreen* gameOverScreen;
	Texture backgroundTexture;
	Sprite backgroundSprite;

	//Adicionar Player
	vector<Player*> players;

	//Funções privadas
	void initWindow();
	void initTextures();
	void initPlayer();
	void initSprite();
	void initOverScreen();

public:
	Game();
	virtual ~Game();

	//Funções públicas
	void run();

	void pollEvents();
	void updateInput();
	void updateBullets();
	void checkCollisionBullets();
	void update();
	void render();
	void renderGameOverScreen();
};