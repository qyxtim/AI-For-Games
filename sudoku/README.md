# Understanding Sudoku Code

## Implementation of Sudoku

Implementation of Sudoku is split into four files:

- `generate.cpp`, used to generate a sudoku
- `main.cpp` provides an AI version of Sudoku (UI)
- `board.cpp` provides the basic structure of Sudoku
  - `grid` that stores the value of blocks
  - `output`, used to output the grid
- `ai.cpp` provides an implementation of Sudoku AI.

For AI, Sudoku AI uses brute force search, which means at some extreme cases, it may take a long time to solve sudoku.

## How to generate Sudoku

`generate.cpp` uses a clever way to generate sudoku. It takes the following step:

- It first randomly fills in $maxLevel$ Number of blocks
- Then, it uses AI to check if the sudoku is solvable
  - if it is, output the sudoku
  - if it is not, go back to step one
