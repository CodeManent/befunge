#include "parser.h"
#include <stdexcept>
#include <sstream>
#include <iostream>
#include <random>

Parser::Parser()
	:board()
	,stringMode(false)
	,pc(0, 0)
	,random_engine(std::random_device()())
	,dist(0, 3)
{
}

//Returns false on end symbol
int Parser::step()
{
	int v1 = 0;
	int v2 = 0;
	char ch = 0;

	char op = ((const Board)board)(pc.x, pc.y);
	// std::cout << pc << ' ' << op << " stack :  "  << stack << std::endl;;

	if(stringMode && op != '"'){
		stack.push(op);
		goto skipDecoder;
	}


	switch(op){
	case ' ':
		//nop
		break;

	case '@':
		return false;
	
	case '+':
		stack.push(stack.pop() + stack.pop());
		break;

	case '-':
		v2 = stack.pop();
		v1 = stack.pop();
		stack.push(v1 - v2);
		break;

	case '*':
		stack.push(stack.pop() * stack.pop());
		break;

	case '/':
		v2 = stack.pop();
		v1 = stack.pop();
		if(v2 == 0)
			throw std::runtime_error("Division with 0");
		stack.push(v1/v2);
		break;

	case '%':
		v2 = stack.pop();
		v1 = stack.pop();
		stack.push(v1 % v2);
		break;

	case '!':
		stack.push(!stack.pop());
		break;

	case '`': // Greater
		v2 = stack.pop();
		v1 = stack.pop();
		stack.push(v1 > v2);
		break;

	case '>': // Right
		pc.setDirection(ProgramCounter::RIGHT);
		break;

	case '<':
		pc.setDirection(ProgramCounter::LEFT);
		break;

	case '^':
		pc.setDirection(ProgramCounter::UP);
		break;

	case 'v':
		pc.setDirection(ProgramCounter::DOWN);
		break;

	case '_':
		if(stack.pop()){
			pc.setDirection(ProgramCounter::LEFT);
		}
		else{
			pc.setDirection(ProgramCounter::RIGHT);
		}
		break;

	case '|':
		if(stack.pop()){
			pc.setDirection(ProgramCounter::UP);
		}
		else{
			pc.setDirection(ProgramCounter::DOWN);
		}
		break;

	case '"':
		stringMode = !stringMode;
		break;

	case ':': // dup
		stack.push(stack.top());
		break;

	case '\\': // swap
		{
			auto v2 = stack.pop();
			auto v1 = stack.pop();

			stack.push(v2);
			stack.push(v1);
		}
		break;

	case '$': // pop
		stack.pop();
		break;

	case '.':
		std::cout << (int) stack.pop() << ' ';
		break;

	case ',':
		std::cout << (char) stack.pop();
		break;

	case '#': // bridge
		pc.forward(board);
		break;
	
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		stack.push(op - '0');
		break;

	case 'g':
		v2 = stack.pop();
		v1 = stack.pop();
		stack.push(((const Board)board)(v1, v2));
		break;

	case 'p':
		v2 = stack.pop();
		v1 = stack.pop();

		board(v1, v2) = stack.pop();
		break;

	//TODO: chech I/O
	case '&':
		std::cin >> v1;
		stack.push(v1);
		break;

	case '~':
		std::cin >> ch;
		stack.push(ch);
		break;
		
	case '?':
		{
			auto selection = dist(random_engine);
			switch(selection){
				case 0: pc.setDirection(ProgramCounter::UP); break;
				case 1: pc.setDirection(ProgramCounter::DOWN); break;
				case 2: pc.setDirection(ProgramCounter::LEFT); break;
				case 3: pc.setDirection(ProgramCounter::RIGHT); break;
			}
		}
		break;

	default:
	{
		std::stringstream ss;
		
		ss << "Unrecognised operation"
			<< " at (" << pc.x << ", " << pc.y << ")"
			<< " \"" << (char)op << "\" (" << (int)op << ")"
			<< std::endl;

		std::cerr << ss.str() << std::endl;
		// throw std::runtime_error(ss.str());
	}
	}

skipDecoder:

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
			y = board.height() - 1;
		}
		else{
			--y;
		}
		break;

	case DOWN:
		if(y == board.height() - 1){
			y = 0;
		}
		else{
			y++;
		}
		break;

	case LEFT:
		if(x == 0){
			x = board.width() - 1;
		}
		else{
			--x;
		}
		break;

	case RIGHT:
		if(x == board.width() - 1){
			x = 0;
		}
		else{
			++x;
		}
	}
}

void Parser::ProgramCounter::setDirection(Direction d)
{
	dir = d;
}
