#include "MainMenu.h"

#include "Game.h"
#include "Gameplay.h"

MainMenu::MainMenu()
	: _font()
	, _selection(0)
	, _knob({_sizeKnob, _sizeKnob})
{
	if (!_font.loadFromFile("assets/mplus-1m-bold.ttf")) {
		throw std::runtime_error("Failed to load font.");
	}

	_text[0] = sf::Text("Pong Clone", _font, 100);
	_text[1] = sf::Text("Start Game", _font);
	_text[2] = sf::Text("Exit", _font);

	sf::FloatRect bounds;
	sf::Vector2f pos;

	bounds = _text[0].getGlobalBounds();
	pos.x = (Game::width - bounds.width + 1)/2;
	pos.y = (Game::height - bounds.height + 1)/4;
	_text[0].setPosition(pos);

	bounds = _text[1].getGlobalBounds();
	pos.x = (Game::width - bounds.width + 1)/2;
	pos.y = (Game::height - bounds.height + 1)/2;
	_text[1].setPosition(pos);

	bounds = _text[2].getGlobalBounds();
	pos.x = (Game::width - bounds.width + 1)/2;
	pos.y = (Game::height - bounds.height + 1)/2 + 50;
	_text[2].setPosition(pos);

	bounds = _knob.getGlobalBounds();
	pos.x = (Game::width - bounds.width + 1)/2 - 100;
	pos.y = (Game::height - bounds.height + 1)/2 + 7;
	_knob.setPosition(pos);
}

void MainMenu::input(void)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		if (_selection != 0) {
			_selection = 0;
			_updateSelection = true;
		}
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		if (_selection != 1) {
			_selection = 1;
			_updateSelection = true;
		}
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
		if (_selection == 0) {
			_gameview.reset(new Gameplay);
		} else {
			_window.close();
		}
	}
}

void MainMenu::update(void)
{
	if (_updateSelection) {
		_knob.move(0, (_selection == 0) ? -50 : 50);
		_updateSelection = false;
	}
}

void MainMenu::render(void)
{
	_window.clear();

	_window.draw(_text[0]);
	_window.draw(_text[1]);
	_window.draw(_text[2]);

	_window.draw(_knob);

	_window.display();
}
