#ifndef BEFUNGE_STACK_H
#define BEFUNGE_STACK_H

#include <stack>
#include <utility>
#include <iostream>

class Stack{
public:
	Stack()
		:stack()
	{
	}

	Stack(const Stack& st)
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

	int top(){
		if(stack.empty())
			return 0;

		return stack.top();
	}

	friend std::ostream& operator<<(std::ostream& os, const Stack& st){
		Stack st2(st);

		while(!st2.stack.empty()){
			int v = st2.pop();

			if(isprint(v)){
				std::cout << " " << (char)v;
			}
			else{
				std::cout << " " << v;
			}
		}
		
		return os;
	}


private:
	std::stack<int> stack;
};

#endif

