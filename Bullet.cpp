#include "Bullet.h"

Bullet::Bullet(Texture* texture, float pos_X, float pos_Y, float dir_X, float dir_Y, float move_Speed)
{
	this->shape.setTexture(*texture);

	this->shape.setPosition(pos_X, pos_Y);
	this->direction.x = dir_X;
	this->direction.y = dir_Y;
	this->moveSpeed = move_Speed;
}

Bullet::~Bullet()
{
}

void Bullet::update()
{
	//Mover
	this->shape.move(this->moveSpeed * this->direction);
}

const FloatRect Bullet::getBounds() const
{
	return this->shape.getGlobalBounds();
}

void Bullet::render(RenderTarget* target)
{
	target->draw(this->shape);
}
