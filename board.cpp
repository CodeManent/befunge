#include "board.h"
#include <fstream>
#include <stdexcept>

using namespace std;

Board::Board():
	board(80, vector<char>(25, ' '))
{
}

/* Initializes the board with the Befunge script in the specified file.
 *
 * Reads at most board_limit_size characters (65536) one by one and every time
 * a line is filled, it's appended to the end of the board.
 */
Board::Board(const std::string path):
	board()
{
	// Open the file
	fstream infile(path);
	infile.exceptions();

	vector<char> line;
	size_t read = board_size_limit;

	// As we still have characters and laven't read much too many
	while(!infile.eof() && --read){
		// Get a char and push it in the line
		char ch = 0;
		infile.get(ch);
	
		switch(ch){
		case 10:
			// On the end of the ilne, add it to the end of the board
			board.push_back(line);
			line.clear();
			break;

		case '\r':
			continue;

		default:
			line.push_back(ch);
		}
	}

	// If we read too much, probably it's not a valid script file
	if(!read){
		throw std::runtime_error("Board(): File read size limit reached");
	}

	// Because the last line may not be followed by a newline
	if(line.size()){
		board.push_back(line);
	}
}

Board::~Board()
{
}

char& Board::operator()(const size_t x, const size_t y)
{
	return board.at(x).at(y);
}

char Board::operator()(const size_t x, const size_t y) const
{
	return board.at(x).at(y);
}

ostream& Board::operator<<(ostream& os) const
{
	for(auto line : board){
		for(auto ch : line){
			os << ch;
		}
		os << endl;
	}
	return os;
}

ostream& operator<<(ostream& os, const Board& board)
{
	return board << os;
}

