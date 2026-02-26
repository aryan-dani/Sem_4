# Traveling Salesperson Problem (TSP): Detailed Line-by-Line Explanation

This document breaks down the logic of each function in the Hill Climbing implementation for the Traveling Salesperson Problem.

---

### 1. Initial Guess: `randomSolution`

This function creates our starting point by generating a random route.

- **`cities = list(range(len(tsp)))`**: Creates a list of city indices based on the size of the distance matrix (e.g., `[0, 1, 2, 3]`).
- **`random.shuffle(cities)`**: Randomly reorders the cities to create a random starting route.

---

### 2. The Objective Function: `routeLength`

This function acts as the **Heuristic ($h$)**, calculating the total distance of a specific route.

- **`total_distance = 0`**: Initializes the counter to zero.
- **`for i in range(len(solution)):`**: Iterates through every city in the provided route.
- **`tsp[solution[i - 1]][solution[i]]`**: Accesses the distance matrix.
  - Using `i - 1` is a clever Python trick: when `i` is 0, `i - 1` becomes -1 (the last city), ensuring the route "closes the loop" by returning to the start.
- **`total_distance += ...`**: Adds up the distances between each consecutive city in the path.

---

### 3. Creating Neighbors: `getNeighbours`

In TSP local search, a "neighbor" is a new route created by making a small change (swapping two cities) to the current route.

- **`for i in range(len(solution)):`** and **`for j in range(i + 1, len(solution)):`**: Nested loops that pick every possible pair of cities to swap.
- **`neighbour = solution.copy()`**: Creates a copy of the current route so we don't accidentally overwrite the original.
- **`neighbour[i], neighbour[j] = neighbour[j], neighbour[i]`**: Swaps the two selected cities to create a slightly different route.
- **`neighbours.append(neighbour)`**: Adds this new variation to a list of potential candidates.

---

### 4. Selection: `getBestNeighbour`

This part implements the **Greedy** choice, looking for the best immediate improvement.

- **`bestRouteLength = routeLength(tsp, neighbours[0])`**: Assumes the first neighbor is the best to start the comparison.
- **`for neighbour in neighbours:`**: Checks every single swapped route generated in the previous step.
- **`if currentRouteLength < bestRouteLength:`**: If a route is found that is shorter than our current "best," we update our record.

---

### 5. The Brain: `hillClimbing`

This is the core loop that drives the local search process.

- **`currentSolution = randomSolution(tsp)`**: Sets our initial random starting route.
- **`currentRouteLength = routeLength(tsp, currentSolution)`**: Calculates how "bad" or "good" our starting point is.
- **`while bestNeighbourRouteLength < currentRouteLength:`**: The "Climbing" condition. As long as there is a neighboring route that is shorter than our current one, we keep moving.
- **`currentSolution = bestNeighbour`**: Moves our position to the better route and repeats the search for even better neighbors.
- **`return currentSolution, currentRouteLength`**: Once no more neighbors can be found that reduce the distance, the algorithm "terminates" at the best route it found.

---

### Summary of Local Search Characteristics

- **Informed Search**: It uses the `routeLength` as a heuristic to guide the search.
- **Greedy**: It always takes the best immediate step.
- **Not Complete**: It can get stuck in a **Local Optimum** (a good route that isn't the absolute shortest) because it cannot "look ahead" or backtrack.
    