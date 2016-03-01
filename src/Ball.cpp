#include "Ball.h"

#include "Game.h"
#include "Paddle.h"

#include <iostream>

Ball::Ball()
	: _square({_radius, _radius})
{
	_square.setOrigin(_radius/2, _radius/2);
	restart();
}

void Ball::restart(void)
{
	_velocity = sf::Vector2f(0, 0);
	_square.setPosition((Game::width + 1)/2, (Game::height + 1)/2);
}

void Ball::launch(void)
{
	std::uniform_real_distribution<float> dist(-35, 35);
	std::bernoulli_distribution bern;
	float speed = 800;
	//float angle = dist(rgn);
	float angle = 1.0;
	if (bern(rgn)) {
		angle += 180;
	}
	_velocity = sf::Vector2f(std::cos(angle), std::sin(angle)) * speed;
	std::cerr << std::cos(angle) << ":" << std::sin(angle) << "\n";
}

void Ball::collidesWithPaddle(const Paddle& paddle)
{
	if (_square.getGlobalBounds().intersects(paddle.getBounds())) {
		_velocity.x *= -1;
	}
}

void Ball::collideswithWall(void)
{
	auto box = _square.getGlobalBounds();
	if (0 <= box.top || box.top + box.height >= Game::height) {
		_velocity.y *= -1;
	}
}

void Ball::updatePosition(void)
{
	_square.move(_velocity);
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

