Program: Program.o Block.o
	g++ -std=c++11 -g Program.o Block.o -o Program -lncurses

clean:
	rm -f Program *~ core *.o

brun: Program.o Block.o
	g++ -std=c++11 -g Program.o Block.o -o Program -lncurses
	./Program

Program.o: Program.cpp Block.h
	g++ -std=c++11 -g -c Program.cpp

Block.o: Block.cpp Block.h
	g++ -std=c++11 -g -c Block.cpp
# Program: Program.o heap.o Pokedex.o
# 	g++ Program.o heap.o Pokedex.o -o Program -lncurses

# clean:
# 	rm -f Program *~ core *.o seeds.txt

# brun: Program.o heap.o Pokedex.o
# 	g++ Program.o heap.o Pokedex.o -o Program -lncurses
# 	./Program

# Program.o: Program.cpp 
# 	g++ -Wall -Werror -g Program.cpp -c 

# heap.o: heap.cpp heap.h
# 	g++ -Wall -Werror -g heap.cpp -c

# Pokedex.o: Pokedex.cpp Pokedex.h
# 	g++ -Wall -Werror -g Pokedex.cpp -c