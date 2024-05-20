#pragma once
#include <SFML/Graphics.hpp>
#include "state.hpp"
#include "GameState.hpp"
#include "Game.hpp"

namespace Deus {
	class MainMenuState : public State {
	public:
		MainMenuState(GameDataRef data);
		void init();

		void handleInput();
		void update(float dt);
		void draw(float dt);
		~MainMenuState();
	private:
		GameDataRef _data;
		sf::Sprite _background;
		sf::Sprite _playButton;
		sf::Sprite _playButtonOuter;
		sf::Sprite _title;
	};
}