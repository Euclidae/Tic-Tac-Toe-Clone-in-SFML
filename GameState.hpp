#pragma once
#pragma once
#include <SFML/Graphics.hpp>
#include "state.hpp"
#include "Game.hpp"
#include "AI.hpp"

namespace Deus {
	class GameState : public State {
	public:
		GameState(GameDataRef data);
		void init();

		void handleInput();
		void update(float dt);
		void draw(float dt);
		
		~GameState();
	private:

		
		GameDataRef _data;
		sf::Sprite _background;
		sf::Sprite _pauseButton;
		sf::Sprite _gridSprite;

		sf::Sprite _gridPieces[3][3];
		int gridArray[3][3];
		int turn;
		int gamestate;
		void InitGridPieces();
		void CheckAndPlacePiece();
		void CheckPlayerHasWon(int turn);
		void Check3PiecesForMatch(int x1, int y1, int x2, int y2, int x3, int y3, int pieceToCheck);
		AI* ai;
		sf::Clock _clock;
	};
}