/* Checkers (for one player)
 *
 * Program author
 * Name: Marko *********
 * Student number: **********
 * UserID: ************
 * E-Mail: m************@tuni.fi
 *
 * */

#include "gameboard.hh"
#include <iostream>
#include <vector>

GameBoard::GameBoard(char const& piece):
piece_(piece)
{
fill_board();
}

void GameBoard::print() const
{
    // Printing upper border
    print_line(LEFT_COLUMN_WIDTH + 1 + 2 * SIZE + 1, '=');

    // Printing title row
    std::cout << "|   | ";
    for(unsigned int i = 0; i < SIZE; ++i)
    {
        std::cout << i + 1 << " ";
    }
    std::cout << "|" << std::endl;

    // Printing line after the title row
    print_line(LEFT_COLUMN_WIDTH + 1 + 2 * SIZE + 1, '-');

    // Printing the actual content of the gameboard
    for(unsigned int i = 0; i < SIZE; ++i)
    {
        std::cout << "| " << i + 1 << " | ";
        for(unsigned int j = 0; j < SIZE; ++j)
        {
            // Prints the board's elements from the matrix with vector indexing
            std::cout << board_[i][j] << " ";
        }
        std::cout << "|" << std::endl;
    }

    // Printing lower border
    print_line(LEFT_COLUMN_WIDTH + 1 + 2 * SIZE + 1, '=');
}

void GameBoard::print_line(unsigned int length, char fill_character) const
{
    for(unsigned int i = 0; i < length; ++i)
    {
        std::cout << fill_character;
    }
    std::cout << std::endl;
}

void GameBoard::move(const std::vector<unsigned int>& moves) {
    /* Moves a piece on the gameboard if a move is considered valid,
     * the method is called through the first validator in main file,
     * the move-method then further checks if the move is legit e.g. diagonal
     * and if necessary, removes game pieces from the board. Coordinates are
     * assigned into int-type vars just to remove jank with the vector indexing.
     * Messy conditionals here, didn't study use cases of switch yet... */

    int start_x = moves[1]-1;
    int end_x = moves[3]-1;
    int start_y = moves[0]-1;
    int end_y = moves[2]-1;
    int between_x = start_x;
    int between_y = start_y;

    // Making sure there's a piece to move and empty spot at the destination
    if (board_[start_x][start_y] == piece_ && board_[end_x][end_y] == ' ') {

        if (start_x - end_x == 2 or start_x - end_x == -2) {
            if (start_y - end_y == 2 or start_y - end_y == -2) {
                // Assign matrix indices for the tile between start and end
                if (start_x > end_x) {
                    between_x--;
                } else {
                    between_x++;
                }
                if (start_y > end_y) {
                    between_y--;
                } else {
                    between_y++;
                }

                // Final check to see if there's a piece between two points.
                if (board_[between_x][between_y] == piece_) {
                    board_[between_x][between_y] = ' ';
                    board_[start_x][start_y] = ' ';
                    board_[end_x][end_y] = piece_;

                    pieces_--;
                    moves_++;

                    print();
                    return;
                }
            }
        }
    }
    std::cout << "Cannot move from start point to destination point."
    << std::endl;
}

void GameBoard::fill_board() {
    /* Called only once in the constructor, fills the board with game pieces
     * while accounting for the empty space in the middle */

    for (unsigned int i=0; i<=SIZE; i++) {
        std::vector<char> row;
        for (unsigned int j=0; j<=SIZE; j++) {
            // Conditional check for empty 4x4 in the middle
            // Due to how indexing works the coordinates are treated as -1
            if (i > 1 and i < 6) {
                if (j > 1 and j < 6) {
                    row.push_back(' ');
                    continue;
                }
            }
            row.push_back(piece_);

            // Add pieces to the total count if one is placed in the vector.
            if (i < SIZE && j < SIZE) {
                pieces_++;
            }

        }
        board_.push_back(row);
    }
}

bool GameBoard::is_game_over() {
    // Runs in the main loop as another ending condition aside of 'Q' input.
    if (pieces_ <= 1) {
        return true;
    }
    return false;
}

void GameBoard::quit_game() const{
    // The method called after user inputs 'Q' or 'q' to display score.

    std::cout << moves_ << " move(s) made." << std::endl;
    std::cout << pieces_ << " piece(s) left." << std::endl;
}


