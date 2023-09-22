#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "Player.h"

using namespace sf;
using namespace std;

class Bullet
{
private:

	Sprite shape;
	
	Vector2f direction;
	float speedBullet;
	float rotation;
	Player* shooter;

public:

	Bullet(Texture* texture, float pos_X, float pos_Y, float dir_X, float dir_Y, float move_Speed, float playerRotation, Player* player);
	virtual ~Bullet();


	//Getters
	const FloatRect getBounds() const;

	//Funções públicas
	Player* getShooter();
	void update();
	void render(RenderTarget* target);

};

