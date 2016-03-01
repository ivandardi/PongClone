#include "Game.h"

#include <iostream>

int main(void)
{
	try {
		Game g;
		g.run();
	} catch (std::exception e) {
		std::cerr << "Unhandled exception: " << e.what() << std::endl;
	}
	return 0;
}
