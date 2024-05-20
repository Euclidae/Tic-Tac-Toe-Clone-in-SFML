#pragma once
#include <SFML/Graphics.hpp>
#include "StateMachine.hpp"
#include "Game.hpp"

namespace Deus {
	class SplashState : public State {
	public:
		SplashState(GameDataRef data);
		void init();

		void handleInput();
		void update(float dt);
		void draw(float dt);
		SplashState(){}
	private:
		GameDataRef _data;
		sf::Clock _clock;

		sf::Sprite _background;
	};
}