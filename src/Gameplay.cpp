#include "Gameplay.h"
#include "MainMenu.h"
#include "Game.h"

#include <iostream>

Gameplay::Gameplay()
	: _font()
	, _player(Game::width - 40)
	, _computer(40)
	, _ball()
	, _divisor(Direction::Vertical, Game::width/2, 31)
{
	if (!_font.loadFromFile("assets/mplus-1m-bold.ttf")) {
		throw std::runtime_error("Failed to load font.");
	}
}

void Gameplay::input(void)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		_player.moveUp();
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		_player.moveDown();
	} else {
		_player.isMoving = false;
	}

	if (!_ball.launched) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			_ball.launch();
			_computer.AIUpdate(_ball.predictY());
		}
	}
}

void Gameplay::update(void)
{
	// Check to see if someone won
	if (_winner != -1) {
		_gameview.reset(new MainMenu);
		return;
	}
	constexpr int maxScore = 10;
	if (_player.getScore() == maxScore) {
		_winner = 0;
	} else if (_computer.getScore() == maxScore) {
		_winner = 1;
	}

	if (!_ball.launched) {
		return;
	}

	_computer.AIMove(_ball.getX());

	if (_ball.collidesWithPaddle(_player.getPaddle())) {
		_computer.AIUpdate(_ball.predictY());
	} else {
		_ball.collidesWithPaddle(_computer.getPaddle());
	}
	_ball.collideswithWall();

	_ball.updatePosition();

	// Checks to see if a new round should begin
	if (_ball.isOffscreen() != Edge::None) {
		_ball.isOffscreen() == Edge::Left ? _player.increaseScore() : _computer.increaseScore();
		_ball.restart();
		_player.resetY();
		_computer.resetY();
	}
}

void Gameplay::render(void)
{
	_window.clear();

	_window.draw(_divisor);

	_window.draw(_player);
	_window.draw(_computer);

	if (_winner == 0) {
		// If player won
		sf::Text winner("You won!", _font, 75);
		winner.setOrigin(winner.getGlobalBounds().width/2, 0);
		winner.setPosition((Game::width + 1)*3/4, (Game::height + 1)/4 - winner.getGlobalBounds().height);
		_window.draw(winner);
	} else if (_winner == 1) {
		// If computer won
		sf::Text winner("You lost!", _font, 70);
		winner.setOrigin(winner.getGlobalBounds().width/2, 0);
		winner.setPosition((Game::width + 1)/4, (Game::height + 1)/4 - winner.getGlobalBounds().height);
		_window.draw(winner);
	} else {
		// If nobody won yet
		_window.draw(_ball);
	}

	_window.display();

	// If someone wins, let the winning text stay onscreen for 5 seconds
	if (_winner != -1) {
		sf::sleep(sf::seconds(5));
	}
}

