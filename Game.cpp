#include "Game.h"


//Funções privadas
void Game::initWindow()
{
	this->window = new RenderWindow(VideoMode::getDesktopMode(), "Third Game" , Style::Fullscreen);
	this->window->setFramerateLimit(60);
	this->window->setVerticalSyncEnabled(false);
}

void Game::initTextures()
{
	this->textures["BULLET"] = new Texture();
	this->textures["BULLET"]->loadFromFile("Textures/bullet.png");

	if (!this->backgroundTexture.loadFromFile("Textures/background1.png"))
		std::cout << "ERROR::GAME::INITTEXTURE::Erro ao carregar textura!";

}

void Game::initPlayer()
{
	this->players.push_back(new Player(*window, 1));
	this->players.push_back(new Player(*window, 2));
}

void Game::initSprite()
{
	this->backgroundSprite.setTexture(this->backgroundTexture);

	 Vector2u windowSize = window->getSize();

	this->backgroundSprite.setScale(
		windowSize.x / this->backgroundSprite.getLocalBounds().width,
		windowSize.y / this->backgroundSprite.getLocalBounds().height
	);
}

void Game::initOverScreen()
{
	this->gameOverScreen = new GameOverScreen(*this->window);
	this->gameOverScreen->initText("Você perdeu");
}

//Construtor e destrutor
Game::Game()
{
	this->initWindow();
	this->initTextures();
	this->initSprite();
	this->initPlayer();
	this->initOverScreen();

	float segundos = 0.f;

}

Game::~Game()
{
	delete this->window;
	
	//Apagar os players
	for (auto& player : this->players) {
		delete player;
	}

	this->players.clear();

	//Apagar as texturas
	for (auto& texture : this->textures) {
		delete texture.second;
	}

	this->textures.clear();

	//Apagar os tiros
	for (auto* bullet : this->bullets) {
		delete bullet;
	}

	this->bullets.clear();

	delete this->gameOverScreen;
}

//Funções públicas
void Game::run()
{

	while (this->window->isOpen()) {
		this->update();

		// Verifique se o jogo acabou
		if (gameOver) {
			this->renderGameOverScreen();
		}
		else {
			this->render();
		}
	}
}

void Game::pollEvents()
{
	Event ev;
	while (this->window->pollEvent(ev) && !gameOver)
	{

		for (auto* player : this->players) {
			if (player->getHealth() <= 0) {
				gameOver = true;
				break;
			}
		}

		if (gameOver) {
			this->initOverScreen();
			this->gameOverScreen->render();
			this->gameOverScreen->render();
			
		}
		if (ev.type == Event::Closed)
			this->window->close();
		if (ev.KeyPressed && ev.key.code == Keyboard::Escape)
			this->window->close();
	}
}

void Game::updateInput()
{

	float bulletPos_Y, bulletPos_X;


	segundos = clock.getElapsedTime().asSeconds();

	if (cooldownNitroPlayer1 > 5 && segundos>1) {
		cooldownNitroPlayer1++;
		clock.restart();
	}

	if (cooldownNitroPlayer2 > 5 && segundos > 1) {
		cooldownNitroPlayer2++;
		clock.restart();
	}

		//Teste de nitro
		if (Keyboard::isKeyPressed(Keyboard::Key::LShift)) {
	
			if (segundos > 1) {
				cooldownNitroPlayer1++;
				clock.restart();
			}
			if(cooldownNitroPlayer1<5)
				this->players[0]->setSpeed(10.f);
			else
				this->players[0]->setSpeed(5.f);
			if (cooldownNitroPlayer1 >15) {
				cooldownNitroPlayer1 = 0;
			}

		}
		else {
			this->players[0]->setSpeed(5.f);
		}

		if (Keyboard::isKeyPressed(Keyboard::Key::RShift)) {
			if (segundos > 1) {
				cooldownNitroPlayer2++;
				clock.restart();
			}
			if (cooldownNitroPlayer2 < 5)
				this->players[1]->setSpeed(10.f);
			else
				this->players[1]->setSpeed(5.f);
			if (cooldownNitroPlayer2 > 15) {
				cooldownNitroPlayer2 = 0;
			}
		}
		else {
			this->players[1]->setSpeed(5.f);
		}

		//Mover player 1 com WASD
		if (Keyboard::isKeyPressed(Keyboard::Key::A))
			this->players[0]->move("Left");
		if (Keyboard::isKeyPressed(Keyboard::Key::D))
			this->players[0]->move("Right");
		if (Keyboard::isKeyPressed(Keyboard::Key::W))
			this->players[0]->move("Up");
		if (Keyboard::isKeyPressed(Keyboard::Key::S))
			this->players[0]->move("Down");

		//Mover player 2 com setas
		if (Keyboard::isKeyPressed(Keyboard::Key::Left))
			this->players[1]->move("Left");
		if (Keyboard::isKeyPressed(Keyboard::Key::Right))
			this->players[1]->move("Right");
		if (Keyboard::isKeyPressed(Keyboard::Key::Up))
			this->players[1]->move("Up");
		if (Keyboard::isKeyPressed(Keyboard::Key::Down))
			this->players[1]->move("Down");

		if (Keyboard::isKeyPressed(Keyboard::Key::Space) && this->players[0]->canAttack()) {
			bulletPos_X = this->players[0]->getPos().x + (this->players[0]->getDimensions().x * 0.4f);
			bulletPos_Y = this->players[0]->getPos().y;
			this->bullets.push_back(new Bullet(this->textures["BULLET"], bulletPos_X, bulletPos_Y, 0.f, -1.f, 10.f, this->players[0]->getRotation(), this->players[0]));
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::Numpad1) && this->players[1]->canAttack()) {
			bulletPos_X = this->players[1]->getPos().x - (this->players[1]->getDimensions().x * 0.62f);
			bulletPos_Y = this->players[1]->getPos().y - (this->players[1]->getDimensions().y * .2f);
			this->bullets.push_back(new Bullet(this->textures["BULLET"], bulletPos_X, bulletPos_Y, 0.f, 1.f, 10.f, this->players[1]->getRotation(), this->players[1]));
		}


	
}

void Game::updateBullets()
{
	unsigned cont = 0;

	for (auto* bullet : this->bullets) {
		bullet->update();

		// Eliminar tiro quando tocar no topo da janela
		if (bullet->getBounds().top + bullet->getBounds().height < 0.f || bullet->getBounds().top > this->window->getSize().y) {
			// Apagar o tiro
			delete this->bullets.at(cont);
			this->bullets.erase(this->bullets.begin() + cont);
			--cont;
		}
		++cont;
	}
}

	void Game::checkCollisionBullets()
	{
		for (auto it = bullets.begin(); it != bullets.end();) {
			Bullet* bullet = *it;

			bool bulletHitPlayer = false;
			for (auto* player : players) {
				if (player != bullet->getShooter() && player->getBounds().intersects(bullet->getBounds())) {
					bulletHitPlayer = true;
					player->takeDamage(1);
					break;
				}
			}

			if (bulletHitPlayer) {
				// Exclui o tiro se atingir um jogador
				delete bullet;
				it = bullets.erase(it);
			}
			else {
				++it;
			}
		}
	}


void Game::update()
{
	
	this->pollEvents();
	this->updateInput();

	for (auto* player : this->players) {
		player->update();
	}

	for (auto* bullet : this->bullets) {
		bullet->update();
	}

	this->checkCollisionBullets();
	this->updateBullets();
}

void Game::render()
{
	//Limpa o frame antigo
	this->window->clear();

	//Renderiza na tela o que for exibido
	this->window->draw(this->backgroundSprite);

	for (auto* player : this->players)
		player->render(*window);

	for (auto* bullet : this->bullets)
		bullet->render(this->window);
	
	//Exibe o novo frame
	this->window->display();
}

void Game::renderGameOverScreen()
{
	// Limpa o frame antigo
		this->window->clear();

	//Renderiza a tela de Game Over
	this->gameOverScreen->render();

	//Exibe o novo frame
	this->window->display();
}


