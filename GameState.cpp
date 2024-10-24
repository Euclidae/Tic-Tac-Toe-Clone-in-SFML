#include "GameState.hpp"
#include <iostream>
#include <sstream>
#include "DEFINITIONS.hpp"
#include "GameOverState.hpp"
#include "PauseState.hpp"

namespace Deus {
	GameState::GameState(GameDataRef data) : _data(data) {

	}

	void GameState::init() {
		gamestate = STATE_PLAYING;
		turn = PLAYER_PIECE;
		this->ai = new AI(turn, this->_data);

		this->_data->assets.LoadTexture("Pause Button", PAUSE_BUTTON);
		this->_data->assets.LoadTexture("Grid Sprite", GRID_SPRITE_FILEPATH);
		this->_data->assets.LoadTexture("X Piece", X_PIECE_FILEPATH);
		this->_data->assets.LoadTexture("O Piece", O_PIECE_FILEPATH);
		this->_data->assets.LoadTexture("X Winning Piece", X_WINNING_PIECE_FILEPATH);
		this->_data->assets.LoadTexture("O Winning Piece", O_WINNING_PIECE_FILEPATH);

		_background.setTexture(this->_data->assets.GetTexture("Background"));
		_gridSprite.setTexture(this->_data->assets.GetTexture("Grid Sprite"));
		_pauseButton.setTexture(this->_data->assets.GetTexture("Pause Button"));
		_pauseButton.setPosition(this->_data->window.getSize().x - _pauseButton.getLocalBounds().width, _pauseButton.getPosition().y);
		_gridSprite.setPosition((SCREEN_WIDTH/2)-(_gridSprite.getGlobalBounds().width/2),
			(SCREEN_HEIGHT / 2) - (_gridSprite.getGlobalBounds().height / 2));

		InitGridPieces();

		for (int x = 0; x < 3; ++x) {
			for (int y = 0; y < 3; ++y) {
				gridArray[x][y] = EMPTY_PIECE;
			}
		}

	}

	void GameState::handleInput() {
		sf::Event event;

		while (this->_data->window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				this->_data->window.close();
			}

			if (this->_data->input.IsSpriteClicked(this->_pauseButton, sf::Mouse::Left, this->_data->window)) {
				this->_data->machine.AddState(StateRef(new PauseState(_data)), false);
			}
			else if (this->_data->input.IsSpriteClicked(this->_gridSprite, sf::Mouse::Left, this->_data->window)) {
				if (STATE_PLAYING == gamestate) {
					this->CheckAndPlacePiece();
				}
							}
		}
	}

	void GameState::update(float dt) {
		if (STATE_DRAW == gamestate || STATE_LOSE == gamestate || STATE_WON == gamestate) {
			if (this->_clock.getElapsedTime().asSeconds() > TIME_BEFORE_BEFORE_SHOWING_GAME_OVER) {
				this->_data->machine.AddState(StateRef(new GameOverState(_data)), true);
			}
		}
	}

	void GameState::draw(float dt) {
		this->_data->window.clear();


		this->_data->window.draw(this->_background);
		this->_data->window.draw(this->_pauseButton);
		this->_data->window.draw(this->_gridSprite);

		for (int x = 0; x < 3; ++x) {
			for (int y = 0; y < 3; ++y) {
				this->_data->window.draw(this->_gridPieces[x][y]);
			}
		}
		this->_data->window.display();

	}

	void GameState::InitGridPieces() {
		sf::Vector2u tempSpriteSize = this->_data->assets.GetTexture("X Piece").getSize();
		for (int x = 0; x < 3; ++x) {
			for (int y = 0; y < 3; ++y) {
				_gridPieces[x][y].setTexture(this->_data->assets.GetTexture("X Piece"));
				_gridPieces[x][y].setPosition(_gridSprite.getPosition().x + (tempSpriteSize.x * x) - 7, _gridSprite.getPosition().y +
					(tempSpriteSize.y * y) - 7);

				_gridPieces[x][y].setColor(sf::Color(255, 255, 255, 0));
			}
		}
	}

	void GameState::CheckAndPlacePiece() {
		sf::Vector2i touchPoint = this->_data->input.GetMousePosition(this->_data->window);
		sf::FloatRect gridSize = _gridSprite.getGlobalBounds();
		sf::Vector2f gapOutsideOfGrid = sf::Vector2f((SCREEN_WIDTH - gridSize.width) / 2, (SCREEN_HEIGHT - gridSize.height) / 2);

		sf::Vector2f gridLocalTouchPos = sf::Vector2f(touchPoint.x - gapOutsideOfGrid.x, touchPoint.y - gapOutsideOfGrid.y);

		//std::cout << gridLocalTouchPos.x << ", " << gridLocalTouchPos.y << std::endl;

		sf::Vector2f gridSectionSize = sf::Vector2f(gridSize.width / 3, gridSize.height / 3);

		int column, row;

		// Check which column the user has clicked
		if (gridLocalTouchPos.x < gridSectionSize.x) // First Column
		{
			column = 1;
		}
		else if (gridLocalTouchPos.x < gridSectionSize.x * 2) // Second Column
		{
			column = 2;
		}
		else if (gridLocalTouchPos.x < gridSize.width) // Third Column
		{
			column = 3;
		}

		// Check which row the user has clicked
		if (gridLocalTouchPos.y < gridSectionSize.y) // First Row
		{
			row = 1;
		}
		else if (gridLocalTouchPos.y < gridSectionSize.y * 2) // Second Row
		{
			row = 2;
		}
		else if (gridLocalTouchPos.y < gridSize.height) // Third Row
		{
			row = 3;
		}

		if (gridArray[column - 1][row - 1] == EMPTY_PIECE)
		{
			gridArray[column - 1][row - 1] = turn;

			if (PLAYER_PIECE == turn)
			{
				_gridPieces[column - 1][row - 1].setTexture(this->_data->assets.GetTexture("X Piece"));

				this->CheckPlayerHasWon(turn);

			}
			
			_gridPieces[column - 1][row - 1].setColor(sf::Color(255, 255, 255, 255));
		}
	}

	void GameState::CheckPlayerHasWon(int turn){
		Check3PiecesForMatch(0, 0, 1, 0, 2, 0, turn);
		Check3PiecesForMatch(0, 1, 1, 1, 2, 1, turn);
		Check3PiecesForMatch(0, 2, 1, 2, 2, 2, turn);
		Check3PiecesForMatch(0, 0, 0, 1, 0, 2, turn);
		Check3PiecesForMatch(1, 0, 1, 1, 1, 2, turn);
		Check3PiecesForMatch(2, 0, 2, 1, 2, 2, turn);
		Check3PiecesForMatch(0, 0, 1, 1, 2, 2, turn);
		Check3PiecesForMatch(0, 2, 1, 1, 2, 0, turn);

		if (STATE_WON != gamestate) {
			gamestate = STATE_AI_PLAYING;
			ai->PlacePiece(&gridArray, _gridPieces, &gamestate);

			Check3PiecesForMatch(0, 0, 1, 0, 2, 0, AI_PIECE);
			Check3PiecesForMatch(0, 1, 1, 1, 2, 1, AI_PIECE);
			Check3PiecesForMatch(0, 2, 1, 2, 2, 2, AI_PIECE);
			Check3PiecesForMatch(0, 0, 0, 1, 0, 2, AI_PIECE);
			Check3PiecesForMatch(1, 0, 1, 1, 1, 2, AI_PIECE);
			Check3PiecesForMatch(2, 0, 2, 1, 2, 2, AI_PIECE);
			Check3PiecesForMatch(0, 0, 1, 1, 2, 2, AI_PIECE);
			Check3PiecesForMatch(0, 2, 1, 1, 2, 0, AI_PIECE);
		}

		int emptyNum = 9;

		for (int x = 0; x < 3; ++x) {
			for (int y = 0; y < 3; ++y) {
				if (EMPTY_PIECE != gridArray[x][y]) {
					--emptyNum;
				}
			}

			if (0 == emptyNum && (STATE_WON != gamestate) && (STATE_LOSE != gamestate)) {
				gamestate = STATE_DRAW;
			}
			if (STATE_DRAW == gamestate || STATE_LOSE == gamestate || STATE_WON == gamestate) {
				this->_clock.restart();
			}
			std::cout << gamestate << std::endl;
		}

	}

	void GameState::Check3PiecesForMatch(int x1, int y1, int x2, int y2, int x3, int y3, int pieceToCheck) {
		std::string winningPieceStr;
		if (pieceToCheck == gridArray[x1][y1] && pieceToCheck == gridArray[x2][y2] && pieceToCheck == gridArray[x3][y3]) {			
			if (O_PIECE == pieceToCheck) {
				winningPieceStr = "O Winning Piece";
			}
			else {
				winningPieceStr = "X Winning Piece";
			}
			
			_gridPieces[x1][y1].setTexture(this->_data->assets.GetTexture(winningPieceStr));
			_gridPieces[x2][y2].setTexture(this->_data->assets.GetTexture(winningPieceStr));
			_gridPieces[x3][y3].setTexture(this->_data->assets.GetTexture(winningPieceStr));

			if (PLAYER_PIECE == pieceToCheck) {
				gamestate = STATE_WON;
			}
			if(AI_PIECE == pieceToCheck) {
				gamestate = STATE_LOSE;
			}
		}
	}
}

