#include "GameOverScreen.h"

GameOverScreen::GameOverScreen(RenderWindow& gameWindow)
	:window(gameWindow)
{
	if (!font.loadFromFile("Fonts/Montserrat-VariableFont_wght.ttf"))
		cout << "ERROR::GAMEOVERSCREEN::Não foi possível carregar a fonte.";

	gameOverText.setFont(this->font);
	gameOverText.setCharacterSize(48);
	gameOverText.setFillColor(Color::Red);

	FloatRect textBounds = gameOverText.getLocalBounds();
	gameOverText.setPosition((gameWindow.getSize().x - textBounds.width)/2.2f, (gameWindow.getSize().y - textBounds.height) / 2.f);

}

GameOverScreen::~GameOverScreen()
{
	delete &this->window;
}


void GameOverScreen::initText(String message)
{
	this->gameOverText.setFont(this->font);
	this->gameOverText.setCharacterSize(18);
	this->gameOverText.setStyle(sf::Text::Bold);
	this->gameOverText.setString(message);
}

void GameOverScreen::render()
{
	this->window.clear();

	this->window.draw(this->gameOverText);

	this->window.display();
	
	if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
		this->window.close();

}
