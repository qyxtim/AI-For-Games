# Understanding 2048 Code

## Implementation of 2048

Implementation of 2048 is split into four files:

- `2048.cpp` provides the human-played version of 2048 (UI)
- `2048ai.cpp` provides an AI version of 2048 (UI)
- `2048grid.cpp` provides basic structure of 2048
  - `grid` that stores the value of blocks
  - `up`, `left`, `down`, `right` method
  - `score` method, serving as an utility function for AI
  - `structure`, used to output the grid
- `ai.cpp` provides an implementation of 2048AI
- `ui.cpp` provides an implementation of the UI of 2048.
  - It allows two modes: manual or AI.
  - To activate manual mode, you can use: `./ui`.
  - To start AI mode, you need to add the `-a` flag: `./ui -a`. In this mode, you have no control and can only see how the AI moves.

For AI, 2048 AI uses Monte Carlo Tree Search, for more information you can [click here](https://www.geeksforgeeks.org/ml-monte-carlo-tree-search-mcts/).

## UI

To compile the UI, you can use the following `cmake` configuration:

<img src="https://raw.githubusercontent.com/qyxtim/AI-For-Games/main/2048/assets/21.png" width=50% height=50%>

```cmake
cmake_minimum_required(VERSION 3.7)
project(Sudoku)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)
set(SOURCE_FILES ui.cpp ai.cpp 2048grid.cpp)
add_executable(ui ${SOURCE_FILES})

target_link_libraries(ui ${OpenCV_LIBS})
```