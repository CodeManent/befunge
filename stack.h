#ifndef BEFUNGE_STACK_H
#define BEFUNGE_STACK_H

#include <stack>
#include <utility>

class Stack{
public:
	Stack()
		:stack()
	{
	}

	Stack(Stack& st)
		:stack(st.stack)
	{
	}

	Stack(Stack&& st)
		:stack(std::move(st.stack))
	{
	}

	void push(int value){
		stack.push(value);
	}

	int pop(){
		int ret = 0;
		
		if(!stack.empty()){
			ret = stack.top();
			stack.pop();
		}

		return ret;
	}

private:
	std::stack<int> stack;
};

#endif

