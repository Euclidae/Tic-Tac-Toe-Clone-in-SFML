#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <memory>
#include "StateMachine.hpp"
#include "InputManager.hpp"
#include "AssetManager.hpp"

namespace Deus {
	struct GameData {
		StateMachine machine;
		sf::RenderWindow window;
		AssetManager assets;
		InputManager input;
	};

	typedef std::shared_ptr<GameData> GameDataRef;

	class Game {
	public:
		Game(int width, int height, std::string title);
	private:
		const float dt = 1.0f / 60.0f;
		sf::Clock _clock;

		GameDataRef _data = std::make_shared<GameData>();
		void run();
	};
}