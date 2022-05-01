#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#define TAB_SIZE  1000
#define BUF_SIZE  1000

double get(int cols, int row, int col, const double *A)
{
    return 0;
}

void set(int cols, int row, int col, double *A, double value)
{
    return;
}

void prod_mat(int rowsA, int colsA, int colsB, double *A, double *B, double *AB)
{
    return;
}

void read_mat(int rows, int cols, double *t)
{
    return;
}

void print_mat(int rows, int cols, double *t)
{
    return;
}

int read_char_lines(char *tab[])
{
    return 0 ;
}

void write_char_line(char *tab[], int n)
{
    return;
}

void delete_lines(char *tab[], int line_count)
{
    return;
}

int read_dbl_lines_v1(double *ptr_tab[])
{
    return 0;
}

void write_dbl_line_v1(double *ptr_tab[], int n)
{
    return;
}

int main(void) {
    int to_do;

    scanf ("%d", &to_do);

    double A[TAB_SIZE], B[TAB_SIZE], C[TAB_SIZE];
    int n, lines_counter, rowsA,colsA,rowsB,colsB;
    char *char_lines_table[TAB_SIZE];
    double series_table[TAB_SIZE];
    double *ptr_table[TAB_SIZE];

    switch (to_do) {
        case 1:
            scanf("%d %d",&rowsA,&colsA);
            read_mat(rowsA, colsA, A);
            scanf("%d %d",&rowsB,&colsB);
            read_mat(rowsB, colsB, B);
            prod_mat(rowsA,colsA,colsB,A,B,C);
            print_mat(rowsA,colsB,C);
            break;
        case 2:
            scanf("%d",&n);
            ptr_table[0] = series_table;
            lines_counter = read_dbl_lines_v1(ptr_table);
            write_dbl_line_v1(ptr_table,n);
            break;
        case 3:
            scanf("%d", &n);
            lines_counter = read_char_lines(char_lines_table);
            write_char_line(char_lines_table,n);
            delete_lines(char_lines_table,lines_counter);
            break;
        default:
            printf("NOTHING TO DO FOR %d\n", to_do);
    }
    return 0;
}
