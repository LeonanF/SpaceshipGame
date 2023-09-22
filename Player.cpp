#include "Player.h"

//Funções privadas

void Player::initVariables()
{
	this->health = 5;
	this->moveSpeed = 5.f;

	this->attackCooldownMax = 30.f;
	this->attackCooldown = this->attackCooldownMax;



}

void Player::initTexture()
{
	//Carregar textura
	if (!this->texture.loadFromFile("Textures/ship.png"))
		std::cout << "ERROR::PLAYER::INITTEXTURE::Erro ao carregar textura!";

	if (!this->nitroTexture.loadFromFile("Textures/flame.png"))
		std::cout << "ERROR::PLAYER::INITTEXTURE::Erro ao carregar textura!";

}

void Player::initSprite()
{
	
	//Adicionar textura à sprite
	this->sprite.setTexture(this->texture);
	this->nitroFlame.setTexture(this->nitroTexture);

	//Escalonar a sprite
	this->sprite.scale(0.30f, 0.30f);


	Vector2u gameWindow = window.getSize();

	Vector2f playerSize = this->getDimensions();

	if (numberPlayer == 1) {
		this->sprite.setPosition((gameWindow.x / 2) - (playerSize.x / 2), gameWindow.y - playerSize.y);
		this->playerRotation = 0.f;
		this->nitroFlame.rotate(180);
	}
	if (numberPlayer == 2) {
		this->sprite.setPosition((gameWindow.x / 2) + (playerSize.x / 2), 0+playerSize.y);
		this->playerRotation = 180.f;
		this->sprite.rotate(this->playerRotation);
	}


	this->nitroFlame.setScale(0.2f, 0.2f);
	
}

void Player::isTouchingBorderWindow()
{
	FloatRect spriteBounds = this->sprite.getGlobalBounds();
	Vector2u windowSize = window.getSize();

	if (spriteBounds.left < 0)
		this->testers.left = 0.f;
	else
		this->testers.left = 1.f;

	if (spriteBounds.left + spriteBounds.width > windowSize.x)
		this->testers.right = 0.f;
	else
		this->testers.right = 1.f;

	if (spriteBounds.top < 0)
		this->testers.up = 0.f;
	else
		this->testers.up = 1.f;

	if (spriteBounds.top  + spriteBounds.height >windowSize.y)
		this->testers.down = 0.f;
	else
		this->testers.down = 1.f;

}

//Construtor e destrutor
Player::Player(RenderWindow& gameWindow, int numberSelector)
	: window(gameWindow),
	numberPlayer(numberSelector)
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

const FloatRect Player::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

float Player::getRotation()
{
	return this->playerRotation;
}

int Player::getHealth()
{
	return this->health;
}

void Player::takeDamage(int damage)
{
	this->health -= damage;
}

void Player::setSpeed(float newSpeed)
{
	this->moveSpeed = newSpeed;
}

void Player::move(string direction)
{
	if (direction == "Up")
		this->sprite.move(0.f, -(this->moveSpeed*1.f* this->testers.up));
	if (direction == "Down")
		this->sprite.move(0.f, this->moveSpeed * 1.f* this->testers.down);
	if (direction == "Left")
		this->sprite.move(-(moveSpeed * 1.f*this->testers.left), 0.f);
	if (direction == "Right")
		this->sprite.move(this->moveSpeed * 1.f*this->testers.right, 0.f);
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
	this->isTouchingBorderWindow();
	this->updateCooldown();

	if(numberPlayer==1)
		this->nitroFlame.setPosition(this->sprite.getPosition().x+(this->sprite.getGlobalBounds().width*0.84f), this->sprite.getPosition().y + (this->sprite.getGlobalBounds().height*1.5f));

	if(numberPlayer==2)
		this->nitroFlame.setPosition(this->sprite.getPosition().x - (this->sprite.getGlobalBounds().width*0.84f), this->sprite.getPosition().y - (this->sprite.getGlobalBounds().height*1.5f));

}

void Player::render(RenderTarget& target)
{
	target.draw(this->sprite);
	if(moveSpeed==10.f)
	target.draw(this->nitroFlame);
}
