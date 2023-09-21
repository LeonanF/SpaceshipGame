#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

using namespace sf;

class Bullet
{
private:

	Sprite shape;
	
	Vector2f direction;
	float moveSpeed;

public:

	Bullet(Texture* texture, float pos_X, float pos_Y, float dir_X, float dir_Y, float move_Speed);
	virtual ~Bullet();

	//Getters
	const FloatRect getBounds() const;

	//Funções públicas
	void update();
	void render(RenderTarget* target);

};

