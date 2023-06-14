
//By Abbas and Melisa

#include <iostream>
using namespace std;
bool isWon(char, char[][3]);
bool isDraw(char[][3]);
void displayBoard(char[][3]);
void makeAMove(char[][3], char);


//If the root folder contains all 3 cpp files, to run, we must temporally change the main() of two files that we do not want to run.
//For example, we would change main() of TikTakToe to Amain(), and creditCard to Bmain(), so there is one valid main() for dictionary.
//Otherwise, as there are multiple cpp files in this folder with main(), programs won't run.
//Run the cpp files we want to run, repeat the step and run the other programs.
//Ignore if there are no issues with multiple main() errors, or know a better way around this, or running files separately.

int mainA() {
	//
	// PLEASE DO NOT CHANGE main()
	//
	char board[3][3] = { { ' ', ' ', ' ' },{ ' ', ' ', ' ' },{ ' ', ' ', ' ' } };
	displayBoard(board);
	while (true) {
		// The first player makes a move
		makeAMove(board, 'X');
		displayBoard(board);
		if (isWon('X', board)) {
			cout << "X player won" << endl;
			exit(0);
		}
		else if (isDraw(board)) {
			cout << "No winner" << endl;
			exit(0);
		}
		// The second player makes a move
		makeAMove(board, 'O');
		displayBoard(board);
		if (isWon('O', board)) {
			cout << "O player won" << endl;
			exit(0);
		}
		else if (isDraw(board)) {
			cout << "No winner" << endl;
			exit(0);
		}
	}
	return 0;
}
bool isWon(char curr_player, char board[][3])
{

	for (int i = 0; i < 3; i++)
	{
		if (board[i][0] == curr_player)
		{
			if (board[i][0] == board[i][1]
				&& board[i][0] == board[i][2])
			{
				return true;
			}
		}

		if (board[0][i] == curr_player)
		{

			if (board[0][i] == board[1][i]
				&& board[0][i] == board[2][i])
			{
				return true;
			}
		}
	}

	if (board[1][1] == curr_player)
	{

		if (board[0][0] == board[1][1]
			&& board[0][0] == board[2][2])
		{

			return true;
		}

		if (board[0][2] == board[1][1]
			&& board[0][2] == board[2][0])
		{

			return true;
		}
	}

	if (board[0][2] == curr_player)
	{
		if (board[0][2] == board[1][1]
			&& board[0][2] == board[2][0])
		{
			return true;
		}
	}

	return false;
}

bool isDraw(char board[][3])
{

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (board[i][j] == ' ')
			{
				return false;
			}
		}
	}
	return true;
}

void displayBoard(char board[][3])
{
	cout << "-------------" << endl;
	for (int i = 0; i < 3; i++)
	{
		cout << "|";
		for (int j = 0; j < 3; j++)
		{
			cout << " " << board[i][j] << " |";
		}
		cout << endl;
	}
	cout << "-------------" << endl;
}

void makeAMove(char board[][3], char curr_player)
{

	int row_num;
	int col_num;

	cout << "Enter a row (0, 1, 2) for player "
		<< curr_player << " : ";
	cin >> row_num;
	cout << "Enter a column (0, 1, 2) for player "
		<< curr_player << " : ";
	cin >> col_num;

	while (board[row_num][col_num] != ' ')
	{
		cout << "The cell is already occupied."
			<< " Try a different cell" << endl;
		cout << "Enter a row (0, 1, 2) for player "
			<< curr_player << " : ";
		cin >> row_num;
		cout << "Enter a column (0, 1, 2) for player "
			<< curr_player << " : ";
		cin >> col_num;
	}

	board[row_num][col_num] = curr_player;
}
