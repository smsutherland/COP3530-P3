all: main
	
main: main.o avl.hpp bst.hpp tree.hpp Bucket.hpp
	g++ -Wall -Werror -std=c++14 main.o avl.hpp bst.hpp tree.hpp Bucket.hpp  -o main

main.o: main.cpp
	g++ -Wall -Werror -std=c++14 -O -c main.cpp


clean:
	rm -f *.o main *.gch
