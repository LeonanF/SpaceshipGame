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
	this->player = new Player(*window);
}

void Game::initEnemy() {
	this->enemy = new Enemy();
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

//Construtor e destrutor
Game::Game()
{
	this->initWindow();
	this->initTextures();
	this->initSprite();
	this->initPlayer();
	this->initEnemy();
}

Game::~Game()
{
	delete this->window;
	delete this->player;
	delete this->enemy;

	//Apagar as texturas
	for (auto& i : this->textures) {
		delete i.second;
	}

	//Apagar os tiros
	for (auto* i : this->bullets) {
		delete i;
	}

}

//Funções públicas
void Game::run()
{
	while (this->window->isOpen()) {
		this->update();
		this->render();
	}
}

void Game::pollEvents()
{
	Event ev;
	while (this->window->pollEvent(ev))
	{
		if (ev.type == Event::Closed)
			this->window->close();
		if (ev.KeyPressed && ev.key.code == Keyboard::Escape)
			this->window->close();
	}
}

void Game::updateInput()
{

	//Mover player
	if (Keyboard::isKeyPressed(Keyboard::Key::A) || Keyboard::isKeyPressed(Keyboard::Key::Left))
		this->player->move("Left");
	if (Keyboard::isKeyPressed(Keyboard::Key::D) || Keyboard::isKeyPressed(Keyboard::Key::Right))
		this->player->move("Right");
	if (Keyboard::isKeyPressed(Keyboard::Key::W) || Keyboard::isKeyPressed(Keyboard::Key::Up))
		this->player->move("Up");
	if (Keyboard::isKeyPressed(Keyboard::Key::S) || Keyboard::isKeyPressed(Keyboard::Key::Down))
		this->player->move("Down");

	if (Mouse::isButtonPressed(Mouse::Left) && this->player->canAttack())
		this->bullets.push_back(new Bullet(this->textures["BULLET"], (this->player->getPos().x)-(this->player->getDimensions().x*0.06f), this->player->getPos().y-this->player->getDimensions().y, 0.f, -1.f, 7.f));
}

void Game::updateBullets()
{
	unsigned cont = 0;

	for (auto* bullet : this->bullets) {
		bullet->update();
		
		//Eliminar tiro quando tocar no topo da janela
		if (bullet->getBounds().top + bullet->getBounds().height < 0.f) {
			//Apagar o tiro
			delete this->bullets.at(cont);
			this->bullets.erase(this->bullets.begin()+cont);
			--cont;
		}
			++cont;
	}
}

void Game::update()
{
	
	this->pollEvents();
	this->updateInput();
	this->player->update();
	this->enemy->update();
	this->updateBullets();
}

void Game::render()
{
	//Limpa o frame antigo
	this->window->clear();

	//Renderiza na tela o que for exibido
	this->window->draw(this->backgroundSprite);
	this->enemy->render(*this->window);
	this->player->render(*this->window);

	for (auto* bullet : this->bullets) {
		bullet->render(this->window);
	}

	//Exibe o novo frame
	this->window->display();
}
