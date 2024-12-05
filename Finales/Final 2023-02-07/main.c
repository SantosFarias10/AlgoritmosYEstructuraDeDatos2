#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#include "position.h"

int main(){
    position_t p = NULL;
    p = position_absolute(3, 4, 6);
    unsigned int **board = position_board(p);

    for(unsigned int i = 0u; i < 6u; i++){
        for(unsigned int j = 0u; j < 6u; j++){
            printf("[%d] ", board[i][j]);
        }
        printf("\n");
        free(board[i]);
    }
    printf("\n");
    free(board);

    list_t l = position_movements(p);
    list_show(l);

    l = list_destroy(l);
    position_destroy(p);

    return 0;
}