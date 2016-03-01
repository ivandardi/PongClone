#include "GameView.h"

sf::RenderWindow GameView::_window;
std::unique_ptr<GameView> GameView::_gameview{nullptr};
