#pragma once
#include<SFML/Graphics.hpp>
using namespace sf;
class Pumpkin
{
	Texture textures[3];
	const int gravity;
	const int flap_speed;
	float velocity_y;
	int anim_counter, texture_switch;
	bool should_fly;
public:
	Sprite pumpkin_sprite;
	Pumpkin();
	void setShouldFly(bool);
	void flapPumpkin(Time&);
	void resetPumpkinPosition();
	void update(Time&);
	float getRightBound();

};