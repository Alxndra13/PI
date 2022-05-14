#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAB_SIZE  1000
#define BUF_SIZE  1000

double get(int cols, int row, int col, const double *A)
{
    return A[row*cols + col];
}

void set(int cols, int row, int col, double *A, double value)
{
    A[row*cols + col] = value;
}

void prod_mat(int rowsA, int colsA, int colsB, double *A, double *B, double *AB)
{
    double sum, a, b;
    for (int i = 0; i < rowsA; i++)
    {
        for (int j = 0; j < colsB; j++)
        {
            sum = 0;
            for (int k = 0; k < colsA; k++) {
                a = get(colsA, i, k, A);
                b = get(colsB, k, j, B);
                sum = sum + a * b;
            }
            set(colsB,i,j,AB,sum);
        }
    }
}

void read_mat(int rows, int cols, double *t)
{
    int i = rows * cols;
    for(int j = 0; j < i; j++)
        scanf("%lf",&t[j]);
}

void print_mat(int rows, int cols, double *t)
{
    int d = rows*cols;
    for(int i = 0; i < d; i++)
    {
        printf("%0.2f ",t[i]);
        if ((i+1) % cols == 0)
            printf("\n");
    }
    printf("\n");
}

int read_char_lines(char *tab[])
{
    char line[BUF_SIZE];
    int i = 0;
    while(fgets(line,BUF_SIZE,stdin))
    {
        line[strlen(line)] = '\0';
        tab[i] = malloc(strlen(line));
        strcpy(tab[i],line);
        i++;
    }
    return i;
}

void write_char_line(char *tab[], int n)
{
    printf("%s ", tab[n]);
}

void delete_lines(char *tab[], int line_count)
{
    for(int i = 0; i < line_count; i++)
        free(tab[i]);
}

int read_dbl_lines_v1(double *ptr_tab[])
{
    int i = 0, j = 0;
    char* k;
    char line[BUF_SIZE];
    double number;
    while(fgets(line,BUF_SIZE,stdin))
    {
        k = line;
        while(k[0] != '\n')
        {
            number = strtod(k,&k);
            ptr_tab[i][j] = number;
            j++;
        }
        i++;
        ptr_tab[i] = &ptr_tab[i-1][j];
        j = 0;
    }
    return i;
}

void write_dbl_line_v1(double *ptr_tab[], int n)
{
    int i = 0;
    while(&ptr_tab[n][i] != &ptr_tab[n+1][0])
    {
        printf("%0.2f ",ptr_tab[n][i]);
        i++;
    }
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

