#include "DashedLine.h"

#include "Game.h"

DashedLine::DashedLine(Direction direction, int position, unsigned long quantity)
	: _direction(direction)
	, _position(position)
	, _quantity(quantity)
	, _lines(_quantity, sf::VertexArray(sf::Lines, 2))
{
	if (_direction == Direction::Vertical) {
		for (size_t i = 0; i < _lines.size(); ++i) {
			_lines[i][0] = sf::Vertex(sf::Vector2f(position, (Game::height*i)/_lines.size()), ((i % 2 == 0) ? sf::Color::White : sf::Color::Black));
			_lines[i][1] = sf::Vertex(sf::Vector2f(position, (Game::height*(i + 1))/_lines.size()), ((i % 2 == 0) ? sf::Color::White : sf::Color::Black));
		}
	} else {
		for (size_t i = 0; i < _lines.size(); ++i) {
			_lines[i][0] = sf::Vertex(sf::Vector2f((Game::width*i)/_lines.size(), position), ((i % 2 == 0) ? sf::Color::White : sf::Color::Black));
			_lines[i][1] = sf::Vertex(sf::Vector2f(Game::width*(i + 1)/_lines.size(), position), ((i % 2 == 0) ? sf::Color::White : sf::Color::Black));
		}
	}
}

void DashedLine::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const auto& elem : _lines) {
		target.draw(elem, states);
	}
}
