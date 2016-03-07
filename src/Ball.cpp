#include "Ball.h"

#include "Game.h"
#include "Paddle.h"
#include "Util.h"

#include <iostream>

#define PI 3.14159265
#define TORAD(x) ((x)*PI/180.0)

#define MINANG TORAD(15)
#define MAXANG TORAD(35)

Ball::Ball()
	: _radius(25)
	, _speed(500)
	, _hits(0)
	, _square({_radius, _radius})
	, _velocity()
	, _clock()
{
	_square.setOrigin(_radius/2, _radius/2);
	restart();
}

void Ball::restart(void)
{
	float angle = Util::getRandomFloat(MINANG, MAXANG);
	_velocity = sf::Vector2f(std::cos(angle) * Util::getRandomSignal(), std::sin(angle) * Util::getRandomSignal()) * _speed;

	_square.setPosition(Game::width/2, Util::getRandomFloat(Game::height/4.0, Game::height*3/4.0));

	launched = false;
}

void Ball::launch(void)
{
	launched = true;
	_clock.restart();
}

// TODO: Fix bounce angle
bool Ball::collidesWithPaddle(const sf::RectangleShape& paddle)
{
	sf::FloatRect paddleBounds {paddle.getGlobalBounds()};
	sf::FloatRect ballBounds  {_square.getGlobalBounds()};

	if (!paddleBounds.intersects(ballBounds)) {
		return false;
	}

	sf::Vector2f paddleOrigin((paddleBounds.left + paddleBounds.width)/2, (paddleBounds.top + paddleBounds.height)/2);
	sf::Vector2f ballOrigin((ballBounds.left + ballBounds.width)/2, (ballBounds.top + ballBounds.height)/2);

	// Creating the new velocity
	sf::Vector2f newVelocity(ballOrigin.x - paddleOrigin.x, ballOrigin.y - paddleOrigin.y);

	// Setting the angle between 10 and 40 degrees
	if (newVelocity.x > 0) {
		// East quadrant
		if (newVelocity.y > 0) {
			// South quadrant
			newVelocity.y = std::max(newVelocity.y, static_cast<float>(std::tan(MINANG)) * newVelocity.x);
			newVelocity.y = std::min(newVelocity.y, static_cast<float>(std::tan(MAXANG)) * newVelocity.x);
		} else {
			// North quadrant
			newVelocity.y = std::min(newVelocity.y, static_cast<float>(std::tan(-MINANG)) * newVelocity.x);
			newVelocity.y = std::max(newVelocity.y, static_cast<float>(std::tan(-MAXANG)) * newVelocity.x);
		}
	} else {
		// West quadrant
		if (newVelocity.y > 0) {
			// South quadrant
			newVelocity.y = std::max(newVelocity.y, static_cast<float>(std::tan(PI - MINANG)) * newVelocity.x);
			newVelocity.y = std::min(newVelocity.y, static_cast<float>(std::tan(PI - MAXANG)) * newVelocity.x);
		} else {
			// North quadrant
			newVelocity.y = std::min(newVelocity.y, static_cast<float>(std::tan(PI + MINANG)) * newVelocity.x);
			newVelocity.y = std::max(newVelocity.y, static_cast<float>(std::tan(PI + MAXANG)) * newVelocity.x);
		}
	}

	// Making it with size one by dividing it by its modulus
	newVelocity /= static_cast<float>(std::sqrt(std::pow(newVelocity.x, 2) + std::pow(newVelocity.y, 2)));

	// Now that the vector has size one, multiply it with the speed
	newVelocity *= _speed;

	// Set the new velocity
	_velocity = newVelocity;

	// For every 5 hits, make the ball go a little bit faster
	++_hits;
	if (_hits == 5) {
		_velocity *= 1.1f;
		_hits = 0;
		//std::cout << "Increased velocity: (" << _velocity.x << "," << _velocity.y << ")\n";
	}
	return true;
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
	float delta = _clock.restart().asSeconds();
	_square.move(_velocity * delta);
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

Side Ball::isOffscreen(void) const
{
	auto pos = _square.getGlobalBounds();
	if (pos.left + pos.width < 0) {
		return Side::Left;
	}
	if (pos.left > Game::width) {
		return Side::Right;
	}
	return Side::None;
}

void Ball::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_square, states);
}

