# Understanding 2048 Code
Implementation of 2048 is split into four files:

- `2048.cpp` provide human-played version of 2048 (UI)
- `2048ai.cpp` provide AI version of 2048 (UI)
- `2048grid.cpp` provide basic structure of 2048
  - `grid` that stores the value of blocks
  - `up`, `left`, `down`, `right` method
  - `score` method, serving as an utility function for AI
  - `structure`, used to output the grid
- `ai.cpp`, implementation of 2049AI

For AI, 2048 AI uses Monte Carlo Tree Search, for more information you can [click here](https://www.geeksforgeeks.org/ml-monte-carlo-tree-search-mcts/).

