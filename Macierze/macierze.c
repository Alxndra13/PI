#include <stdio.h>
#include <math.h>

#define SIZE 40

void read_vector(double x[], int n) {
    for(int i = 0; i < n; ++i) {
        scanf("%lf", x++);
    }
}

void print_vector(double x[], int n) {
    for(int i = 0; i < n; ++i) {
        printf("%.4f ", x[i]);
    }
    printf("\n");
}

void read_mat(double A[][SIZE], int m, int n) {
    for(int i = 0; i < m; ++i) {
        for(int j = 0; j < n; ++j) {
            scanf("%lf", &A[i][j]);
        }
    }
}

void print_mat(double A[][SIZE], int m, int n) {
    for(int i = 0; i < m; ++i) {
        for(int j = 0; j < n; ++j) {
            printf("%.4f ", A[i][j]);
        }
        printf("\n");
    }
}

void print_mat_ind(double A[][SIZE], int m, int n, const int indices[])
{
    return;
}

// 5.1
// Calculate matrix product, AB = A X B
// A[m][p], B[p][n]
void mat_product(double A[][SIZE], double B[][SIZE], double AB[][SIZE], int m, int p, int n) {
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            double s = 0;
            for (int k = 0; k < p; ++k) {
                s += A[i][k] * B[k][j];

            }
            AB[i][j] = s;
        }
    }
}

// Calculate matrix - vector product
void mat_vec_product(double A[][SIZE], const double b[], double Ab[], int m, int n)
{
    return;
}

void backward_substit(double A[][SIZE], double x[], int n)
{
    return;
}

void backward_substitution_index(double A[][SIZE], const int indices[], double x[], int n)
{
    return;
}

// 5.2
// Matrix triangulation and determinant calculation - simplified version
// (no rows' swaps). If A[i][i] == 0, function returns NAN.
// Function may change A matrix elements.
double gauss_simplified(double A[][SIZE], int n)
{
    int i, j;
    double first, second, diff;
    for (int k=0; k<n-1; k++)
    {
        if (A[k][k] == 0) return NAN;
        else first = A[k][k];
        i = k+1;
        j = k;
        while (i < n)
        {
            second = A[i][j];
            diff = second / first;
            while (j < n)
            {
                A[i][j] = A[i][j] - (diff * A[k][j]);
                j++;
            }
            i++;
            j = k;
        }
    }
    double wyznacznik = A[0][0];
    for (int i=1; i<n; i++)
        wyznacznik *= A[i][i];
    return wyznacznik;
}

// 5.3
// Matrix triangulation, determinant calculation, and Ax = b solving - extended version
// (Swap the rows so that the row with the largest, leftmost nonzero entry is on top. While
// swapping the rows use index vector - do not copy entire rows.)
// If max A[i][i] < eps, function returns 0.
// If det != 0 && b != NULL && x != NULL then vector x should contain solution of Ax = b.

double gauss(double A[][SIZE], double b[], double x[], const int n, const double eps)
{
    double det = 1;
    int ind[n], tmp;
    double diff,s;
    for (int i = 0; i < n; ++i)
        ind[i] = i;
    for (int k = 0; k < n; ++k)
    {
        for (int i = k + 1; i < n; ++i)
        {
            if (fabs(A[ind[i]][k]) > fabs(A[ind[k]][k]))
            {
                tmp = ind[k];
                ind[k] = i;
                ind[i] = tmp;
                det *= -1;
            }
        }

        if (fabs(A[ind[k]][k]) < eps)
            det=0;
        for (int i = k + 1; i < n; ++i)
        {
            diff = A[ind[i]][k] / A[ind[k]][k];
            for (int j = k; j < n; ++j)
                A[ind[i]][j] -= A[ind[k]][j] * diff;
            b[ind[i]] -= b[ind[k]] * diff;
        }

        det *= A[ind[k]][k];
    }

    if (x == NULL || b == NULL)
        return 0;

    for (int i = n - 1; i >= 0; --i)
    {
        s = 0;
        for (int j = n - 1; j > i; --j)
        {
            s += A[ind[i]][j] * x[j];
        }
        x[i] = (b[ind[i]] - s) / A[ind[i]][i];
    }

    return det;
}

// 5.4
// Returns the determinant; B contains the inverse of A (if det(A) != 0)
// If max A[i][i] < eps, function returns 0.
double matrix_inv(double A[][SIZE], double B[][SIZE], int n, double eps)
{ //rozmiar A to 2n*n
//    int ind[n];
//    for (int i=0; i<n; i++)
//        ind[i]=i;
    double det=1;
    double C[n][2*n];
    for (int i=0; i<n; i++)
        for (int j=0; j<n; j++)
        {
            C[i][j]=A[i][j];
            C[i][j+n]=0;
            C[i][i+n]=1;
        }
    double d;
    for (int i=0; i<n; i++)
    {
        if (C[i][i+n]<eps) det=0;
        det *= C[i][i];
        if (C[i][i] != 1)
        {
            for (int k = i + 1; k < 2 * n; k++)
                C[i][k] /= C[i][i];
            C[i][i] = 1;
        }
        for (int j=i+1; j<n; j++)
        {
            d = C[j][i];
            for(int k=i; k<2*n; k++)
            {
                C[j][k] -= C[i][k]*d;
            }
        }
    }
    for (int i=n-1; i>=0; i--)
    {
        for (int j=i-1; j>=0; j--)
        {
            d = C[j][i];
            for (int k=i;k<2*n;k++)
            {
                C[j][k]-=d*C[i][k];
            }
        }
    }
    for (int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            B[i][j] = C[i][j+n];
    return det;
}

int main(void) {

    double A[SIZE][SIZE], B[SIZE][SIZE], C[SIZE][SIZE];
    double b[SIZE], x[SIZE], det, eps = 1.e-13;

    int to_do;
    int m, n, p;

    scanf("%d", &to_do);

    switch (to_do) {
        case 1:
            scanf("%d %d %d", &m, &p, &n);
            read_mat(A, m, p);
            read_mat(B, p, n);
            mat_product(A, B, C, m, p, n);
            print_mat(C, m, n);
            break;
        case 2:
            scanf("%d", &n);
            read_mat(A, n, n);
            printf("%.4f\n", gauss_simplified(A, n));
            break;
        case 3:
            scanf("%d", &n);
            read_mat(A, n, n);
            read_vector(b, n);
            det = gauss(A, b, x, n, eps);
            printf("%.4f\n", det);
            if (det) print_vector(x, n);
            break;
        case 4:
            scanf("%d", &n);
            read_mat(A, n, n);
            printf("%.4f\n", matrix_inv(A, B, n, eps));
            print_mat(B, n, n);
            break;
        default:
            printf("NOTHING TO DO FOR %d\n", to_do);
            break;
    }
}