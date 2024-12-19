#include "tetromino.h"
#include "board.h"
#include "constants.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

static Block all_blocks[7];

void initialize_all_blocks() {
	size_t o_block_length = 2;
	int *o_block_arr = malloc(o_block_length * o_block_length * sizeof(int));
	o_block_arr[0] = 1; 
	o_block_arr[1] = 1; 
	o_block_arr[2] = 1; 
	o_block_arr[3] = 1; 

	// Each block is initialized centered at the top of the board
	// The rotation is set to 0
	Block new_block = {o_block_arr, o_block_length, 4, 0, 0, 0};
	all_blocks[0] = new_block;

	size_t l_block_length = 3;
	int *l_block_arr = malloc(l_block_length * l_block_length * sizeof(int));
	l_block_arr[0] = 1; 
	l_block_arr[1] = 0; 
	l_block_arr[2] = 0; 
	l_block_arr[3] = 1; 
	l_block_arr[4] = 1; 
	l_block_arr[5] = 1; 
	l_block_arr[6] = 0; 
	l_block_arr[7] = 0; 
	l_block_arr[8] = 0; 

	Block l_block = {l_block_arr, l_block_length, 3, 0, 0, 0};
	all_blocks[1] = l_block;

	size_t j_block_length = 3;
	int *j_block_arr = malloc(j_block_length * j_block_length * sizeof(int));
	j_block_arr[0] = 0; 
	j_block_arr[1] = 0; 
	j_block_arr[2] = 1; 
	j_block_arr[3] = 1; 
	j_block_arr[4] = 1; 
	j_block_arr[5] = 1; 
	j_block_arr[6] = 0; 
	j_block_arr[7] = 0; 
	j_block_arr[8] = 0; 

	Block j_block = {j_block_arr, j_block_length, 3, 0, 0, 0};
	all_blocks[2] = j_block;

	size_t line_block_length = 4;
	int *line_block_arr = malloc(line_block_length * line_block_length * sizeof(int));
	line_block_arr[0] = 0; 
	line_block_arr[1] = 0; 
	line_block_arr[2] = 0; 
	line_block_arr[3] = 0; 
	line_block_arr[4] = 0; 
	line_block_arr[5] = 0; 
	line_block_arr[6] = 0; 
	line_block_arr[7] = 0; 
	line_block_arr[8] = 1; 
	line_block_arr[9] = 1; 
	line_block_arr[10] = 1; 
	line_block_arr[11] = 1; 
	line_block_arr[12] = 0; 
	line_block_arr[13] = 0; 
	line_block_arr[14] = 0; 
	line_block_arr[15] = 0; 

	Block line_block = {line_block_arr, line_block_length, 3, 0, 0, 0};
	all_blocks[3] = line_block;

	size_t t_block_length = 3;
	int *t_block_arr = malloc(t_block_length * t_block_length * sizeof(int));
	t_block_arr[0] = 0; 
	t_block_arr[1] = 1; 
	t_block_arr[2] = 0; 
	t_block_arr[3] = 1; 
	t_block_arr[4] = 1; 
	t_block_arr[5] = 1; 
	t_block_arr[6] = 0; 
	t_block_arr[7] = 0; 
	t_block_arr[8] = 0; 

	Block t_block = {t_block_arr, t_block_length, 3, 0, 0, 0};
	all_blocks[4] = t_block;

	size_t z_block_length = 3;
	int *z_block_arr = malloc(z_block_length * z_block_length * sizeof(int));
	z_block_arr[0] = 1; 
	z_block_arr[1] = 1; 
	z_block_arr[2] = 0; 
	z_block_arr[3] = 0; 
	z_block_arr[4] = 1; 
	z_block_arr[5] = 1; 
	z_block_arr[6] = 0; 
	z_block_arr[7] = 0; 
	z_block_arr[7] = 0; 

	Block z_block = {z_block_arr, z_block_length, 3, 0, 0, 0};
	all_blocks[5] = z_block;

	size_t s_block_length = 3;
	int *s_block_arr = malloc(s_block_length * s_block_length * sizeof(int));
	s_block_arr[0] = 0; 
	s_block_arr[1] = 1; 
	s_block_arr[2] = 1; 
	s_block_arr[3] = 1; 
	s_block_arr[4] = 1; 
	s_block_arr[5] = 0; 
	s_block_arr[6] = 0; 
	s_block_arr[7] = 0; 
	s_block_arr[8] = 0; 

	Block s_block = {s_block_arr, s_block_length, 3, 0, 0, 0};
	all_blocks[6] = s_block;
}

Block* load_block() {
	// Allocate memory for a new block
    Block* new_block = malloc(sizeof(Block));
    
    if (new_block == NULL) {
        return NULL;
    }

	// Copy block type from block templates
	int rand_index = rand() % 7;
    *new_block = all_blocks[rand_index];
    
    new_block->cells = malloc(new_block->size * new_block->size * sizeof(int));
    
    if (new_block->cells == NULL) {
        free(new_block);
        return NULL;
    }
    
	// Copy the block 'pixels' from template
    memcpy(new_block->cells, all_blocks[rand_index].cells, 
           new_block->size * new_block->size * sizeof(int));
    
    return new_block;
}