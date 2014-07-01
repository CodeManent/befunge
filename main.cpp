#include <iostream>
#include <cstdlib>

#include "board.h"

int main(int argc, char* argv[]){
	using namespace std;

	if(argc != 2){
		cerr << "Befunge file must be the only parameter." << endl;
		return EXIT_FAILURE;
	}
	
	clog << "Loading board " << argv[1] << endl;
	Board b(argv[1]);

	cout << b << endl;

	return EXIT_SUCCESS;
}

