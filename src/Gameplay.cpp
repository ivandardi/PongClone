////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Game.h"
#include "Gameplay.h"
#include "MainMenu.h"
#include <iostream>


////////////////////////////////////////////////////////////
Gameplay::Gameplay()
    : _divisor (Direction::Vertical, Game::width/2, 31)
    , _player  (Game::width - 40)
    , _computer(40)
    , _ball    ()
    , _winner  (-1)
    , _font    ()
{
    if (!_font.loadFromFile("assets/mplus-1m-bold.ttf")) {
        throw std::runtime_error("Failed to load font.");
    }
}


////////////////////////////////////////////////////////////
void Gameplay::input(void)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        _player.moveUp();
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        _player.moveDown();
    } else {
        _player.setMoving(false);
    }

    if (!_ball.isLaunched()) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            _ball.launch();
            _computer.AIUpdate(_ball.predictY());
        }
    }
}


////////////////////////////////////////////////////////////
void Gameplay::update(void)
{
    // Check to see if someone won
    if (_winner != -1) {
        Gameview.reset(new MainMenu);
        return;
    }
    constexpr int maxScore = 10;
    if (_player.getScore() == maxScore) {
        _winner = 0;
    } else if (_computer.getScore() == maxScore) {
        _winner = 1;
    }

    if (!_ball.isLaunched()) {
        return;
    }

    // Move the computer paddle with AI
    _computer.AIMove(_ball.center().x);

    // Check for ball collisions
    if (_ball.collidesWithPaddle(_player)) {
        _computer.AIUpdate(_ball.predictY());
    } else {
        _ball.collidesWithPaddle(_computer);
    }
    _ball.collideswithWall();

    // After collisions are calculated, move the ball
    _ball.updatePosition();

    // Check to see if ball is offscreen and award points accordingly
    if (_ball.isOffscreen() != Side::None) {
        _ball.isOffscreen() == Side::Left ? _player.increaseScore() : _computer.increaseScore();
        _ball.restart();
        _player.resetY();
        _computer.resetY();
    }
}


////////////////////////////////////////////////////////////
void Gameplay::render(void)
{
    Window.clear();

    Window.draw(_divisor);
    Window.draw(_player);
    Window.draw(_computer);

    if (_winner != -1) {
        // If player won
        sf::Text winner("", _font, 75);
        std::string result{(_winner == 1 ? "Lost" : "Won")};
        winner.setString("You " + result + "!");
        winner.setPosition(Game::width/2 - winner.getGlobalBounds().width/2, Game::height/4 - winner.getGlobalBounds().height);
        Window.draw(winner);
    } else {
        // If nobody won yet
        Window.draw(_ball);
    }

    Window.display();

    // If someone wins, let the winning text stay onscreen for 5 seconds
    if (_winner != -1) {
        sf::sleep(sf::seconds(5));
    }
}
