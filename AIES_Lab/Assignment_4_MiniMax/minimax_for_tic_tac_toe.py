"""
Step-by-Step Implementation of Minimax for Tic-Tac-Toe

Step 1: Board Representation
We represent the board as a 1D list of 9 elements. Each index (0-8) represents a cell.

Step 2: Checking State (Win/Draw)
We define the winning combinations (rows, columns, diagonals) to check if a player has won.
We also check if the board is full to determine a draw.

Step 3: Minimax Algorithm
The core algorithm that evaluates all possible moves to choose the optimal one.
- If the game is over, it returns a score (+1 if AI wins, -1 if human wins, 0 for tie).
- If it's MAX's turn (AI), it recursively evaluates all possible moves, calling Minimax, and picks the path with the maximum score.
- If it's MIN's turn (Human), it assumes the human will play optimally and picks the path with the minimum score.

Step 4: Finding the Best Move
Iterate through all empty spots and use the Minimax algorithm to find the initial move with the highest score.
"""

import math

def print_board(board):
    for i in range(0, 9, 3):
        print(f" {board[i]} | {board[i+1]} | {board[i+2]} ")
        if i < 6:
            print("-----------")

def check_winner(board, player):
    # Winning combinations (rows, columns, diagonals)
    win_conditions = [
        [0, 1, 2], [3, 4, 5], [6, 7, 8], # Rows
        [0, 3, 6], [1, 4, 7], [2, 5, 8], # Columns
        [0, 4, 8], [2, 4, 6]             # Diagonals
    ]
    for condition in win_conditions:
        if board[condition[0]] == board[condition[1]] == board[condition[2]] == player:
            return True
    return False

def is_board_full(board):
    return ' ' not in board

def minimax(board, depth, is_maximizing):
    # Terminal states (base cases for recursion)
    if check_winner(board, 'X'):   # AI is 'X' (Maximizer)
        return 1
    elif check_winner(board, 'O'): # Human is 'O' (Minimizer)
        return -1
    elif is_board_full(board):     # Tie
        return 0

    if is_maximizing:
        best_score = -math.inf
        for i in range(9):
            if board[i] == ' ':
                board[i] = 'X' # Make a move
                score = minimax(board, depth + 1, False) # Recursive call
                board[i] = ' ' # Undo the move
                best_score = max(score, best_score)
        return best_score
    else:
        best_score = math.inf
        for i in range(9):
            if board[i] == ' ':
                board[i] = 'O' # Make a move
                score = minimax(board, depth + 1, True) # Recursive call
                board[i] = ' ' # Undo the move
                best_score = min(score, best_score)
        return best_score

def find_best_move(board):
    best_score = -math.inf
    best_move = -1
    for i in range(9):
        if board[i] == ' ':
            board[i] = 'X' # Try playing in this cell
            score = minimax(board, 0, False)
            board[i] = ' ' # Undo the move
            if score > best_score:
                best_score = score
                best_move = i
    return best_move

if __name__ == "__main__":
    # Initialize an empty board
    board = [' '] * 9
    print("Tic-Tac-Toe Minimax Algorithm")
    print("You are 'O' and the AI is 'X'")
    print("Positions are 0-8 from top-left to bottom-right.")
    
    while True:
        print_board(board)
        
        # Check game over conditions
        if check_winner(board, 'X'):
            print("AI (X) wins!")
            break
        elif check_winner(board, 'O'):
            print("You (O) win!")
            break
        elif is_board_full(board):
            print("It's a tie!")
            break
            
        # Human turn
        try:
            move = int(input("Enter your move (0-8): "))
            if move < 0 or move > 8 or board[move] != ' ':
                print("Invalid move. Try again.")
                continue
        except ValueError:
            print("Please enter a valid number.")
            continue
            
        board[move] = 'O'
        
        # AI turn
        if not is_board_full(board) and not check_winner(board, 'O'):
            print("AI is making a move...")
            ai_move = find_best_move(board)
            if ai_move != -1:
                board[ai_move] = 'X'

