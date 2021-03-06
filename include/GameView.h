#ifndef GAMEVIEW_H
#define GAMEVIEW_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>

////////////////////////////////////////////////////////////
/// \brief Gameview base class
///
////////////////////////////////////////////////////////////
class GameView {

public:

    ////////////////////////////////////////////////////////////
    /// \brief User input virtual function
    ///
    ////////////////////////////////////////////////////////////
    virtual void  input() = 0;

    ////////////////////////////////////////////////////////////
    /// \brief Update virtual function
    ///
    ////////////////////////////////////////////////////////////
    virtual void update() = 0;

    ////////////////////////////////////////////////////////////
    /// \brief Rendering virtual function
    ///
    ////////////////////////////////////////////////////////////
    virtual void render() = 0;

    ////////////////////////////////////////////////////////////
    /// \brief Virtual destructor for inheritance
    ///
    ////////////////////////////////////////////////////////////
    virtual ~GameView() = default;

    ////////////////////////////////////////////////////////////
    // Static member data
    ////////////////////////////////////////////////////////////
    static sf::RenderWindow          Window;   ///< Game Window
    static std::unique_ptr<GameView> Gameview; ///< Current gameview pointer

};

#endif // GAMEVIEW_H
