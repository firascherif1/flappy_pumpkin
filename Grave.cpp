#include"Grave.h"
#include"Dimension.h"

Texture Grave::texture_down, Grave::texture_up;
int Grave::grave_distance = 170, Grave::move_speed = 400;

Grave::Grave(int y_pos)
{
	sprite_down.setTexture(texture_down);
	sprite_up.setTexture(texture_up);

	sprite_down.setScale(SCALE_FACTOR, SCALE_FACTOR);
	sprite_up.setScale(SCALE_FACTOR, SCALE_FACTOR);

	sprite_up.setPosition(WIN_WIDTH, y_pos);
	sprite_down.setPosition(WIN_WIDTH, y_pos - grave_distance - sprite_up.getGlobalBounds().height);
}

void Grave::loadTextures()
{
	texture_down.loadFromFile("assets/gravedown.png");
	texture_up.loadFromFile("assets/grave.png");
}

void Grave::update(Time& dt)
{
	sprite_up.move(-move_speed * dt.asSeconds(), 0.f);
	sprite_down.move(-move_speed * dt.asSeconds(), 0.f);
}
float Grave::getRightBound()
{
	return sprite_down.getGlobalBounds().left + sprite_down.getGlobalBounds().width;
}