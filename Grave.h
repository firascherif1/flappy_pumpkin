#pragma once
#include<SFML/Graphics.hpp>
using namespace sf;
class Grave
{
	static Texture texture_down, texture_up;
	static int grave_distance, move_speed;
public:
	Grave(int);
	Sprite sprite_up, sprite_down;
	static void loadTextures();
	void update(Time&);
	float getRightBound();
};