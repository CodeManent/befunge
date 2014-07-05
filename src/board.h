#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <vector>
#include <iostream>

class Board{
public:
	//Creates an empty 80x25 board
	Board();

	//Reads the board from the file
	Board(const std::string &path);

	//Destructor
	~Board();

	// Maybe I should make actual get/set methods
	// Returns a referene to the data in the board
	char& operator()(const size_t x, const size_t y);
	char operator()(const size_t x, const size_t y) const;

	size_t width() const;
	size_t height() const;

	std::ostream& operator<<(std::ostream& os) const;

private:
	void fill();

	std::vector<std::vector<char>> board;
	static const size_t board_size_limit = 65535;
};

// Function that prints the bpard
std::ostream& operator<<(std::ostream& os, const Board& board);

#endif

