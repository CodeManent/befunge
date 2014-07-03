#include "parser.h"
#include <stdexcept>
#include <sstream>

Parser::Parser()
	:board()
	,pc(0, 0)
{
}

//Returns false on end symbol
int Parser::step()
{
	// TODO: fill method
	char op = board(pc.x, pc.y);

	switch(op){
	case ' ':
		//nop
		break;

	case '@':
		return false;

	default:
	{
		std::stringstream ss;
		
		ss << "Unrecognised operation "
			<< "\"" << op << "\" (" << (int)op << ")"
			<< " at (" << pc.x << ", " << pc.y << ")"
			<< std::endl;

		throw std::runtime_error(ss.str());
	}
	}

	pc.forward(board);

	return true;
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

void Parser::ProgramCounter::forward(const Board& board)
{
	switch(dir){
	case UP:
		if(y == 0){
			y = board.height();
		}
		else{
			--y;
		}
		break;

	case DOWN:
		if(y == board.height()){
			y = 0;
		}
		else{
			y++;
		}
		break;

	case LEFT:
		if(x == 0){
			x = board.width();
		}
		else{
			--x;
		}
		break;

	case RIGHT:
		if(x == board.width()){
			x = 0;
		}
		else{
			++x;
		}
	}
}
