#ifndef PADDLE_H
#define PADDLE_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Entity.h"


class Ball;

////////////////////////////////////////////////////////////
/// \brief Paddle class for player and computer
///
////////////////////////////////////////////////////////////
class Paddle : public Entity {

public:

    ////////////////////////////////////////////////////////////
    /// \brief Constructor with horizontal position
    ///
    /// \param posX The horizontal position of the paddle
    ///
    ////////////////////////////////////////////////////////////
    explicit Paddle(float posX);

    ////////////////////////////////////////////////////////////
    /// \brief Moves the paddle downwards
    ///
    /// \param multiplier Speed multiplier of the movement
    ///
    ////////////////////////////////////////////////////////////
    void moveDown(float multiplier = 1.0);

    ////////////////////////////////////////////////////////////
    /// \brief Moves the paddle upwards
    ///
    /// \param multiplier Speed multiplier of the movement
    ///
    ////////////////////////////////////////////////////////////
    void moveUp(float multiplier = 1.0);

    ////////////////////////////////////////////////////////////
    /// \brief Increases the score of the paddle by one
    ///
    ////////////////////////////////////////////////////////////
    void increaseScore();

    ////////////////////////////////////////////////////////////
    /// \brief Returns the paddle's score
    ///
    /// \return The paddle's score
    ///
    ////////////////////////////////////////////////////////////
    int getScore() const;

    ////////////////////////////////////////////////////////////
    /// \brief Resets the Y position to the center of the screen's height
    ///
    ////////////////////////////////////////////////////////////
    void resetY();

    ////////////////////////////////////////////////////////////
    /// \brief Updates the paddle AI with the predicted height of the ball
    ///
    /// \param y Predicted height of the ball
    ///
    ////////////////////////////////////////////////////////////
    void AIUpdate(float y);

    ////////////////////////////////////////////////////////////
    /// \brief Moves the paddle towards the predicted ball height, or returns it
    ///        to the center of the screen
    ///
    /// \param x Horizontal position of the ball
    ///
    ////////////////////////////////////////////////////////////
    void AIMove(float x);

    ////////////////////////////////////////////////////////////
    /// \brief Sets the moving state
    ///
    ////////////////////////////////////////////////////////////
    void setMoving(bool isMoving);

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
    const int       _speed;          ///< Speed of movement
          bool      _isMoving;       ///< Tells whether or not the paddle is moving
          int       _predictedBallY; ///< Predicted ball Y to be used with the AI
          int       _score;          ///< Score of the paddle
          sf::Font  _font;           ///< Font for the score text
          sf::Text  _scoreText;      ///< The score to be displayed

};

#endif // PADDLE_H
