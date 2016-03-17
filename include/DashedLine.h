#ifndef DASHEDLINE_H
#define DASHEDLINE_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>


////////////////////////////////////////////////////////////
/// \brief Enum class for the direction of the dashed line
///
////////////////////////////////////////////////////////////
enum class Direction {
    Horizontal,
    Vertical
};


////////////////////////////////////////////////////////////
/// \brief Dashed line class
///
////////////////////////////////////////////////////////////
class DashedLine : public sf::Drawable, public sf::Transformable {

public:

    ////////////////////////////////////////////////////////////
    /// \brief Dashed line constructor
    ///
    /// \param direction The direction of the line
    /// \param position The position of the line on the screen
    /// \param quantity How many dashes the line will have
    ///
    ////////////////////////////////////////////////////////////
    DashedLine(Direction direction, float position, unsigned long quantity);

    ////////////////////////////////////////////////////////////
    /// \brief Draw the shape to a render target
    ///
    /// \param target Render target to draw to
    /// \param states Current render states
    ///
    ////////////////////////////////////////////////////////////
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    const Direction              _direction; ///< The direction of the line
    const float                  _position;  ///< The position of the line on the screen
    const unsigned long          _quantity;  ///< How many dashes the line will have
    std::vector<sf::VertexArray> _lines;     ///< The actual line

};

#endif // DASHEDLINE_H
