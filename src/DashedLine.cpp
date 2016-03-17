////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "DashedLine.h"
#include "Game.h"

////////////////////////////////////////////////////////////
DashedLine::DashedLine(Direction direction, float position, unsigned long quantity)
    : _direction(direction)
    , _position (position)
    , _quantity (quantity)
    , _lines    (_quantity, sf::VertexArray(sf::Lines, 2))
{
    if (_direction == Direction::Vertical) {
        for (size_t i = 0; i < _lines.size(); ++i) {
            _lines[i][0] = sf::Vertex({_position, static_cast<float>(Game::height) *  i      / _lines.size()}, ((i % 2 == 0) ? sf::Color::White : sf::Color::Black));
            _lines[i][1] = sf::Vertex({_position, static_cast<float>(Game::height) * (i + 1) / _lines.size()}, ((i % 2 == 0) ? sf::Color::White : sf::Color::Black));
        }
    } else {
        for (size_t i = 0; i < _lines.size(); ++i) {
            _lines[i][0] = sf::Vertex({static_cast<float>(Game::width) *  i      / _lines.size(), _position}, ((i % 2 == 0) ? sf::Color::White : sf::Color::Black));
            _lines[i][1] = sf::Vertex({static_cast<float>(Game::width) * (i + 1) / _lines.size(), _position}, ((i % 2 == 0) ? sf::Color::White : sf::Color::Black));
        }
    }
}

////////////////////////////////////////////////////////////
void DashedLine::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (const auto& elem : _lines) {
        target.draw(elem, states);
    }
}
