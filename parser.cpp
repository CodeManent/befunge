#include "parser.h"

Parser::Parser()
	:board()
	,pc(0, 0)
{
}

//Returns false on end symbol
int Parser::step()
{
	// TODO: fill method
	
	return false;
}


void Parser::setBoard(Board&& board)
{
	this->board = board;
}

void Parser::setBoard(const Board& board)
{
	this->board = board;
}

const Board& Parser::getBoard() const
{
	return board;
}

Parser::ProgramCounter::ProgramCounter(size_t x, size_t y, Direction dir)
	:x(x)
	,y(y)
	,dir(dir)
{
}


Parser::ProgramCounter::ProgramCounter(const Parser::ProgramCounter &pc2)
	:x(pc2.x)
	,y(pc2.y)
	,dir(pc2.dir)
{
}

