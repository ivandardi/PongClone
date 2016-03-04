#include "Paddle.h"

#include "Game.h"
#include "Ball.h"

const int Paddle::WIDTH  {40};
const int Paddle::HEIGHT {Game::height/5};

Paddle::Paddle(float posX, float posY)
	: _points(0)
	, _font()
	, _score(std::to_string(_points), _font, 50)
	, _rect({WIDTH, HEIGHT})
{
	if (!_font.loadFromFile("assets/mplus-1m-bold.ttf")) {
		throw std::runtime_error("Failed to load font.");
	}

	// Setting the origin of the rectangle on its center
	_rect.setOrigin(WIDTH/2, HEIGHT/2);

	// Setting the actual positions of the paddles
	_rect.setPosition(posX, posY);

	// Setting the score position
	constexpr float halfScreen = (Game::width + 1)/2;
	if (posX < halfScreen) {
		_score.setPosition(halfScreen - _score.getGlobalBounds().width - 80, 50);
	} else {
		_score.setPosition(halfScreen + 80, 50);
	}
}

void Paddle::moveDown(float multiplier)
{
	int padding = 15;
	auto box = _rect.getGlobalBounds();
	float maxY = Game::height - padding;
	if (box.top + box.height < maxY) {
		_rect.move(0, _speed * multiplier);
	}
}

void Paddle::moveUp(float multiplier)
{
	int padding = 15;
	auto box = _rect.getGlobalBounds();
	float minY = 0 + padding;
	if (box.top > minY) {
		_rect.move(0, -_speed * multiplier);
	}
}

void Paddle::increaseScore(void)
{
	_score.setString(std::to_string(++_points));
}

int Paddle::getScore(void) const
{
	return _points;
}

void Paddle::AIUpdate(float y)
{
	_predictedBallY = y;
}

// TODO: Fix jitter
void Paddle::AIMove(float x)
{
	int rectY = _rect.getPosition().y;
	// Paddle only follows ball on the left half of the screen
	if (x < Game::width/2 + 1) {
		if (_predictedBallY > rectY) {
			moveDown(.75);
		} else if (_predictedBallY < rectY) {
			moveUp(.75);
		}
	} else {
		// Paddles goes to the middle of the screen
		if (rectY < Game::height/2) {
			moveDown(0.25);
		} else if (rectY > Game::height/2) {
			moveUp(0.25);
		}
	}
}

void Paddle::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_rect, states);
	target.draw(_score, states);
}
