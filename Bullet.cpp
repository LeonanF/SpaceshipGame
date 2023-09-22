#include "Bullet.h"


Bullet::Bullet(Texture* texture, float pos_X, float pos_Y, float dir_X, float dir_Y, float move_Speed, float playerRotation, Player* player)
{
	this->shape.setTexture(*texture);

	this->shape.setPosition(pos_X, pos_Y);
	this->direction.x = dir_X;
	this->direction.y = dir_Y;
	this->speedBullet = move_Speed;
	this->rotation = playerRotation;
	this->shooter = player;

}

Bullet::~Bullet()
{
}


void Bullet::update()
{
	//Mover
	this->shape.move(this->speedBullet * this->direction);
}

const FloatRect Bullet::getBounds() const
{
	return this->shape.getGlobalBounds();
}

void Bullet::render(RenderTarget* target)
{
	target->draw(this->shape);
}

Player* Bullet::getShooter()
{
	return this->shooter;
}
