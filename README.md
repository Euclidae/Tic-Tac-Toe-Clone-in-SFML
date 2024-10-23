### Tic Tac Toe (SFML)

**README**

This project implements a classic Tic Tac Toe game using the SFML (Simple and Fast Multimedia Library) framework.

### Files

* **Game.hpp/cpp:** Maintains the game state, handles player turns, and updates the game board.
* **InputManager.hpp/cpp:** Manages input from the player (mouse clicks).
* **main.cpp:** The entry point of the application.
* **SFML headers:** Required SFML headers for graphics, window, and system.

### Compilation

1. **Install SFML:** Download and install SFML from [https://www.sfml-dev.org/download.php](https://www.sfml-dev.org/download.php).
2. **Clone the Repository:** Clone this repository to your local machine.
3. **Compile:** Open a terminal or command prompt in the project directory and compile the code using the following command:

   ```bash
   g++ *.cpp -o tictactoe -lsfml-graphics -lsfml-window -lsfml-system
   ```

### Running

1. Execute the compiled executable:
   ```bash
   ./tictactoe
   ```

### Game Play

* **Click on a square:** The current player's symbol (X or O) will be placed on the selected square.
* **Win Condition:** The game ends when a player gets three of their symbols in a row, column, or diagonal.
* **Draw:** If the board fills up without a winner, the game is a draw.

### Customization

* **Game Logic:** Modify the game rules or add features in the `Game` class.
* **Input:** Adjust the input handling in the `InputManager` class.

**Note:** This is a basic implementation of Tic Tac Toe. You can extend it with features like AI opponents, different game modes, or multiplayer functionality.
