#include "Gameplay.h"
#include "MainMenu.h"
#include "Game.h"

Gameplay::Gameplay()
	: _player({Game::width - 40, (Game::height+1)/2})
	, _computer({40, (Game::height+1)/2})
{
	if (!_font.loadFromFile("assets/mplus-1m-bold.ttf")) {
		throw std::runtime_error("Failed to load font.");
	}

	// Creates the screen separator
	float halfScreen = (Game::width + 1)/2;
	for (auto& elem : _divisor) {
		elem = sf::VertexArray(sf::Lines, 2);
	}
	for (size_t i = 0; i < _divisor.size(); ++i) {
		_divisor[i][0] = sf::Vertex(sf::Vector2f(halfScreen, (Game::height*i)/_divisor.size()), ((i % 2 == 0) ? sf::Color::White : sf::Color::Black));
		_divisor[i][1] = sf::Vertex(sf::Vector2f(halfScreen, (Game::height*(i + 1))/_divisor.size()), ((i % 2 == 0) ? sf::Color::White : sf::Color::Black));
	}
}

void Gameplay::input(void)
{
	float playerSpeed = 10;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		_player.increaseY(-playerSpeed);
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		_player.increaseY(playerSpeed);
	}
}

void Gameplay::update(void)
{
	_computer.updateAI(_ball);

	if (_ball.readyToLaunch) {
		_ball.readyToLaunch = false;
		_ball.launch();
	}

	_ball.collidesWithPaddle(_player);
	_ball.collidesWithPaddle(_computer);
	_ball.collideswithWall();

	_ball.updatePosition();

	// Checks to see if a new round should begin
	if (_ball.isOffscreen() != Edge::None) {
		_ball.isOffscreen() == Edge::Left ? _player.increaseScore() : _computer.increaseScore();
		_player.setY(Game::height/2 + 1);
		_computer.setY(Game::height/2 + 1);
		_ball.restart();
		_ball.readyToLaunch = true;
	}

	// Check to see if someone won
	if (_winner != -1) {
		_gameview.reset(new MainMenu);
	}
	const int maxScore = 2;
	if (_player.getScore() == maxScore) {
		_winner = 0;
	} else if (_computer.getScore() == maxScore) {
		_winner = 1;
	}
}

void Gameplay::render(void)
{
	_window.clear();

	// TODO: DashedLine.draw
	for (auto& elem : _divisor) {
		_window.draw(elem);
	}

	_window.draw(_player);
	_window.draw(_computer);

	if (_winner == 0) { // If player won
		sf::Text winner("You won!", _font, 75);
		winner.setOrigin(winner.getGlobalBounds().width/2, 0);
		winner.setPosition((Game::width + 1)*3/4, (Game::height + 1)/4 - winner.getGlobalBounds().height);
		_window.draw(winner);
	} else if (_winner == 1) { // If computer won
		sf::Text winner("You lost!", _font, 70);
		winner.setOrigin(winner.getGlobalBounds().width/2, 0);
		winner.setPosition((Game::width + 1)/4, (Game::height + 1)/4 - winner.getGlobalBounds().height);
		_window.draw(winner);
	} else { // If nobody won yet
		_window.draw(_ball);
	}

	_window.display();

	// If someone wins, let the winning text stay onscreen for 5 seconds
	if (_winner != -1) {
		sf::sleep(sf::seconds(5));
	}
}

