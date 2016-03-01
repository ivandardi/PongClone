#ifndef GAME_H
#define GAME_H

#include "GameView.h"

class Game {
public:
	static const constexpr char* title  {"Pong Clone"};
	static constexpr int         width  {1366};
	static constexpr int         height {768};
	static constexpr sf::Uint32  style  {sf::Style::Fullscreen};

public:
	Game();
	void run(void);
};

#endif // GAME_H
