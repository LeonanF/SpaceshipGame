#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

using namespace std;
using namespace sf;

class Enemy
{
private:
	Sprite sprite;
	Texture texture;

	//Funções privadas
	void initVariables();
	void initTexture();
	void initSprite();
public:
	
	//Construtor e destrutor
	Enemy();
	virtual ~Enemy();

	//Funções públicas
	void update();
	void render(RenderTarget& target);

};

