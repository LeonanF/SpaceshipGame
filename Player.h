#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

using namespace sf;
using namespace std;

struct MoveSpeeds {
	float up = 5.f;
	float down = 5.f;
	float right = 5.f;
	float left = 5.f;
};

class Player
{
private:

	Sprite sprite;
	Texture texture;
	RenderWindow& window;

	float attackCooldown;
	float attackCooldownMax;
	MoveSpeeds speeds;

	//Funções privadas
	void initVariables();
	void initTexture();
	void initSprite();
	void isTouchingBorderWindow(MoveSpeeds& speeds);

public:
	Player(RenderWindow& gameWindow);
	virtual ~Player();

	//Getters
	const Vector2f& getPos() const;
	const Vector2f getDimensions() const;

	//Funções públicas
	void move(string direction);
	const bool canAttack();

	void updateCooldown();
	void update();
	void render(RenderTarget& target);
};

