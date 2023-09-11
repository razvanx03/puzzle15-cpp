#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <string>

std::vector<std::vector<int>> board = {
	{1,2,3,4},
	{5,6,7,8},
	{9,10,11,12},
	{13,14,15,0}
};
int moves = 0;

void printBoard() {
	system("cls");
	for (auto& row : board)
	{
		for (auto& value : row)
		{
			if (value == 0) {
				std::cout << ' ' << "   ";
			}
			else if (value < 10) {
				std::cout << value << "   ";
			}
			else {
				std::cout << value << "  ";
			}
		}
		std::cout << '\n';
	}
	std::cout << "\nMoves: " << moves << "\n\n";
}

void shuffleBoard() {

	std::vector<int> flat_board; // convert 2d vector in 1d

	for (int i = 0; i < board.size(); i++)
	{
		for (int j = 0; j < board[0].size(); j++)
		{
			flat_board.push_back(board[i][j]);
		}
	}

	std::random_device rd; // generator
	std::mt19937 g(rd());
	std::shuffle(flat_board.begin(), flat_board.end(), g);

	int i = 0;
	for (auto& row : board) { // reconstruct 1d in 2d
		for (auto& value : row) {
			value = flat_board[i];
			i++;
		}
	}
}

void clearBuffer() {
	char discard;
	while (std::cin.get(discard) && discard != '\n' || std::cin.fail()); // clear buffer
}

void clearCin() {
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout << "Invalid input, stick to the rules of the game: ";
}

char checkInput() {

	std::cout << "Enter move (wasdq): ";
	char input;
	std::cin >> input;

	while (std::cin.fail() || (input != 'w' && input != 'a' && input != 's' && input != 'd' && input != 'q')) {
		clearCin();
		std::cin >> input;
	}

	clearBuffer();

	return input;
}

bool checkWinCon() {
	int counter = 1;
	for (int i = 0; i < board.size(); i++)
	{
		for (int j = 0; j < board[i].size(); j++)
		{
			if (i != 3 || j != 3) {
				if (board[i][j] != counter) {
					return false;
				}
				counter++;
			}
		}
	}
	std::cout << "\n\tCongrats!\n";
	return true;
}

void playGame() {

	while (!checkWinCon())
	{
		char input = checkInput();
		if (input == 'q') {
			std::cout << "\n\tBye\n";
			return;
		}

		int secondBreak = false;
		for (int i = 0; i < board.size() && secondBreak == false; i++)
		{
			for (int j = 0; j < board[0].size(); j++)
			{
				if (board[i][j] == 0) {
					if (input == 'w') {
						if (i + 1 >= board.size()) {
							secondBreak = true;
							break;
						}
						std::swap(board[i][j], board[i + 1][j]);
					}
					else if (input == 'a') {
						if (j + 1 >= board[0].size()) {
							secondBreak = true;
							break;
						}
						std::swap(board[i][j], board[i][j + 1]);
					}
					else if (input == 's') {
						if (i - 1 < 0) {
							secondBreak = true;
							break;
						}
						std::swap(board[i][j], board[i - 1][j]);
					}
					else { //d
						if (j - 1 < 0) {
							secondBreak = true;
							break;
						}
						std::swap(board[i][j], board[i][j - 1]);
					}
					moves++;
					secondBreak = true;
					break;
				}
			}
		}
		printBoard();
	}
}


int main() {

	shuffleBoard();
	printBoard();
	playGame();

	// board - cols
	// board[0] - rows
	return 0;
}