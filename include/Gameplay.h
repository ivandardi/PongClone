#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "GameView.h"

#include "DashedLine.h"
#include "Paddle.h"
#include "Ball.h"

class Gameplay : public GameView {
private:
	// Font for scores and winning text
	sf::Font _font;

	// The game objects
	Paddle _player;
	Paddle _computer;
	Ball _ball;

	// The divisor array for the screen
	const DashedLine _divisor;

	// The winner indicator. -1 is no winner, 0 is player winner and 1 is comp
	int _winner = -1;

public:
	Gameplay();
	void input (void) override;
	void update(void) override;
	void render(void) override;
};

#endif // GAMEPLAY_H