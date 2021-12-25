all: sudokuAI generate

sudokuAI: main.cpp board.cpp ai.cpp
	g++ -std=c++17 -O2 main.cpp board.cpp ai.cpp -o sudokuAI

generate: generate.cpp board.cpp ai.cpp
	g++ -std=c++17 -O2 generate.cpp board.cpp ai.cpp -o generate