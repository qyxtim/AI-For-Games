# Understanding Demining Code

## Implementation of Demining

Implementation of Demining is split into four files:

- `human.cpp` provides the human-played version of Demining (UI)
- `main.cpp` provides an AI version of Demining (UI)
- `board.cpp` provides the basic structure of Demining
  - `grid` that stores the value of blocks
  - `click`, `tag`, `reset` method
    - after "tagging", the corresponding block becomes "unclickable". You can reset it back to normal block by using `reset` method
  - `output`, used to output the grid
  - `finaloutput`, used to output the grid after the game ends
- `ai.cpp` provides an implementation of Demining AI.
- `ui.cpp` provides an implementation of the UI of the Demining.

For AI, Demining AI uses knowledge-based AI. It uses the following idea to represent knowledge, and make induction:

```cpp
struct GridLocation{
  int x, y;
};

struct Knowledge{
  set<GridLocation> locations;
  int numberOfMines;
};
```

The idea is that if there are two pieces of knowledge $k_1$ and $k_2$ such that $k_1 \subset k_2$. Then, we can use our code to generate a new piece of knowledge $k_3$ such that $k_3.locations = k2.locations - k1.locations$ and $k3.numberOfMines = k2.numberOfMines - k1.numberOfMines$.

Since it is based on knowledge, the AI sometimes can only take random move because it may not have enough knowledge about the game, which means the AI will probabily lose the game.

## UI

<img src="https://raw.githubusercontent.com/qyxtim/AI-For-Games/main/demining/assets/d1.png" width=50% height=50%>

To compile the UI, you can use the following `cmake` configuration:

```cmake
cmake_minimum_required(VERSION 3.7)
project(Demining)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)
set(SOURCE_FILES ui.cpp ai.cpp board.cpp)
add_executable(ui ${SOURCE_FILES})

target_link_libraries(ui ${OpenCV_LIBS})
```