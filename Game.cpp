#include"Game.h"
#include"Dimension.h"
#include<sstream>
Game::Game(RenderWindow& window) :
	win(window),
	is_enter_pressed(false),
	run_game(true),
	start_monitoring(false),
	grave_counter(71),
	grave_spawn_time(70),
	score(0),
	best_score(0)
{
	win.setFramerateLimit(60);
	bg_texture.loadFromFile("assets/bg.png");
	bg_sprite.setTexture(bg_texture);
	bg_sprite.setScale(SCALE_FACTOR, SCALE_FACTOR);
	bg_sprite.setPosition(-10.f, 0.f);

	ground_texture.loadFromFile("assets/ground.png");
	ground_sprite1.setTexture(ground_texture);
	ground_sprite2.setTexture(ground_texture);

	ground_sprite1.setScale(SCALE_FACTOR, SCALE_FACTOR);
	ground_sprite2.setScale(SCALE_FACTOR, SCALE_FACTOR);

	ground_sprite1.setPosition(0, 578);
	ground_sprite2.setPosition(ground_sprite1.getGlobalBounds().width, 578);

	game_over.loadFromFile("assets/gameover.png");
	game_over_sprite.setTexture(game_over);
	game_over_sprite.setPosition(50.f, 200.f);

	font.loadFromFile("assets/arial.ttf");
	restart_text.setFont(font);
	restart_text.setCharacterSize(48);
	restart_text.setFillColor(Color::Green);
	restart_text.setPosition(150, 650);
	restart_text.setString("Restart Game!!");

	start_text.setFont(font);
	start_text.setCharacterSize(48);
	start_text.setFillColor(Color::Green);
	start_text.setPosition(100, 650);
	start_text.setString("press Enter to start");

	score_text.setFont(font);
	score_text.setCharacterSize(24);
	score_text.setFillColor(Color::Green);
	score_text.setPosition(15, 15);
	score_text.setString("Score: 0");

	best_score_text.setFont(font);
	best_score_text.setCharacterSize(24);
	best_score_text.setFillColor(Color::Red);
	best_score_text.setPosition(430, 15);
	best_score_text.setString("Best Score: 0");

	deadSound.openFromFile("assets/sfx/dead.ogg");
	flapSound.openFromFile("assets/sfx/flap.ogg");
	scoreSound.openFromFile("assets/sfx/score.ogg");
	bgSound.openFromFile("assets/sfx/Song.ogg");
	flapSound.setVolume(20);
	scoreSound.setVolume(50);
	deadSound.setVolume(100);
	bgSound.play();
	bgSound.setVolume(20);
	bgSound.setLoop(true);

	Grave::loadTextures();

}

void Game::doProcessing(Time& dt)
{
	if (is_enter_pressed)
	{
		moveGround(dt);

		if (grave_counter > grave_spawn_time)
		{
			graves.push_back(Grave(dist(rd)));
			grave_counter = 0;
		}
		grave_counter++;

		for (int i = 0; i < graves.size(); i++)
		{
			graves[i].update(dt);
			if (graves[i].getRightBound() < 0)
			{
				graves.erase(graves.begin() + i);
			}
		}

		checkCollisions();
		checkScore();
	}
	pumpkin.update(dt);
}

void Game::startGameLoop()
{
	Clock clock;
	//Game Loop
	while (win.isOpen())
	{
		Time dt = clock.restart();
		Event event;
		//Event Loop
		while (win.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				win.close();
			}
			if (event.type == Event::KeyPressed && run_game)
			{
				if (event.key.code == Keyboard::Enter && !is_enter_pressed)
				{
					is_enter_pressed = true;
					start_text.setString("");
					pumpkin.setShouldFly(true);
				}
				if (event.key.code == Keyboard::Space && is_enter_pressed)
				{
					pumpkin.flapPumpkin(dt);
					flapSound.play();

				}
				flapSound.play();

			}
			if (event.key.code == Keyboard::Enter && !run_game)
				restartGame();
			if (event.type == Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && !run_game)
			{

				if (restart_text.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
				{
					restartGame();
				}

			}
		}

		doProcessing(dt);

		draw();
		//display the win
		win.display();
	}
}

void Game::checkCollisions()
{
	if (graves.size() > 0)
	{
		if (graves[0].sprite_down.getGlobalBounds().intersects(pumpkin.pumpkin_sprite.getGlobalBounds()) ||
			graves[0].sprite_up.getGlobalBounds().intersects(pumpkin.pumpkin_sprite.getGlobalBounds()) ||
			pumpkin.pumpkin_sprite.getGlobalBounds().top >= 540)
		{
			is_enter_pressed = false;
			run_game = false;
			deadSound.play();
			bgSound.stop();
		}
		deadSound.play();
	}
	deadSound.play();
}

void Game::checkScore()
{
	if (graves.size() > 0)
	{
		if (!start_monitoring)
		{
			if (pumpkin.pumpkin_sprite.getGlobalBounds().left > graves[0].sprite_down.getGlobalBounds().left &&
				pumpkin.getRightBound() < graves[0].getRightBound())
			{
				start_monitoring = true;
			}
		}
		else
		{
			if (pumpkin.pumpkin_sprite.getGlobalBounds().left > graves[0].getRightBound())
			{
				score++;
				score_text.setString("Score: " + toString(score));
				start_monitoring = false;
				if (score % 5 == 0)
					scoreSound.play();
			}
			scoreSound.play();
		}
		if (score > best_score)
			best_score = score;
	}
}

void Game::draw()
{
	win.draw(bg_sprite);
	for (Grave& grave : graves)
	{
		win.draw(grave.sprite_down);
		win.draw(grave.sprite_up);
	}
	win.draw(ground_sprite1);
	win.draw(ground_sprite2);
	win.draw(pumpkin.pumpkin_sprite);
	win.draw(start_text);
	win.draw(score_text);
	win.draw(best_score_text);
	if (!run_game)
	{
		win.draw(restart_text);
		win.draw(game_over_sprite);
	}
}

void Game::moveGround(Time& dt)
{
	ground_sprite1.move(-move_speed * dt.asSeconds(), 0.f);
	ground_sprite2.move(-move_speed * dt.asSeconds(), 0.f);

	if (ground_sprite1.getGlobalBounds().left + ground_sprite1.getGlobalBounds().width < 0)
	{
		ground_sprite1.setPosition(ground_sprite2.getGlobalBounds().left + ground_sprite2.getGlobalBounds().width, 578);
	}
	if (ground_sprite2.getGlobalBounds().left + ground_sprite2.getGlobalBounds().width < 0)
	{
		ground_sprite2.setPosition(ground_sprite1.getGlobalBounds().left + ground_sprite1.getGlobalBounds().width, 578);
	}
}

void Game::restartGame()
{
	pumpkin.resetPumpkinPosition();
	pumpkin.setShouldFly(false);
	run_game = true;
	is_enter_pressed = false;
	grave_counter = 71;
	graves.clear();
	score = 0;
	score_text.setString("Score: 0");
	best_score_text.setString("best Score: " + toString(best_score));
	start_text.setString("press Enter to start");
	bgSound.play();
}

std::string Game::toString(int num)
{
	std::stringstream ss;
	ss << num;
	return ss.str();
}