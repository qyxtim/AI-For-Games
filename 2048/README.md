# Understanding 2048 Code
Implementation of 2048 is split into four files:

- `2048.cpp` provides the human-played version of 2048 (UI)
- `2048ai.cpp` provides an AI version of 2048 (UI)
- `2048grid.cpp` provides basic structure of 2048
  - `grid` that stores the value of blocks
  - `up`, `left`, `down`, `right` method
  - `score` method, serving as an utility function for AI
  - `structure`, used to output the grid
- `ai.cpp` provides an implementation of 2048AI

For AI, 2048 AI uses Monte Carlo Tree Search, for more information you can [click here](https://www.geeksforgeeks.org/ml-monte-carlo-tree-search-mcts/).

