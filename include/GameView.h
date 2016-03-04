#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <SFML/Graphics.hpp>

class GameView {
public:
	virtual void input(void)  = 0;
	virtual void update(void) = 0;
	virtual void render(void) = 0;

	virtual ~GameView() {};

	static sf::RenderWindow _window;
	static std::unique_ptr<GameView> _gameview;
};

#endif // GAMEVIEW_H
