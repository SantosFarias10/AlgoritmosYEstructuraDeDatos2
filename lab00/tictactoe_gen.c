#include <stdlib.h>  /* exit() y EXIT_FAILURE */
#include <stdio.h>   /* printf(), scanf()     */
#include <stdbool.h> /* Tipo bool             */

#include <assert.h>  /* assert() */

#define FILASxCOLUMNAS 5 //MODIFICAR PARA CAMBIAR TAMANO DEL TABLERO
#define CELL_MAX (FILASxCOLUMNAS * FILASxCOLUMNAS - 1)

void print_sep(int length) {
    printf("\t ");
    for (int i=0; i < length;i++) printf("................");
    printf("\n");

}

void print_board(char board[][FILASxCOLUMNAS])
{
    int cell = 0;

    print_sep(FILASxCOLUMNAS);
    for (int row = 0; row < FILASxCOLUMNAS; ++row) {
        for (int column = 0; column < FILASxCOLUMNAS; ++column) {
            printf("\t | %d: %c ", cell, board[row][column]);
            ++cell;
        }
        printf("\t | \n");
        print_sep(FILASxCOLUMNAS);
    }
}

void fill_empty_board(char board[][FILASxCOLUMNAS]) {
    for (int i = 0; i < FILASxCOLUMNAS; i++){
        for (int j = 0; j < FILASxCOLUMNAS; j++){
            board[i][j] = '-';
        }
    }
}

char get_winner(char board[][FILASxCOLUMNAS]){
    char winner = '-';
    bool fila_winner, col_winner, diag_winner, diagOp_winner;

    diag_winner = true;
    diagOp_winner = true;

    //Fila
    for (int i = 0; i < FILASxCOLUMNAS; i++){
        fila_winner = true;
        for (int j = 0; j < FILASxCOLUMNAS; j++){
            if (board[i][j] != board[i][0] || board[i][0] == '-'){
                fila_winner = false;
                break;
            }
        }
        if (fila_winner){
            winner = board[i][0];
            return winner;
        }
    }

    //Columna
    for (int i = 0; i < FILASxCOLUMNAS; i++){
        col_winner = true;
        for (int j = 0; j < FILASxCOLUMNAS; j++){
            if (board[j][i] != board[0][i] || board[0][i] == '-'){
                col_winner = false;
                break;
            }
        }
        if (col_winner){
            winner = board[0][i];
            return winner;
        }
    }

    //Diagonal
    for (int i = 0; i < FILASxCOLUMNAS; i++){
        if (board[i][i] != board[0][0] || board[0][0] == '-'){
            diag_winner = false;
            break;
        }
    }
    if (diag_winner){
        winner = board[0][0];
        return winner;
    }

    //Diagonal Opuesta
    for (int i = 0; i < FILASxCOLUMNAS; i++){
        if (board[i][FILASxCOLUMNAS - 1 - i] != board[0][FILASxCOLUMNAS - 1] || board[0][FILASxCOLUMNAS - 1] == '-'){
            diagOp_winner = false;
            break;
        }
    }
    if (diagOp_winner){
        winner = board[0][FILASxCOLUMNAS - 1];
        return winner;
    }
    
    return winner;
}

bool has_free_cell(char board[FILASxCOLUMNAS][FILASxCOLUMNAS]){
    bool free_cell = false;
    
    for (int i = 0; i < FILASxCOLUMNAS; i++){
        for (int j = 0; j < FILASxCOLUMNAS; j++){
            if (board[i][j] == '-'){
                return true;  
            }
        }
    }

    return free_cell;
}

int main(void){
    printf("TicTacToe [Casi Completo :)]\n");

    char board[FILASxCOLUMNAS][FILASxCOLUMNAS];
    
    fill_empty_board(board);

    char turn = 'X';
    char winner = '-';
    int cell = 0;

    while (winner == '-' && has_free_cell(board)) {
        print_board(board);
        printf("\nTurno %c - Elija posición (número del 0 al %d): ", turn,
               CELL_MAX);
        int scanf_result = scanf("%d", &cell);
        if (scanf_result <= 0) {
            printf("Error al leer un número desde teclado\n");
            exit(EXIT_FAILURE);
        }
        if (cell >= 0 && cell <= CELL_MAX) {
            int row = cell / FILASxCOLUMNAS;
            int colum = cell % FILASxCOLUMNAS;
            if (board[row][colum] == '-') {
                board[row][colum] = turn;
                turn = turn == 'X' ? 'O' : 'X';
                winner = get_winner(board);
            } else {
                printf("\nCelda ocupada!\n");
            }
        } else {
            printf("\nCelda inválida!\n");
        }
    }
    print_board(board);
    if (winner == '-') {
        printf("Empate!\n");
    } else {
        printf("Ganó %c\n", winner);
    }
    return 0;