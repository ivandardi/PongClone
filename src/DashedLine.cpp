#include "DashedLine.h"

#include "Game.h"


// TODO: Fix the dashed line
DashedLine::DashedLine(sf::Vector2f begin, sf::Vector2f end, unsigned long quantity)
	: _lines()
	, _begin(begin)
	, _end(end)
	, _quantity(quantity)
{
	// make _begin always be left of _end
    if (_begin.x >= _end.x) {
		std::swap(_begin, _end);
    }

	_lines.resize(_quantity);

	for (auto& elem : _lines) {
		elem = sf::VertexArray(sf::Lines, 2);
	}

	float jump = (_end.x - _begin.x)/_quantity;
	float x = _begin.x;
	for (size_t i = 0; i < _lines.size(); ++i) {
		_lines[i][0] = sf::Vertex(sf::Vector2f(x, _lineFunction(x)), ((i % 2 == 0) ? sf::Color::White : sf::Color::Black));
		_lines[i][1] = sf::Vertex(sf::Vector2f(x, _lineFunction(x + jump)), ((i % 2 == 0) ? sf::Color::White : sf::Color::Black));
		x += jump;
	}
}

float DashedLine::_lineFunction(float x)
{
	float dx = _end.x - _begin.x;
	float dy = _end.y - _begin.y;
	float m = dx/dy;
	//(y + yo) = m(x - xo)
	return m*(x - _begin.x) - _begin.y;
}

void DashedLine::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const auto& elem : _lines) {
		target.draw(elem, states);
	}
}
