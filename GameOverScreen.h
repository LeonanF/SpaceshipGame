#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

using namespace sf;
using namespace std;

class GameOverScreen
{

private:
	RenderWindow& window;
	Font font;
	Text gameOverText;
public:
	GameOverScreen(RenderWindow& gameWindow);
	virtual ~GameOverScreen();

	//Funções públicas
	void initText(String message);
	void render();

};

