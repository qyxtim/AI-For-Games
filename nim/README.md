# Understanding Nim

> **Nim** is a [mathematical](https://en.wikipedia.org/wiki/Mathematical_game) [game of strategy](https://en.wikipedia.org/wiki/Game_of_strategy) in which two players take turns removing (or "nimming") objects from distinct heaps or piles. On each turn, a player must remove at least one object, and may remove any number of objects provided they all come from the same heap or pile. Depending on the version being played, the goal of the game is either to avoid taking the last object or to take the last object.
>
> --Wikipaedia

## Implementation of Nim

Implementation of Nim is split into four files:

- `human.cpp` provides the human-played version of Nim (UI)
- `main.cpp` provides an AI version of Nim (UI)
- `board.cpp` provides the basic structure of Nim
  - `piles`: a one dimensional array that stores the number of movable stuffs in each pile
  - `remove(const Pair&)` method
    - remove `Pair.y` numbers of stuff from `piles[Pair.x]`
  - `output`, used to output the piles
- `ai.cpp` provides an implementation of Nim AI.

For AI, Nim AI uses reinforcement learning, more specifically q-learning. It uses a `<map>` to store the knowledge gathered by playing the game with itself.

The knowledge of this game is represented by this form:

```cpp
struct Pair{
  int x,y;
};

struct Knowledge{
  std::vector<int> piles;
  Pair nextAction;
};
```

Every time when the AI plays against itself, it will update the q-value for every corresponding knowledge by using the formula below:

$Q_{knowledge} = Q_{knowledge} + \alpha \times (reward + FutureEstimate - Q_{knowledge})$

In this formula, the $reward$ is $-1, 0, 1$. $1$ is given when at some states,  action leads to final success; $-1$ is given when at some states, action leads to failure. $\alpha$ is the learning rate of the AI.

For $FutureEstimate$, we get it by following the rule below:

Consider an arbitrary three-states pair: $State1, State2, State3$ such that $State1$ --> $State2$ --> $State3$. Then, $State1$'s Future Estimate is the greatest q-value in $State3$, which means the greatest $(piles, nextAction)$ pair for piles in $State3$.

If there is no $State4$ after $State3$, then $State2$'s Future Estimate is also based on $State3$. This can only happen when $State3$ is an empty pile, which can only happen when the game ends.

