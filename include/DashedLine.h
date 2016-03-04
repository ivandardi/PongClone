#ifndef DASHEDLINE_H
#define DASHEDLINE_H

#include <SFML/Graphics.hpp>

class DashedLine : public sf::Drawable, public sf::Transformable {
private:
	std::vector<sf::VertexArray> _lines;
	float _lineFunction(float x);
	sf::Vector2f _begin;
	sf::Vector2f _end;
	const unsigned long _quantity;
public:
	DashedLine(sf::Vector2f bgn, sf::Vector2f end, unsigned long quantity);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif // DASHEDLINE_H
