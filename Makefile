all:
	c++ -std=c++17 -Wall -pedantic -shared -fPIC shared_functions.cpp -o shared_function.so
	c++ -std=c++17 -Wall -pedantic -ldl main.cpp -o main.out

clean:
	rm *.so *.out
