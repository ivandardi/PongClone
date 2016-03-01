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
	const float _radius{25};
	std::mt19937 rgn;
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
	void collidesWithPaddle(const Paddle& paddle);
	void collideswithWall(void);
	void updatePosition(void);
	Edge::Side isOffscreen(void) const;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	bool readyToLaunch{true};
};

#endif // BALL_H
