#include "Ball.h"

#include "Game.h"
#include "Paddle.h"

#include <iostream>
#include <chrono>

#define TORAD(x) ((x)*3.14159265/180.0)

Ball::Ball()
	: _rgn(std::chrono::high_resolution_clock::now().time_since_epoch().count())
	, _square({_radius, _radius})
	, _velocity()
	, _clock()
{
	_square.setOrigin(_radius/2, _radius/2);
	restart();
}

void Ball::restart(void)
{
	std::bernoulli_distribution bern;
	auto signal = [&](){ return (bern(_rgn) ? 1 : -1); };

	std::uniform_int_distribution<int> launchAngle(10, 40);
	float angle = TORAD(launchAngle(_rgn));
	_velocity = sf::Vector2f(std::cos(angle) * signal(), std::sin(angle) * signal()) * _speed ;

	std::uniform_int_distribution<int> startingY((Game::height + 1)/4, (Game::height + 1)*3/4);
	_square.setPosition((Game::width + 1)/2, startingY(_rgn));

	launched = false;
}

void Ball::launch(void)
{
	launched = true;
}

// TODO: Implement proper boucing off
bool Ball::collidesWithPaddle(const sf::RectangleShape& paddle)
{
	if (_square.getGlobalBounds().intersects(paddle.getGlobalBounds())) {
		auto paddleOrigin = paddle.getOrigin();
		auto ballOrigin = _square.getOrigin();
        float m = (paddleOrigin.y - ballOrigin.y)/(paddleOrigin.x - ballOrigin.x);
		std::cout << m << '\n';

        _velocity.x *= -1;
		return true;
	}
	return false;
}

void Ball::collideswithWall(void)
{
	auto box = _square.getGlobalBounds();
	if (0 >= box.top || box.top + box.height >= Game::height) {
		_velocity.y *= -1;
	}
}

void Ball::updatePosition(void)
{
	_square.move(_velocity);
}

int Ball::predictY(void) const
{
	float m = _velocity.y/_velocity.x;
	int predictedY = std::abs(m * -_square.getPosition().x + _square.getPosition().y);
	int reflections = predictedY / Game::height;
	predictedY = (reflections % 2 == 0 ? predictedY % Game::height : Game::height - (predictedY % Game::height));
	return predictedY;
}

float Ball::getX(void) const
{
	return _square.getPosition().x;
}

Edge::Side Ball::isOffscreen(void) const
{
	auto pos = _square.getPosition();
	if (pos.x + _radius/2 < 0) {
		return Edge::Left;
	}
	if (pos.x - _radius/2 > Game::width) {
		return Edge::Right;
	}
	return Edge::None;
}

void Ball::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_square, states);
}

