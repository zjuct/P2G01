CPP_FLAGS := -O2 -g 
BIN_DIR := build

all : ordinary-fibo ordinary-pair ordinary-left modified-fibo modified-pair modified-binary

ordinary-fibo: code/dijkstra-test.cpp code/ordinary-dijkstra.hpp code/fiboHeap.hpp 
	g++ -o $(BIN_DIR)/$@ $(CPP_FLAGS) -DFIBO $< 

ordinary-pair: code/dijkstra-test.cpp code/ordinary-dijkstra.hpp code/pairHeap.hpp 
	g++ -o $(BIN_DIR)/$@ $(CPP_FLAGS) -DPAIR $< 

ordinary-left: code/dijkstra-test.cpp code/ordinary-dijkstra.hpp code/leftHeap.hpp 
	g++ -o $(BIN_DIR)/$@ $(CPP_FLAGS) -DLEFT $< 

modified-fibo: code/dijkstra-test.cpp code/modified-dijkstra.hpp code/fiboHeap.hpp 
	g++ -o $(BIN_DIR)/$@ $(CPP_FLAGS) -DFIBO -DMODIFY $< 

modified-pair: code/dijkstra-test.cpp code/modified-dijkstra.hpp code/pairHeap.hpp 
	g++ -o $(BIN_DIR)/$@ $(CPP_FLAGS) -DPAIR -DMODIFY $< 

modified-binary: code/dijkstra-test.cpp code/modified-dijkstra.hpp code/binaryHeap.hpp 
	g++ -o $(BIN_DIR)/$@ $(CPP_FLAGS) -DBINARY -DMODIFY $< 

clean : 
	rm -rf build/*