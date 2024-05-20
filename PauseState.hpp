#pragma once

#include <SFML/Graphics.hpp>
#include "state.hpp"
#include "Game.hpp"

namespace Deus {
	class PauseState : public State {
	public:
		PauseState(GameDataRef data);
		void init();

		void handleInput();
		void update(float dt);
		void draw(float dt);
		~PauseState();
	private:
		GameDataRef _data;
		sf::Sprite _background;
		sf::Sprite _resumeButton;
		sf::Sprite _homeButton;
	};
}