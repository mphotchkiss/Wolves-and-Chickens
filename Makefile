CC = g++ -std=c++11

main: main.o gameState.o
	$(CC) -o main main.o gameState.o
main.o: main.cpp
	$(CC) -c main.cpp
gameState.o: gameState.cpp
	$(CC) -c gameState.cpp