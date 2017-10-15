CC=g++
CC_FLAGS=-O2 -Wall -std=c++11
BIN=./bin

all: prep build clearafter

prep:
	mkdir -p $(BIN)

build: main.o graph.o inputter.o
	$(CC) $(BIN)/* -o main $(CC_FLAGS)

main.o: graph.o inputter.o
	$(CC) -c main.cc -o $(BIN)/main.o $(CC_FLAGS)

graph.o:
	$(CC) -c graph.cc -o $(BIN)/graph.o $(CC_FLAGS)

inputter.o:
	$(CC) -c inputter.cc -o $(BIN)/inputter.o $(CC_FLAGS)
	

clearafter:
	rm -rf $(BIN)/*.o
	rm -rf $(BIN)/*~

clean: clearafter
	rm -f main
