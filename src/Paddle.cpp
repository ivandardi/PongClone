////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Ball.h"
#include "Game.h"
#include "Paddle.h"
#include "Util.h"


////////////////////////////////////////////////////////////
Paddle::Paddle(float posX)
    : Entity         (40.f, Game::height/5.f)
    , _speed         (300)
    , _isMoving      (false)
    , _predictedBallY(0)
    , _score         (0)
    , _font          ()
    , _scoreText     (std::to_string(_score), _font, 50)
{
    if (!_font.loadFromFile("assets/mplus-1m-bold.ttf")) {
        throw std::runtime_error("Failed to load font.");
    }

    // Setting the origin of the rectangle on its center
    _rect.setOrigin(width()/2, height()/2);

    // Setting the actual positions of the paddles
    _rect.setPosition(posX, 0);
    resetY();

    // Setting the score position
    if (posX < Game::width/2) {
        _scoreText.setPosition(Game::width/2 - _scoreText.getGlobalBounds().width - 80, 50);
    } else {
        _scoreText.setPosition(Game::width/2 + 80, 50);
    }
}

////////////////////////////////////////////////////////////
void Paddle::moveDown(float multiplier)
{
    if (!_isMoving) {
        _clock.restart();
        _isMoving = true;
    }

    int padding = 1;

    float maxY = Game::height - padding;
    float delta = _clock.restart().asSeconds();
    if (bottom() < maxY) {
        _rect.move(0, _speed * multiplier * delta);
    }
}

////////////////////////////////////////////////////////////
void Paddle::moveUp(float multiplier)
{
    if (!_isMoving) {
        _clock.restart();
        _isMoving = true;
    }

    int padding = 1;

    float minY = 0 + padding;
    float delta = _clock.restart().asSeconds();
    if (top() > minY) {
        _rect.move(0, -_speed * multiplier * delta);
    }
}

////////////////////////////////////////////////////////////
void Paddle::increaseScore()
{
    _scoreText.setString(std::to_string(++_score));
}

////////////////////////////////////////////////////////////
int Paddle::getScore() const
{
    return _score;
}

////////////////////////////////////////////////////////////
void Paddle::resetY()
{
    _rect.setPosition(_rect.getPosition().x, Game::height/2);
}

////////////////////////////////////////////////////////////
void Paddle::AIUpdate(float y)
{
    _predictedBallY = y;
}

////////////////////////////////////////////////////////////
void Paddle::AIMove(float x)
{
    // Set up a random region of collision each time
    float topY    = top()    + Util::getRandomInt(0, height()/2 - 5);
    float bottomY = bottom() - Util::getRandomInt(0, height()/2 + 5);

    // Paddle only follows ball on the left half of the screen
    if (x < Game::width/2) {
        if (bottomY < _predictedBallY) {
            moveDown();
        } else if (topY > _predictedBallY) {
            moveUp();
        } else {
            _isMoving = false;
        }
    } else {
        // Paddles goes to the general middle of the screen
        if (bottomY < Game::height/2) {
            moveDown(0.3);
        } else if (topY > Game::height/2) {
            moveUp(0.3);
        } else {
            _isMoving = false;
        }
    }
}


////////////////////////////////////////////////////////////
void Paddle::setMoving(bool isMoving)
{
    _isMoving = isMoving;
}


////////////////////////////////////////////////////////////
void Paddle::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_rect, states);
    target.draw(_scoreText, states);
}
