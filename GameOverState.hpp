#pragma once
#include <SFML/Graphics.hpp>
#include "state.hpp"
#include "GameState.hpp"
#include "Game.hpp"

namespace Deus {
	class GameOverState : public State {
	public:
		GameOverState(GameDataRef data);
		void init();

		void handleInput();
		void update(float dt);
		void draw(float dt);
		~GameOverState();
	private:
		GameDataRef _data;
		sf::Sprite _homeButton;
		sf::Sprite _retryButton;
	};
}