# 8-Puzzle A\* Logic: Detailed Line-by-Line Explanation

This document breaks down the logic of each function in the A\* implementation for an 8-Puzzle solver.

---

### 1. The Heuristic: `get_manhattan_distance`

This function "guesses" how far we are from the goal state.

- **`for i in range(1, 9):`** Loops through tiles 1 to 8 (we ignore the blank space `0` because moving other tiles is what actually counts).
- **`state.index(i)`**: Finds the current position of tile `i` in the 1D list.
- **`goal.index(i)`**: Finds where tile `i` _should_ be in the final goal configuration.
- **`idx // 3` and `idx % 3`**: Converts the flat index (0-8) into Row and Column coordinates.
  - `// 3` gives the row (quotient).
  - `% 3` gives the column (remainder).
- **`abs(...) + abs(...)`**: Calculates the Manhattan Distance—the total horizontal and vertical steps a tile must move to reach its target.

---

### 2. The Movement: `get_neighbors`

This function finds all possible board states reachable from the current one.

- **`blank_idx = state.index(0)`**: Locates the position of the empty space (represented by `0`).
- **`moves = [(-1, 0), (1, 0), (0, -1), (0, 1)]`**: Defines the possible moves for the blank space: Up, Down, Left, and Right.
- **`if 0 <= nr < 3 and 0 <= nc < 3:`**: A boundary check to ensure the blank space doesn't move "off the board" (outside the $3 \times 3$ grid).
- **`list(state)`**: Converts the board from a **Tuple** to a **List**. Tuples are "immutable" (cannot be changed), so we must convert to a list to swap tile positions.
- **`neighbor_list[blank_idx], neighbor_list[target_idx] = ...`**: A standard Python swap to move the blank space to its new position.
- **`tuple(neighbor_list)`**: Converts the board back into a Tuple so it can be stored in the **Closed List** (sets require immutable elements).

---

### 3. The Brain: `solve_8_puzzle` (A\* Algorithm)

This is the core logic where the **Open** and **Closed** lists manage the search.

- **`open_list = []`**: Our Priority Queue. It stores nodes that are discovered but not yet explored.
- **`heapq.heappush(..., (f, g, state))`**: Adds the starting state to the Open List. By storing it as a tuple starting with `f`, the heap always ensures the state with the lowest total cost is at the top.
- **`closed_list = set()`**: Our "Done" list. It tracks every state we have already fully explored to prevent infinite loops.
- **`parent_map = {start: None}`**: A dictionary acting as "breadcrumbs." It maps every state to its "parent" state so we can reconstruct the final path.
- **`while open_list:`**: Continues the search as long as there are states left to explore.
- **`f, g, current = heapq.heappop(open_list)`**: Picks the "best" current state (the one with the lowest $f$ score).
- **`if current == goal:`**: The Goal Test. If we match the target, we stop the search.
- **`new_f = g + 1 + h`**: Calculates the cost for a neighbor.
  - `g + 1` is the cost to reach the neighbor (one more move).
  - `h` is the Manhattan "guess" for the remaining distance.

---

### 4. Retracing Steps: `reconstruct_path`

Once the goal is found, this function builds the step-by-step solution.

- **`while current is not None:`**: Looks at the `parent_map` and follows the link from the Goal state back to the Start state.
- **`path[::-1]`**: Reverses the list so the final output displays the moves from Start $\rightarrow$ Goal.

---

### 5. Display: `print_board`

- **`state[i], state[i+1], state[i+2]`**: Grabs three elements at a time from the 1D tuple and prints them on a single line to visualize the $3 \times 3$ grid.
