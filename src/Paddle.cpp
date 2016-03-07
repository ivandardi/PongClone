#include "Paddle.h"

#include "Game.h"
#include "Ball.h"
#include "Util.h"

const int Paddle::WIDTH  {40};
const int Paddle::HEIGHT {Game::height/5};

Paddle::Paddle(float posX)
	: _speed(300)
	, _points(0)
	, _font()
	, _score(std::to_string(_points), _font, 50)
	, _rect({WIDTH, HEIGHT})
	, _clock()
	, isMoving(false)
{
	if (!_font.loadFromFile("assets/mplus-1m-bold.ttf")) {
		throw std::runtime_error("Failed to load font.");
	}

	// Setting the origin of the rectangle on its center
	_rect.setOrigin(WIDTH/2, HEIGHT/2);

	// Setting the actual positions of the paddles
	_rect.setPosition(posX, 0);
	resetY();

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
	if (!isMoving) {
		_clock.restart();
		isMoving = true;
	}

	int padding = 15;
	auto box = _rect.getGlobalBounds();
	float maxY = Game::height - padding;
	float delta = _clock.restart().asSeconds();
	if (box.top + box.height < maxY) {
		_rect.move(0, _speed * multiplier * delta);
	}
}

void Paddle::moveUp(float multiplier)
{
	if (!isMoving) {
		_clock.restart();
		isMoving = true;
	}

	int padding = 15;
	auto box = _rect.getGlobalBounds();
	float minY = 0 + padding;
	float delta = _clock.restart().asSeconds();
	if (box.top > minY) {
		_rect.move(0, -_speed * multiplier * delta);
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

void Paddle::resetY()
{
	_rect.setPosition(_rect.getPosition().x, Game::height/2);
}

void Paddle::AIUpdate(float y)
{
	_predictedBallY = y;
}

void Paddle::AIMove(float x)
{
	// Set up a random region of collision each time
	float topY = _rect.getGlobalBounds().top;
	topY += Util::getRandomInt(0, _rect.getGlobalBounds().height/2);
	float bottomY = topY + _rect.getGlobalBounds().height/2;

	// Paddle only follows ball on the left half of the screen
	if (x < Game::width/2) {
		if (bottomY < _predictedBallY) {
			moveDown();
		} else if (topY > _predictedBallY) {
			moveUp();
		} else {
			isMoving = false;
		}
	} else {
		// Paddles goes to the general middle of the screen
		if (bottomY < Game::height/2) {
			moveDown(0.3);
		} else if (topY > Game::height/2) {
			moveUp(0.3);
		} else {
			isMoving = false;
		}
	}
}

void Paddle::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_rect, states);
	target.draw(_score, states);
}
