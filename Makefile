Program: Program.o
	g++ Program.o -o Program -lncurses

clean:
	rm -f Program *~ core *.o

brun: Program.o
	g++ Program.o -o Program -lncurses
	./Program

Program.o: Program.cpp
	g++ -g Program.cpp -c

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