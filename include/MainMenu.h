#ifndef MAINMENU_H
#define MAINMENU_H

#include <GameView.h>

class MainMenu : public GameView {
private:
	// Font for array of text, holding all the text in the screen
	sf::Font _font;
	sf::Text _text[3];

	// Menu selection
    unsigned _selection:1;

    // Flag to tell if we should rerender the selection knob
    bool _updateSelection{false};

    // The selection knob
    const float _sizeKnob{15};
    sf::RectangleShape _knob;

public:
	MainMenu();
	void input (void) override;
	void update(void) override;
	void render(void) override;
};

#endif // MAINMENU_H
