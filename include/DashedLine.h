#ifndef DASHEDLINE_H
#define DASHEDLINE_H

#include <SFML/Graphics.hpp>

enum class Direction {
	Horizontal,
	Vertical
};

class DashedLine : public sf::Drawable, public sf::Transformable {
private:
	const Direction _direction;
	const int _position;
	const unsigned long _quantity;
	std::vector<sf::VertexArray> _lines;
public:
	DashedLine(Direction direction, int position, unsigned long quantity);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif // DASHEDLINE_H
