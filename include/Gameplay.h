#ifndef GAMEPLAY_H
#define GAMEPLAY_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Ball.h"
#include "DashedLine.h"
#include "GameView.h"
#include "Paddle.h"


////////////////////////////////////////////////////////////
/// \brief Gameplay gameview class
///
////////////////////////////////////////////////////////////
class Gameplay : public GameView {

public:

    ////////////////////////////////////////////////////////////
    /// \brief Explicit gameplay constructor
    ///
    ////////////////////////////////////////////////////////////
    explicit Gameplay();

    ////////////////////////////////////////////////////////////
    /// \brief Overriden user input function
    ///
    ////////////////////////////////////////////////////////////
    void  input() override;

    ////////////////////////////////////////////////////////////
    /// \brief Overriden update function
    ///
    ////////////////////////////////////////////////////////////
    void update() override;

    ////////////////////////////////////////////////////////////
    /// \brief Overriden rendering function
    ///
    ////////////////////////////////////////////////////////////
    void render() override;

private:

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////

    const DashedLine _divisor;  ///< The divisor array for the screen
          Paddle     _player;   ///< Player paddle
          Paddle     _computer; ///< Computer paddle
          Ball       _ball;     ///< The ball
          int        _winner;   ///< The winner indicator. -1 is no winner, 0 is player winner and 1 is computer
          sf::Font   _font;     ///< Font for scores and winning text

};

#endif // GAMEPLAY_H
