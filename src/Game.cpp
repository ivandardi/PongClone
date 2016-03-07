#include <Game.h>
#include <MainMenu.h>

Game::Game()
{
	GameView::_window.create(sf::VideoMode(width, height), title, style, sf::ContextSettings(0, 0, 4));
	GameView::_window.setMouseCursorVisible(false);
	GameView::_gameview.reset(new MainMenu);
}

void Game::run(void)
{
	while (GameView::_window.isOpen()) {
		sf::Event e;
		while (GameView::_window.pollEvent(e)) {
			if (e.type == sf::Event::KeyPressed) {
				if (e.key.code == sf::Keyboard::Escape) {
					GameView::_window.close();
				}
			}
		}
		GameView::_gameview->input();
		GameView::_gameview->update();
		GameView::_gameview->render();
    }
}
