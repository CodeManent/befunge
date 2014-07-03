#ifndef BEFUNGE_PARSER_H
#define BEFUNGE_PARSER_H

#include "board.h"

class Parser{
public:
	Parser();

	// Forwards the simulation
	void step();

	// Getters ans setters for the board
	void setBoard(Board&& board);
	void setBoard(const Board& board);
	const Board& getBoard() const;

private:
	Board board;

	class ProgramCounter{
		enum Direction{UP, DOWN, LEFT, RIGHT};
	public:
		ProgramCounter(size_t x=0, size_t y=0, Direction dir=RIGHT);
		ProgramCounter(const ProgramCounter& pc2);

		void forward();

	private:
		size_t x;
		size_t y;
		Direction dir;
	} pc;
};

#endif

