/* Checkers (for one player)
 *
 * Desc:
 *   This program implements a checkers game for one player. The size of
 * the gameboard is 8 x 8, and it will filled with empty spaces and
 * game pieces (character given by the user).
 *   At first, the gameboard is filled with pieces, but there is an
 * empty area of size 4 x 4 in the middle of the gameboard. The aim is to
 * remove pieces such that only one of them is left. A piece can be moved
 * diagonally over another piece, whereupon the piece that was skipped
 * will be removed.
 *   On each round, the user is asked for two points (four coordinates):
 * the piece to be moved and its target position. The program checks if
 * if the move is possible.
 *   The program terminates when there is only one piece left or if the
 * user gives a quitting command ('q' or 'Q'). In such case the program
 * prints the number of moves made and that of pieces left.
 *
 *
 * Notes about the program and it's implementation (if any):
 *
 * In my implementation I chose to omit std namespace explicitly
 * as a personal choice and future-proofing myself to avoid lazy
 * choices down the line.
 *
 * */

#include "gameboard.hh"
#include <iostream>
#include <string>
#include <vector>


void check_move(const std::vector<char> moves, GameBoard& checkers) {
    /* Checks the validity of a move, then makes GameBoard object method calls
     * if necessary to adjust game piece movement on board, SIZE constant
     * declared in header-file is being used for comparison */

    std::vector<unsigned int> valid_moves;

    /* Substracting ascii value of a char-type representing a number(0-9)
     * with the ascii value of char-type '0' gets the respective in int,
     * here I utilise a similar technique I did with encryption exercise */
    const unsigned int ascii_value_of_0 = static_cast<int>('0');

    for (auto move : moves) {
        for (unsigned int i = 1; i <= SIZE; i++) {
            if (move-ascii_value_of_0 == i) {
                valid_moves.push_back(i);
                break;
            }
        }
    }

    if (valid_moves.size() != 4) {
        std::cout << "Invalid start/destination point." << std::endl;
    } else {
        checkers.move(valid_moves);
    }
}

bool get_move(GameBoard& checkers)
{
    /* Reads user input for movement on gameboard inside main loop
     * Depending on the return value it will dictate the program exit
     * If the input is valid, it will check for movement validity
     *
     * Bad practice of black magic mixing cin and getline on purpose, but
     * I had a lot of overflow errors with cin in reading input, I didn't
     * want to mess further with string to char conversions in main function..
     * */


    std::cout << "Enter start point (x, y) and destination point (x, y),"
                 " or q to quit: ";
    std::vector<char> moves;

    std::string move_input;
    std::getline(std::cin, move_input);

    for (char move : move_input) {
        if (move == ' ') {
            continue;
        } if (move == 'q' or move == 'Q') {
            return false;
        } moves.push_back(move);
    }

    if (moves.size() == 4) {
        check_move(moves, checkers);
    } else {
        std::cout << "Invalid start/destination point." << std::endl;
    }

    return true;
}

int main()
{
    char piece;

    std::cout << "Enter piece character: ";
    std::cin >> piece;
    std::cin.clear();
    std::cin.ignore();

    GameBoard checkers = GameBoard(piece);

    checkers.print();

    while (true) {
        if (get_move(checkers) == false or checkers.is_game_over()) {
            break;
        }
    }
    checkers.quit_game();

    return 0;
}
