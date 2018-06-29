from enum import Enum


class Direction(Enum):
    UP = 0
    RIGHT = 1
    DOWN = 2
    LEFT = 3


if __name__ == '__main__':
    maze = [[False for _ in range(101)] for _ in range(101)]

    # Get n
    n = int(input())

    # Get the move input
    move_str = input().strip()
    
    row = 50
    col = 50
    min_row = row
    max_row = row
    min_col = col
    max_col = col
    maze[row][col] = True

    direction = Direction.DOWN

    # Move on
    for c in move_str:
        if c == 'F':
            # Move forward
            if direction == Direction.UP:
                row -= 1
                min_row = min(min_row, row)
            elif direction == Direction.RIGHT:
                col += 1
                max_col = max(max_col, col)
            elif direction == Direction.DOWN:
                row += 1
                max_row = max(max_row, row)
            elif direction == Direction.LEFT:
                col -= 1
                min_col = min(min_col, col)
            # Mark it
            maze[row][col] = True
        elif c == 'L':
            # Turn left
            direction = Direction((direction.value + 3) % 4)
        elif c == 'R':
            # Turn right
            direction = Direction((direction.value + 1) % 4)
        
    # Print the maze
    for i in range(min_row, max_row + 1):
        for j in range(min_col, max_col + 1):
            print('.' if maze[i][j] is True else '#', end='')
        print()
