#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<vector>
#include<random>
#include"Pumpkin.h"
#include"Grave.h"
using namespace sf;
class Game
{
	Texture bg_texture, ground_texture, game_over;
	Sprite bg_sprite, ground_sprite1, ground_sprite2, game_over_sprite;
	Pumpkin pumpkin;
	bool is_enter_pressed, run_game, start_monitoring;
	const int move_speed = 270;
	void draw();
	void moveGround(Time&);
	void doProcessing(Time& dt);
	void checkCollisions();
	void restartGame();
	void checkScore();
	std::string toString(int);
	int grave_counter, grave_spawn_time, score, best_score;
	std::vector<Grave> graves;
	std::random_device rd;
	std::uniform_int_distribution<int> dist{ 250,550 };
	Font font;
	Text restart_text, score_text, start_text,best_score_text;
	Music deadSound, flapSound, scoreSound, bgSound;
public:
	Game(RenderWindow&);
	RenderWindow& win;
	void startGameLoop();
};