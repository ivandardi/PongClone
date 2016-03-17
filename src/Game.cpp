////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Game.h>
#include <MainMenu.h>

////////////////////////////////////////////////////////////
Game::Game()
{
    GameView::Window.create(sf::VideoMode(width, height), title, style, sf::ContextSettings(0, 0, 4));
    GameView::Window.setMouseCursorVisible(false);
    GameView::Gameview.reset(new MainMenu);
}

////////////////////////////////////////////////////////////
void Game::run()
{
    while (GameView::Window.isOpen()) {
        sf::Event e;
        while (GameView::Window.pollEvent(e)) {
            if (e.type == sf::Event::KeyPressed) {
                if (e.key.code == sf::Keyboard::Escape) {
                    GameView::Window.close();
                }
            }
        }
        GameView::Gameview->input();
        GameView::Gameview->update();
        GameView::Gameview->render();
    }
}
