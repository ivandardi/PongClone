#include "Ball.h"

#include "Game.h"
#include "Paddle.h"
#include "Util.h"

#include <iostream>

#define TORAD(x) ((x)*3.14159265/180.0)

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
	float angle = TORAD(Util::getRandomInt(10, 40));
	_velocity = sf::Vector2f(std::cos(angle) * Util::getRandomSignal(), std::sin(angle) * Util::getRandomSignal()) * _speed ;

	_square.setPosition((Game::width + 1)/2, Util::getRandomFloat((Game::height + 1)/4.0, (Game::height + 1)*3/4.0));

	launched = false;
}

void Ball::launch(void)
{
	launched = true;
	_clock.restart();
}

// TODO: Implement proper boucing off
bool Ball::collidesWithPaddle(const sf::RectangleShape& paddle)
{
	if (!_square.getGlobalBounds().intersects(paddle.getGlobalBounds())) {
		return false;
	}
	auto paddleBounds {paddle.getGlobalBounds()};
	auto ballBounds  {_square.getGlobalBounds()};

	sf::Vector2f paddleOrigin((paddleBounds.top + paddleBounds.width)/2, (paddleBounds.top + paddleBounds.height)/2);
	sf::Vector2f ballOrigin((ballBounds.top + ballBounds.width)/2, (ballBounds.top + ballBounds.height)/2);

	// Creating the new velocity
	sf::Vector2f newVelocity(ballOrigin.x - paddleOrigin.x, ballOrigin.y - paddleOrigin.y);
	std::cout << "New velocity 1: (" << newVelocity.x << "," << newVelocity.y << ")\n";

	// Setting the angle between 10 and 40 degrees
	if (newVelocity.x > 0) {
		// East quadrant
		if (newVelocity.y > 0) {
			// South quadrant
			newVelocity.y = std::max(newVelocity.y, static_cast<float>(std::tan(TORAD(10))) * newVelocity.x);
			newVelocity.y = std::min(newVelocity.y, static_cast<float>(std::tan(TORAD(40))) * newVelocity.x);
		} else {
			// North quadrant
			newVelocity.y = std::min(newVelocity.y, static_cast<float>(std::tan(TORAD(360 - 10))) * newVelocity.x);
			newVelocity.y = std::max(newVelocity.y, static_cast<float>(std::tan(TORAD(360 - 40))) * newVelocity.x);
		}
	} else {
		// West quadrant
		if (newVelocity.y > 0) {
			// South quadrant
			newVelocity.y = std::max(newVelocity.y, static_cast<float>(std::tan(TORAD(180 - 10))) * newVelocity.x);
			newVelocity.y = std::min(newVelocity.y, static_cast<float>(std::tan(TORAD(180 - 40))) * newVelocity.x);
		} else {
			// North quadrant
			newVelocity.y = std::min(newVelocity.y, static_cast<float>(std::tan(TORAD(180 + 10))) * newVelocity.x);
			newVelocity.y = std::max(newVelocity.y, static_cast<float>(std::tan(TORAD(180 + 40))) * newVelocity.x);
		}
	}

	// Making it with size one by dividing it by its modulus
	newVelocity /= static_cast<float>(std::sqrt(std::pow(newVelocity.x, 2) + std::pow(newVelocity.y, 2)));
	std::cout << "New velocity 2: (" << newVelocity.x << "," << newVelocity.y << ")\n";

	// Now that the vector has size one, multiply it with the speed
	newVelocity *= _speed;
	std::cout << "New velocity 3: (" << newVelocity.x << "," << newVelocity.y << ")\n";

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

