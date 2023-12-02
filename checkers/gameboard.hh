/* Checkers (for one player)
 *
 * The GameBoard class method and attribute definition,
 * most of the game's logic is handled through the class
 * while the main file only asks for user input and performs
 * some initial validation before passing parameters to the object.
 *
 * */

#ifndef GAMEBOARD_HH
#define GAMEBOARD_HH
#include <vector>


// Size of the gameboard
const unsigned int SIZE = 8;

// Width of the left-most column, needed in printing the gameboard
const unsigned int LEFT_COLUMN_WIDTH = 5;

// GameBoard class
class GameBoard
{
public:
    // Constructor:
    // Takes user input and chooses the character for gamepiece
    GameBoard(char const& piece);

    // Prints the gameboard (after you have finished the method).
    void print() const;

    // Moves a piece on the gameboard with some validity checking
    void move(const std::vector<unsigned int>& moves);

    // Check game score for ending condition
    bool is_game_over();

    // Displays statistics at the end of the game
    void quit_game() const;

private:
    // Prints a line with the given length and fill character.
    void print_line(unsigned int length, char fill_character) const;

    // Initializes the board piece placement
    void fill_board();

    // Represent the board as a matrix
    std::vector<std::vector<char>> board_;

    char piece_;

    int moves_ = 0;

    int pieces_ = 0;
};

#endif // GAMEBOARD_HH
