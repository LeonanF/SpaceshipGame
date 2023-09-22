#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

using namespace sf;
using namespace std;

struct MoveTesters {
	float up = 5.f;
	float down = 5.f;
	float right = 5.f;
	float left = 5.f;
};

class Player
{
private:

	Texture texture;
	Texture nitroTexture;
	RenderWindow& window;

	float attackCooldown;
	float attackCooldownMax;
	float playerRotation;
	int numberPlayer;
	int health;
	float moveSpeed;
	MoveTesters testers;

	//Funções privadas
	void initVariables();
	void initTexture();
	void initSprite();
	void isTouchingBorderWindow();

public:
	Player(RenderWindow& gameWindow, int numberPlayer);
	virtual ~Player();


	Sprite sprite;
	Sprite nitroFlame;

	//Getters
	const Vector2f& getPos() const;
	const Vector2f getDimensions() const;
	const FloatRect getBounds() const;
	float getRotation();
	int getHealth();


	//Setter
	void takeDamage(int damage);
	void setSpeed(float newSpeed);

	//Funções públicas
	void move(string direction);
	const bool canAttack();

	void updateCooldown();
	void update();
	void render(RenderTarget& target);
};

