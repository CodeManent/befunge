#ifndef BEFUNGE_PARSER_H
#define BEFUNGE_PARSER_H

#include "board.h"

class Parser{
public:
	Parser();

	// Forwards the simulation
	int step();

	// Getters ans setters for the board
	void setBoard(Board&& board);
	void setBoard(const Board& board);
	const Board& getBoard() const;

private:
	Board board;

	class ProgramCounter{
	public:
		enum Direction{UP, DOWN, LEFT, RIGHT};
		ProgramCounter(size_t x=0, size_t y=0, Direction dir=RIGHT);
		ProgramCounter(const ProgramCounter& pc2);

		void forward(const Board& board);

		size_t x;
		size_t y;
		Direction dir;
	} pc;
};

#endif

