#include<SFML/Graphics.hpp>
#include"dimension.h"
#include"Game.h"
using namespace sf;
int main()
{
	RenderWindow win(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "Flappy Pumpkin");
	Game game(win);
	game.startGameLoop();
	return 0;
}