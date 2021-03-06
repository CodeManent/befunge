#ifndef BEFUNGE_PARSER_H
#define BEFUNGE_PARSER_H

#include "board.h"
#include "stack.h"
#include <random>

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
	Stack stack;
	bool stringMode;

	class ProgramCounter{
	public:
		enum Direction{UP, DOWN, LEFT, RIGHT};
		ProgramCounter(size_t x=0, size_t y=0, Direction dir=RIGHT);
		ProgramCounter(const ProgramCounter& pc2);

		void forward(const Board& board);
		void setDirection(Direction d);

		size_t x;
		size_t y;
		Direction dir;

		friend std::ostream& operator<< (std::ostream& os, const ProgramCounter &pc){
			os << '(' << pc.x << ", " << pc.y << ')';
			return os;
		}
	} pc;

	std::mt19937 random_engine;
	std::uniform_int_distribution<> dist;
};

#endif

