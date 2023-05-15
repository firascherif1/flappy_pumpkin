#include"Pumpkin.h"
#include"Dimension.h"
Pumpkin::Pumpkin() :
	gravity(10),
	flap_speed(250),
	anim_counter(0),
	texture_switch(1),
	should_fly(false)
{
	textures[0].loadFromFile("assets/1.png"); 
	textures[1].loadFromFile("assets/2.png");
	textures[2].loadFromFile("assets/3.png");

	pumpkin_sprite.setTexture(textures[0]);
	pumpkin_sprite.setScale(SCALE_FACTOR, SCALE_FACTOR);
	resetPumpkinPosition();
}

void Pumpkin::setShouldFly(bool should_fly)
{
	this->should_fly = should_fly;
}

void Pumpkin::flapPumpkin(Time& dt)
{
	velocity_y = -flap_speed * dt.asSeconds();
}

void Pumpkin::resetPumpkinPosition()
{
	pumpkin_sprite.setPosition(100, 50);
	velocity_y = 0;
}

void Pumpkin::update(Time& dt)
{
	if (pumpkin_sprite.getGlobalBounds().top < 548 && should_fly)
	{
		if (anim_counter == 5)
		{
			pumpkin_sprite.setTexture(textures[texture_switch]);
			if (texture_switch == 2) texture_switch = 0;
			else if (texture_switch == 0) texture_switch = 1;
			else texture_switch = 2;
			anim_counter = 0;
		}
		anim_counter++;

		velocity_y += gravity * dt.asSeconds();
		pumpkin_sprite.move(0, velocity_y);

		if (pumpkin_sprite.getGlobalBounds().top < 0)
			pumpkin_sprite.setPosition(100, 0);
	}
}

float Pumpkin::getRightBound()
{
	return pumpkin_sprite.getGlobalBounds().left + pumpkin_sprite.getGlobalBounds().width;
}