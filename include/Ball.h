#ifndef BALL_H
#define BALL_H

#include <SFML/Graphics.hpp>

class Paddle;

namespace Edge
{
enum Side {
	None,
	Right,
	Left
};
}

class Ball : public sf::Drawable, public sf::Transformable {
private:
	const float _radius;
	const float _speed;
	int _hits;
	sf::RectangleShape _square;
	sf::Vector2f _velocity;
	sf::Clock _clock;

public:
	Ball();
	/**
	 Sets the ball position at the starting position and launches it.
	 */
	void restart(void);
	void launch(void);
	bool collidesWithPaddle(const sf::RectangleShape& paddle);
	void collideswithWall(void);
	void updatePosition(void);
	int predictY(void) const;
	float getX(void) const;
	Edge::Side isOffscreen(void) const;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	bool launched{false};
};

#endif // BALL_H
