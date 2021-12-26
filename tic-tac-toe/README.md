# Understanding tic-tac-toe Code

## Implementation of tic-tac-toe

Implementation of  tic-tac-toe is split into four files:

- ` human.cpp` provides the human-played version of  tic-tac-toe (UI)
- ` main.cpp` provides an AI version of  tic-tac-toe (UI)
- ` board.cpp` provides the basic structure of  tic-tac-toe
  - `board` that stores the value of blocks
  - `move` method
  - `isEnd` method, indicating whether it is the end of the game
  - `winner` method, serving for telling who is the winner and used by AI.
  - `output`, used to output the grid
- `ui.cpp` provides an opencv implementation of the user interface of tic-tac-toe
  - It only includes the AI version of tic-tac-toe.
  - To compile the user interface, you must have the opencv library installed.
- `ai.cpp` provides an implementation of tic-tac-toe AI.

For AI, tic-tac-toe AI uses Minimax, for more information you can [click here](https://www.geeksforgeeks.org/minimax-algorithm-in-game-theory-set-1-introduction/).

## UI

<img src="https://raw.githubusercontent.com/qyxtim/AI-For-Games/main/tic-tac-toe/assets/t1.png" width=50% height=50%>

<img src="https://raw.githubusercontent.com/qyxtim/AI-For-Games/main/tic-tac-toe/assets/t2.png" width=50% height=50%>

To compile the UI, you can use the following `cmake` configuration:

```cmake
cmake_minimum_required(VERSION 3.7)
project(Sudoku)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)
set(SOURCE_FILES ui.cpp ai.cpp board.cpp)
add_executable(ui ${SOURCE_FILES})

target_link_libraries(ui ${OpenCV_LIBS})
```