#include "Player.h"

//Funções privadas

void Player::initVariables()
{
	this->attackCooldownMax = 10.f;
	this->attackCooldown = this->attackCooldownMax;
}

void Player::initTexture()
{
	//Carregar textura
	if (!this->texture.loadFromFile("Textures/ship.png"))
		std::cout << "ERROR::PLAYER::INITTEXTURE::Erro ao carregar textura!";
}

void Player::initSprite()
{
	//Adicionar textura à sprite
	this->sprite.setTexture(this->texture);

	//Escalonar a sprite
	this->sprite.scale(0.30f, 0.30f);
}

void Player::isTouchingBorderWindow(MoveSpeeds &speeds)
{
	FloatRect spriteBounds = this->sprite.getGlobalBounds();
	Vector2u windowSize = window.getSize();

	if (spriteBounds.left < 0)
		speeds.left = 0.f;
	else
		speeds.left = 5.f;
	if (spriteBounds.left +spriteBounds.width > windowSize.x)
		speeds.right = 0.f;
	else
		speeds.right = 5.f;
	if (spriteBounds.top < 0)
		speeds.up = 0.f;
	else
		speeds.up = 5.f;
	if (spriteBounds.top  + spriteBounds.height > windowSize.y)
		speeds.down = 0.f;
	else
		speeds.down = 5.f;

}

//Construtor e destrutor
Player::Player(RenderWindow& gameWindow)
	: window(gameWindow)
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
}

Player::~Player()
{
}

const Vector2f& Player::getPos() const
{
	return this->sprite.getPosition();
}

const Vector2f Player::getDimensions() const
{
	FloatRect bounds = sprite.getGlobalBounds();
	return Vector2f(bounds.width, bounds.height);
}

void Player::move(string direction)
{
	if (direction == "Up")
		this->sprite.move(0.f, -(this->speeds.up*1.f));
	if (direction == "Down")
		this->sprite.move(0.f, this->speeds.down * 1.f);
	if (direction == "Left")
		this->sprite.move(-(this->speeds.left * 1.f), 0.f);
	if (direction == "Right")
		this->sprite.move(this->speeds.right * 1.f, 0.f);
}

const bool Player::canAttack()
{
	if (this->attackCooldown >= this->attackCooldownMax) {
		this->attackCooldown = 0.f;
		return true;
	}
	return false;
}

void Player::updateCooldown()
{
	if(this->attackCooldown<this->attackCooldownMax)
	this->attackCooldown += 0.5f;
}

//Funções públicas
void Player::update()
{
	this->isTouchingBorderWindow(speeds);
	this->updateCooldown();
}

void Player::render(RenderTarget& target)
{
	target.draw(this->sprite);
}
