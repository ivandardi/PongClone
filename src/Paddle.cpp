#include "Paddle.h"

#include "Game.h"

const int Paddle::WIDTH  {40};
const int Paddle::HEIGHT {Game::height/5};

Paddle::Paddle(float posX, float posY)
	: _score({std::to_string(_points), _font, 50})
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

void Paddle::setY(float newY)
{
	_rect.setPosition(_rect.getPosition().x, newY);
}

void Paddle::increaseY(float incrY)
{
	auto pos = _rect.getPosition();
	pos.y += incrY;

	auto box = _rect.getGlobalBounds();
	int padding = 15;
	if (padding <= box.top && box.top + box.height <= Game::height) {
		_rect.setPosition(pos);
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

void Paddle::updateAI(const Ball& ball)
{
}

void Paddle::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_score);
	target.draw(_rect);
}
