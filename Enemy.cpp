#include "Enemy.h"

//Funções privadas
void Enemy::initVariables() {

}

void Enemy::initTexture() {

	if (!this->texture.loadFromFile("Textures/enemy.png"))
		cout << "ERROR::ENEMY::INITTEXTURE::Erro ao carregar textura!";
}

void Enemy::initSprite() {
	//Adicionar textura à sprite
	this->sprite.setTexture(this->texture);

	//Escalonar a sprite
	this->sprite.scale(0.30f, 0.30f);
}

Enemy::Enemy()
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
}

Enemy::~Enemy()
{
}

void Enemy::update()
{
}

void Enemy::render(RenderTarget& target)
{
	target.draw(this->sprite);
}
