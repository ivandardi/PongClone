////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Ball.h"
#include "Game.h"
#include "Paddle.h"
#include "Util.h"
#include <iostream>


////////////////////////////////////////////////////////////
// Constants
////////////////////////////////////////////////////////////
static constexpr double PI    {3.14159265};
static constexpr float  MAXANG{48 * PI / 180.0};


////////////////////////////////////////////////////////////
Ball::Ball()
    : Entity   (25, 25)
    , _velocity()
    , _speed   (500)
    , _launched(false)
    , _hits    (0)
{
    _rect.setOrigin(width()/2, height()/2);
    restart();
}


////////////////////////////////////////////////////////////
void Ball::restart()
{
    _speed = 500;

    float angle = Util::getRandomFloat(0, MAXANG);
    _velocity = sf::Vector2f(std::cos(angle) * Util::getRandomSignal() * _speed,
                             std::sin(angle) * Util::getRandomSignal() * _speed);

    _rect.setPosition(Game::width/2, Util::getRandomFloat(Game::height/4.0, Game::height*3/4.0));

    _launched = false;
}


////////////////////////////////////////////////////////////
void Ball::launch()
{
    _launched = true;
    _clock.restart();
}


////////////////////////////////////////////////////////////
bool Ball::collidesWithPaddle(const Paddle& paddle)
{
    sf::FloatRect paddleBounds {paddle.getBoundingBox()};
    sf::FloatRect ballBounds   {getBoundingBox()};

    if (!paddleBounds.intersects(ballBounds)) {
        return false;
    }

    // Creating the new velocity
    sf::Vector2f newVelocity{center().x - paddle.center().x, center().y - paddle.center().y};

    // Setting the angle between 0 and MAXANG degrees
    if (newVelocity.x > 0) {
        // East quadrant
        if (newVelocity.y > 0) {
            // South quadrant
            newVelocity.y = std::min(newVelocity.y, static_cast<float>(std::tan(MAXANG)) * newVelocity.x);
        } else {
            // North quadrant
            newVelocity.y = std::max(newVelocity.y, static_cast<float>(std::tan(-MAXANG)) * newVelocity.x);
        }
    } else {
        // West quadrant
        if (newVelocity.y > 0) {
            // South quadrant
            newVelocity.y = std::min(newVelocity.y, static_cast<float>(std::tan(PI - MAXANG)) * newVelocity.x);
        } else {
            // North quadrant
            newVelocity.y = std::max(newVelocity.y, static_cast<float>(std::tan(PI + MAXANG)) * newVelocity.x);
        }
    }

    // Making it with size one by dividing it by its modulus
    newVelocity /= static_cast<float>(std::sqrt(std::pow(newVelocity.x, 2) + std::pow(newVelocity.y, 2)));

    // For every 5 hits, make the ball go a little bit faster
    if (++_hits > 5) {
        _speed *= 1.1f;
        _hits = 0;
    }

    // Now that the vector has size one, multiply it with the speed
    newVelocity *= _speed;

    // Set the new velocity
    _velocity = newVelocity;

    return true;
}


////////////////////////////////////////////////////////////
void Ball::collideswithWall()
{
    // The set positions prevent the ball from becoming stuck in the wall
    if (0 >= top()) {
        _rect.setPosition(center().x, height() / 2);
        _velocity.y *= -1;
    } else if(bottom() >= Game::height) {
        _velocity.y *= -1;
        _rect.setPosition(center().x, Game::height - height() / 2);
    }
}


////////////////////////////////////////////////////////////
void Ball::updatePosition()
{
    float delta = _clock.restart().asSeconds();
    _rect.move(_velocity * delta);
}


////////////////////////////////////////////////////////////
int Ball::predictY() const
{
    float m = _velocity.y/_velocity.x;
    int predictedY = std::abs(m * -center().x + center().y);
    int reflections = predictedY / Game::height;
    predictedY = (reflections % 2 == 0 ? predictedY % Game::height : Game::height - (predictedY % Game::height));
    return predictedY;
}


////////////////////////////////////////////////////////////
Side Ball::isOffscreen() const
{
    auto pos = _rect.getGlobalBounds();
    if (pos.left + pos.width < 0) {
        return Side::Left;
    }
    if (pos.left > Game::width) {
        return Side::Right;
    }
    return Side::None;
}


////////////////////////////////////////////////////////////
bool Ball::isLaunched() const
{
    return _launched;
}


////////////////////////////////////////////////////////////
void Ball::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_rect, states);
}
