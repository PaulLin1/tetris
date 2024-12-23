#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "board.h"
#include "tetromino.h"
#include "constants.h"

Board init_board() {
    Board board;
    for (int y = 0; y < ROWS; y++) {
        for (int x = 0; x < COLS; x++) {
            board.cells[y * COLS + x] = 0;
        }
    }
    board.score = 0;
    return board;
}

int check_end(Board* board) {
    for (int i = 0; i < COLS; ++i) {
        if (board->cells[i] == 1) {  // Check only top row
            return 1;
        }
    }
    return 0;
}

void update_board(Board* board) {
    Block* curr = board->current_block;
    
    for (int y = 0; y < curr->size; y++) {
        for (int x = 0; x < curr->size; x++) {
            int current_pixel = curr->cells[y * curr->size + x];
            if (current_pixel == 1) {
                board->cells[(curr->current_y + y) * COLS + (curr->current_x + x)] = current_pixel;
            }
        }
    }
}

void drop_block(Board* board) {
    if (check_collision(board, 's')) {
        board->current_block->current_y++;
    }
}

int check_collision(Board* board, char movement) {
    Block* block = board->current_block;
    int dx, dy;
    switch (movement) {
        case 'a':
            dx = -1;
            dy = 0;
            break;
        case 'd':
            dx = 1;
            dy = 0;
            break;
        case 's':
            dx = 0;
            dy = 1;
            break;
        default:
            dx = 0;
            dy = 0;
            break;
    }
    for (int i = 0; i < block->size; ++i) {
        for (int j = 0; j < block->size; ++j) {
            if (block->cells[j * block->size + i] == 1) {
                int new_x = block->current_x + i + dx;
                int new_y = block->current_y + j + dy;
                if (new_y >= ROWS || (board->cells[new_y * COLS + new_x] == 1 && movement == 's')) {
                    block->dropped = 1;
                    new_block(board);
                    return 0;
                }
                if (new_x < 0 || new_x >= COLS || new_y < 0 || new_y >= ROWS) {
                    return 0;
                }
                if (board->cells[new_y * COLS + new_x] == 1) {
                    return 0;
                }
            }
        }
    }
    return 1;
}

void move_block(Board* board, char movement) {
    Block* block = board->current_block;
    if (check_collision(board, movement)) {
        if (movement == 's') {
            block->current_y++;
        } else if (movement == 'a') {
            block->current_x--;
        } else if (movement == 'd') {
            block->current_x++;
        }
    }
    if (movement == 'w') {
        int n = block->size;
        int rotated[n * n];
        int temp[n * n];
        memcpy(temp, block->cells, n * n * sizeof(int));
        
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                rotated[j * n + (n - 1 - i)] = block->cells[i * n + j];
            }
        }
        memcpy(block->cells, rotated, n * n * sizeof(int));
        
        while (block->current_x < 0) {
            block->current_x++;
        }
        while (block->current_x > COLS - block->size) {
            block->current_x--;
        }
        if (!check_collision(board, 'l')) {
            memcpy(block->cells, temp, n * n * sizeof(int));
            block->rotation = (block->rotation + 1) % 4;
        }
    }
}

void new_block(Board* board) {
    Block* curr = board->current_block;

    for (int y = 0; y < curr->size; y++) {
        for (int x = 0; x < curr->size; x++) {
            int current_pixel = curr->cells[y * curr->size + x];
            if (current_pixel == 1) {
                board->cells[(curr->current_y + y) * COLS + (curr->current_x + x)] = current_pixel;
            }
        }
    }
    tetris(board);
    board->current_block = board->next_block;
    Block* z = malloc(sizeof(Block));
    Block* temp = load_block();
    memcpy(z, temp, sizeof(Block));
    board->next_block = z;
}

void tetris(Board *board) {
    int clear_counter = 0;
    for (int j = 0; j < ROWS; ++j) {
        int total = 0;

        for (int i = 0; i < COLS; ++i) {
            if (board->cells[j * COLS + i] == 1) {
                total += 1;
            }
        }
        if (total == COLS) {
            clear_counter++;
            for (int i = j; i > 0; --i) {
                for (int k = 0; k < COLS; ++k) {
                    board->cells[i * COLS + k] = board->cells[(i - 1) * COLS + k];
                }
            }

            for (int q = 0; q < COLS; ++q) {
                board->cells[q] = 0;  // Creates empty top row
            }
        }
    }
 
    // Scoring: number of rows cleared at once multiplies the reward
    switch (clear_counter) {
        case 1:
            board->score += 100;
            break;
        case 2:
            board->score += 300;
            break;
        case 3:
            board->score += 500;
            break;
        case 4:
            board->score += 800;
            break;
        default:
            ;
    }
}