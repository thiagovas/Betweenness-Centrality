CC=g++
CC_FLAGS=-O2 -Wall -std=c++11
BIN=./bin

all: prep build clearafter

prep: clean
	mkdir -p $(BIN)

build: main.o graph.o inputter.o
	$(CC) $(BIN)/* -o $(BIN)/main $(CC_FLAGS)

main.o: graph.o inputter.o
	$(CC) -c src/main.cc -o $(BIN)/main.o $(CC_FLAGS)

graph.o:
	$(CC) -c src/graph.cc -o $(BIN)/graph.o $(CC_FLAGS)

inputter.o:
	$(CC) -c src/inputter.cc -o $(BIN)/inputter.o $(CC_FLAGS)

clearafter:
	rm -rf $(BIN)/*.o
	rm -rf $(BIN)/*~

clean: clearafter
	rm -f main
	rm -f $(BIN)/main
