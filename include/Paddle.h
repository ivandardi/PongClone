#ifndef PADDLE_H
#define PADDLE_H

#include <SFML/Graphics.hpp>

class Ball;

class Paddle : public sf::Drawable, public sf::Transformable {
private:

	static const int WIDTH;
	static const int HEIGHT;

	// Font and text for the scores
	sf::Font _font;
	sf::Text _score;

	// Points of the paddle
	int _points{0};

	// The actual paddle
	sf::RectangleShape _rect;

public:
	Paddle(float posX, float posY);
	void setY(float newY);
	void increaseY(float incrY);
	void increaseScore(void);
	int getScore(void) const;
	void updateAI(const Ball& ball);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::FloatRect getBounds(void) const { return _rect.getGlobalBounds(); }

};

#endif // PADDLE_H
