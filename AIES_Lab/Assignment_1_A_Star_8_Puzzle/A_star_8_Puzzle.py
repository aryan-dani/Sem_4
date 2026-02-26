import heapq

def get_manhattan_distance(state, goal):
    distance = 0
    for i in range(1, 9):
        curr_idx = state.index(i)
        goal_idx = goal.index(i)
        
        curr_r, curr_c = curr_idx // 3, curr_idx % 3
        goal_r, goal_c = goal_idx // 3, goal_idx % 3
        
        distance += abs(curr_r - goal_r) + abs(curr_c - goal_c)
    return distance

def get_neighbors(state):
    neighbors = []
    blank_idx = state.index(0)
    r, c = blank_idx // 3, blank_idx % 3
    
    moves = [(-1, 0), (1, 0), (0, -1), (0, 1)]
    
    for dr, dc in moves:
        nr, nc = r + dr, c + dc
        if 0 <= nr < 3 and 0 <= nc < 3:
            neighbor_list = list(state)
            target_idx = nr * 3 + nc
            
            neighbor_list[blank_idx], neighbor_list[target_idx] = neighbor_list[target_idx], neighbor_list[blank_idx]
            neighbors.append(tuple(neighbor_list))
            
    return neighbors

def solve_8_puzzle(start, goal):
    open_list = []
    # (f_score, g_score, current_state)
    heapq.heappush(open_list, (get_manhattan_distance(start, goal), 0, start))
    
    closed_list = set()
    parent_map = {start: None}

    while open_list:
        f, g, current = heapq.heappop(open_list)

        if current == goal:
            return reconstruct_path(parent_map, current)

        closed_list.add(current)

        for neighbor in get_neighbors(current):
            if neighbor in closed_list:
                continue
            
            if neighbor not in parent_map:
                h = get_manhattan_distance(neighbor, goal)
                parent_map[neighbor] = current
                heapq.heappush(open_list, (g + 1 + h, g + 1, neighbor))

    return None

def reconstruct_path(parent_map, current):
    path = []
    while current is not None:
        path.append(current)
        current = parent_map[current]
    return path[::-1]

def print_board(state):
    for i in range(0, 9, 3):
        print(state[i], state[i+1], state[i+2])
    print()

start = (1, 2, 3, 4, 0, 5, 7, 8, 6)
goal = (1, 2, 3, 4, 5, 6, 7, 8, 0)

solution = solve_8_puzzle(start, goal)

if solution:
    print("Goal reached!")
    for i, state in enumerate(solution):
        print("Step", i)
        print_board(state)
else:
    print("No solution.")