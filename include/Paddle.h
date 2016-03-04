#ifndef PADDLE_H
#define PADDLE_H

#include <SFML/Graphics.hpp>

class Ball;

class Paddle : public sf::Drawable, public sf::Transformable {
private:
	const int _speed{20};

	// Predicted ball Y to be used with the AI
	int _predictedBallY{0};

	// Points of the paddle
	int _points;

	// Font and text for the scores
	sf::Font _font;
	sf::Text _score;

	// The actual paddle
	sf::RectangleShape _rect;

public:
	static const int WIDTH;
	static const int HEIGHT;

	Paddle(float posX, float posY);
	void moveDown(float multiplier = 1.0);
	void moveUp(float multiplier = 1.0);
	void increaseScore(void);
	int getScore(void) const;
	void AIUpdate(float y);
	void AIMove(float x);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::RectangleShape getPaddle(void) const { return _rect; }

};

#endif // PADDLE_H
