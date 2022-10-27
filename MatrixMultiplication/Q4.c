#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int MAT_SIZE = 8;

int count = 0;

void print(int n, int** mat) {
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d\t", mat[i][j]);
        }
        printf("\n");
    }
}

void mul_matrix(int n, int** A, int** B, int** C) {
    // Standards
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
                // 1 multiplication, 1 addition
                count += 2;
            }
            // Actually addition need to be subtracted by 1 (n elements, n-1 additions)
            count--;
        }
    }
}

void add_matrix(int n, int** A, int** B, int** C) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

void sub_matrix(int n, int** A, int** B, int** C) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}

void divide_n_conquer(int n, int** A, int** B, int** C) {
    if (n == 2) {
        mul_matrix(n, A, B, C);
    }
    else {
        int temp_row, temp_col;

        // Allocate memories for row and column
        int** a11 = malloc(sizeof(int*) * n / 2);
        int** a12 = malloc(sizeof(int*) * n / 2);
        int** a21 = malloc(sizeof(int*) * n / 2);
        int** a22 = malloc(sizeof(int*) * n / 2);
        int** b11 = malloc(sizeof(int*) * n / 2);
        int** b12 = malloc(sizeof(int*) * n / 2);
        int** b21 = malloc(sizeof(int*) * n / 2);
        int** b22 = malloc(sizeof(int*) * n / 2);
        int** c11 = malloc(sizeof(int*) * n / 2);
        int** c12 = malloc(sizeof(int*) * n / 2);
        int** c21 = malloc(sizeof(int*) * n / 2);
        int** c22 = malloc(sizeof(int*) * n / 2);
        int** temp_mat_1 = malloc(sizeof(int*) * n / 2);
        int** temp_mat_2 = malloc(sizeof(int*) * n / 2);

        // Divide to n/2 x n/2 matrices
        for (int i = 0; i < n / 2; i++) {
            a11[i] = malloc(sizeof(int) * n / 2);
            a12[i] = malloc(sizeof(int) * n / 2);
            a21[i] = malloc(sizeof(int) * n / 2);
            a22[i] = malloc(sizeof(int) * n / 2);
            b11[i] = malloc(sizeof(int) * n / 2);
            b12[i] = malloc(sizeof(int) * n / 2);
            b21[i] = malloc(sizeof(int) * n / 2);
            b22[i] = malloc(sizeof(int) * n / 2);
            c11[i] = malloc(sizeof(int) * n / 2);
            c12[i] = malloc(sizeof(int) * n / 2);
            c21[i] = malloc(sizeof(int) * n / 2);
            c22[i] = malloc(sizeof(int) * n / 2);
            temp_mat_1[i] = malloc(sizeof(int) * n / 2);
            temp_mat_2[i] = malloc(sizeof(int) * n / 2);
        }
        
        // Assign values to submatrices
        temp_row = 0;
        temp_col = 0;
        for (int i = 0; i < n; i++) {
            temp_col = 0;
            for (int j = 0; j < n; j++) {
                if (i < n / 2 && j < n / 2) {
                    a11[i][j] = A[i][j];
                    b11[i][j] = B[i][j];
                }
                else if (i >= n / 2 && j < n / 2) {
                    a12[temp_row][j] = A[i][j];
                    b12[temp_row][j] = B[i][j];
                }
                else if (i < n / 2 && j >= n / 2) {
                    a21[i][temp_col] = A[i][j];
                    b21[i][temp_col] = B[i][j];
                }
                else if (i >= n / 2 && j >= n / 2) {
                    a22[temp_row][temp_col] = A[i][j];
                    b22[temp_row][temp_col] = B[i][j];
                }

                if (j >= n / 2) {
                    temp_col++;
                }
            }
            if (i >= n / 2) {
                temp_row++;
            }
        }

        // find c11, c12, c21, c22 by multipling submatrices
        // c11
        divide_n_conquer(n / 2, a11, b11, temp_mat_1);
        divide_n_conquer(n / 2, a21, b12, temp_mat_2);
        add_matrix(n / 2, temp_mat_1, temp_mat_2, c11);
        printf("\nPartial matrix of C, size of %d\n", n / 2);
        print(n / 2, c11);
        count++;

        // c21
        divide_n_conquer(n / 2, a11, b21, temp_mat_1);
        divide_n_conquer(n / 2, a21, b22, temp_mat_2);
        printf("\nPartial matrix of C, size of %d\n", n / 2);
        add_matrix(n / 2, temp_mat_1, temp_mat_2, c21);
        print(n / 2, c21);
        count++;

        // c12
        divide_n_conquer(n / 2, a12, b11, temp_mat_1);
        divide_n_conquer(n / 2, a22, b12, temp_mat_2);
        add_matrix(n / 2, temp_mat_1, temp_mat_2, c12);
        printf("\nPartial matrix of C, size of %d\n", n / 2);
        print(n / 2, c12);
        count++;

        // c22
        divide_n_conquer(n / 2, a12, b21, temp_mat_1);
        divide_n_conquer(n / 2, a22, b22, temp_mat_2);
        add_matrix(n / 2, temp_mat_1, temp_mat_2, c22);
        printf("\nPartial matrix of C, size of %d\n", n / 2);
        print(n / 2, c22);
        count++;

        // Assign the values to C
        temp_row = 0;
        temp_col = 0;
        for (int i = 0; i < n; i++) {
            temp_col = 0;
            for (int j = 0; j < n; j++) {
                if (i < n / 2 && j < n / 2) {
                    C[i][j] = c11[i][j];
                }
                else if (i >= n / 2 && j < n / 2) {
                    C[i][j] = c12[temp_row][j];
                }
                else if (i < n / 2 && j >= n / 2) {
                    C[i][j] = c21[i][temp_col];
                }
                else if (i >= n / 2 && j >= n / 2) {
                    C[i][j] = c22[temp_row][temp_col];
                }

                if (j >= n / 2) {
                    temp_col++;
                }
            }
            if (i >= n / 2) {
                temp_row++;
            }
        }

        // Deallocate submatrices
        for (int i = 0; i < n / 2; i++) {
            free(a11[i]);
            free(a12[i]);
            free(a21[i]);
            free(a22[i]);
            free(b11[i]);
            free(b12[i]);
            free(b21[i]);
            free(b22[i]);
            free(c11[i]);
            free(c12[i]);
            free(c21[i]);
            free(c22[i]);
            free(temp_mat_1[i]);
            free(temp_mat_2[i]);
        }

        free(a11);
        free(a12);
        free(a21);
        free(a22);
        free(b11);
        free(b12);
        free(b21);
        free(b22);
        free(c11);
        free(c12);
        free(c21);
        free(c22);
        free(temp_mat_1);
        free(temp_mat_2);
    }
}

void strassen(int n, int** A, int** B, int** C) {
    if (n == 2) {
        // If size of submatrix is 2x2, just use standard method
        mul_matrix(n, A, B, C);
    }
    else {
        int temp_row, temp_col;

        // Allocate memory for each row of submatrices (n/2 x n/2)
        int** a11 = malloc(sizeof(int*) * n / 2);
        int** a12 = malloc(sizeof(int*) * n / 2);
        int** a21 = malloc(sizeof(int*) * n / 2);
        int** a22 = malloc(sizeof(int*) * n / 2);
        int** b11 = malloc(sizeof(int*) * n / 2);
        int** b12 = malloc(sizeof(int*) * n / 2);
        int** b21 = malloc(sizeof(int*) * n / 2);
        int** b22 = malloc(sizeof(int*) * n / 2);
        int** c11 = malloc(sizeof(int*) * n / 2);
        int** c12 = malloc(sizeof(int*) * n / 2);
        int** c21 = malloc(sizeof(int*) * n / 2);
        int** c22 = malloc(sizeof(int*) * n / 2);
        // P1 ~ P7
        int** P1 = malloc(sizeof(int*) * n / 2);
        int** P2 = malloc(sizeof(int*) * n / 2);
        int** P3 = malloc(sizeof(int*) * n / 2);
        int** P4 = malloc(sizeof(int*) * n / 2);
        int** P5 = malloc(sizeof(int*) * n / 2);
        int** P6 = malloc(sizeof(int*) * n / 2);
        int** P7 = malloc(sizeof(int*) * n / 2);
        // Allocate temporary memory to save data while calculating
        int** temp_mat_1 = malloc(sizeof(int*) * n / 2);
        int** temp_mat_2 = malloc(sizeof(int*) * n / 2);

        // Allocate memory for each row of submatrices (n/2 x n/2)
        for (int i = 0; i < n / 2; i++) {
            a11[i] = malloc(sizeof(int) * n / 2);
            a12[i] = malloc(sizeof(int) * n / 2);
            a21[i] = malloc(sizeof(int) * n / 2);
            a22[i] = malloc(sizeof(int) * n / 2);
            b11[i] = malloc(sizeof(int) * n / 2);
            b12[i] = malloc(sizeof(int) * n / 2);
            b21[i] = malloc(sizeof(int) * n / 2);
            b22[i] = malloc(sizeof(int) * n / 2);
            c11[i] = malloc(sizeof(int) * n / 2);
            c12[i] = malloc(sizeof(int) * n / 2);
            c21[i] = malloc(sizeof(int) * n / 2);
            c22[i] = malloc(sizeof(int) * n / 2);
            P1[i] = malloc(sizeof(int) * n / 2);
            P2[i] = malloc(sizeof(int) * n / 2);
            P3[i] = malloc(sizeof(int) * n / 2);
            P4[i] = malloc(sizeof(int) * n / 2);
            P5[i] = malloc(sizeof(int) * n / 2);
            P6[i] = malloc(sizeof(int) * n / 2);
            P7[i] = malloc(sizeof(int) * n / 2);
            temp_mat_1[i] = malloc(sizeof(int) * n / 2);
            temp_mat_2[i] = malloc(sizeof(int) * n / 2);
        }

        // Divide A into 4 submatrices A11, A12, A21, A22
        // Divide B into 4 submatrices B11, B12, B21, B22
        temp_row = 0;
        temp_col = 0;
        for (int i = 0; i < n; i++) {
            temp_col = 0;
            for (int j = 0; j < n; j++) {
                if (i < n / 2 && j < n / 2) {
                    a11[i][j] = A[i][j];
                    b11[i][j] = B[i][j];
                    /*temp_mat_1[i][j] = 0;
                    temp_mat_2[i][j] = 0;
                    c11[i][j] = 0;
                    c12[i][j] = 0;
                    c21[i][j] = 0;
                    c22[i][j] = 0;*/
                }
                else if (i >= n / 2 && j < n / 2) {
                    a12[temp_row][j] = A[i][j];
                    b12[temp_row][j] = B[i][j];
                }
                else if (i < n / 2 && j >= n / 2) {
                    a21[i][temp_col] = A[i][j];
                    b21[i][temp_col] = B[i][j];
                }
                else if (i >= n / 2 && j >= n / 2) {
                    a22[temp_row][temp_col] = A[i][j];
                    b22[temp_row][temp_col] = B[i][j];
                }

                if (j >= n / 2) {
                    temp_col++;
                }
            }
            if (i >= n / 2) {
                temp_row++;
            }
        }

        // Find P1 ~ P7
        // P1 = a11 * ( b21 - b22 ) 
        sub_matrix(n / 2, b21, b22, temp_mat_2);
        strassen(n / 2, a11, temp_mat_2, P1);
        count += 2;
        
        // P2 = ( a11 + a21 ) * b22
        add_matrix(n / 2, a11, a21, temp_mat_1);
        strassen(n / 2, temp_mat_1, b22, P2);
        count += 2;

        // P3 = ( a12 + a22 ) * b11
        add_matrix(n / 2, a12, a22, temp_mat_1);
        strassen(n / 2, temp_mat_1, b11, P3);
        count += 2;

        // P4 = a22 * ( b12 - b11 )
        sub_matrix(n / 2, b12, b11, temp_mat_2);
        strassen(n / 2, a22, temp_mat_2, P4);
        count += 2;

        // P5 = ( a11 + a22 ) * ( b11 + b22 )
        add_matrix(n / 2, a11, a22, temp_mat_1);
        add_matrix(n / 2, b11, b22, temp_mat_2);
        strassen(n / 2, temp_mat_1, temp_mat_2, P5);
        count += 3;

        // P6 = ( a21 - a22 ) * ( b12 + b22 )
        sub_matrix(n / 2, a21, a22, temp_mat_1);
        add_matrix(n / 2, b12, b22, temp_mat_2);
        strassen(n / 2, temp_mat_1, temp_mat_2, P6);
        count += 3;

        // P7 = ( a11 - a12 ) * ( b11 + b21 )
        sub_matrix(n / 2, a11, a12, temp_mat_1);
        add_matrix(n / 2, b11, b21, temp_mat_2);
        strassen(n / 2, temp_mat_1, temp_mat_2, P7);
        count += 3;

        // Find c11 ~ c22
        // c11 = P5 + P4 - P2 + P6
        add_matrix(n / 2, P5, P4, temp_mat_1);
        sub_matrix(n / 2, temp_mat_1, P2, temp_mat_2);
        add_matrix(n / 2, temp_mat_2, P6, c11);
        printf("\nPartial matrix of C, size of %d\n", n / 2);
        print(n / 2, c11);
        count += 3;

        // c21 = P1 + P2
        add_matrix(n / 2, P1, P2, c21);
        printf("\nPartial matrix of C, size of %d\n", n / 2);
        print(n / 2, c21);
        count += 2;

        // c12 = P3 + P4
        add_matrix(n / 2, P3, P4, c12);
        printf("\nPartial matrix of C, size of %d\n", n / 2);
        print(n / 2, c12);
        count += 2;

        // c22 = P5 + P1 - P3 - P7
        add_matrix(n / 2, P5, P1, temp_mat_1);
        sub_matrix(n / 2, temp_mat_1, P3, temp_mat_2);
        sub_matrix(n / 2, temp_mat_2, P7, c22);
        printf("\nPartial matrix of C, size of %d\n", n / 2);
        print(n / 2, c22);
        count += 3;

        // Assign c11 ~ c22 to C matrix
        temp_row = 0;
        temp_col = 0;
        for (int i = 0; i < n; i++) {
            temp_col = 0;
            for (int j = 0; j < n; j++) {
                if (i < n / 2 && j < n / 2) {
                    C[i][j] = c11[i][j];
                }
                else if (i >= n / 2 && j < n / 2) {
                    C[i][j] = c12[temp_row][j];
                }
                else if (i < n / 2 && j >= n / 2) {
                    C[i][j] = c21[i][temp_col];
                }
                else if (i >= n / 2 && j >= n / 2) {
                    C[i][j] = c22[temp_row][temp_col];
                }

                if (j >= n / 2) {
                    temp_col++;
                }
            }
            if (i >= n / 2) {
                temp_row++;
            }
        }

        // Deallocate submatrices
        for (int i = 0; i < n / 2; i++) {
            free(a11[i]);
            free(a12[i]);
            free(a21[i]);
            free(a22[i]);
            free(b11[i]);
            free(b12[i]);
            free(b21[i]);
            free(b22[i]);
            free(c11[i]);
            free(c12[i]);
            free(c21[i]);
            free(c22[i]);
            free(P1[i]);
            free(P2[i]);
            free(P3[i]);
            free(P4[i]);
            free(P5[i]);
            free(P6[i]);
            free(P7[i]);
            free(temp_mat_1[i]);
            free(temp_mat_2[i]);
        }

        free(a11);
        free(a12);
        free(a21);
        free(a22);
        free(b11);
        free(b12);
        free(b21);
        free(b22);
        free(c11);
        free(c12);
        free(c21);
        free(c22);
        free(P1);
        free(P2);
        free(P3);
        free(P4);
        free(P5);
        free(P6);
        free(P7);
        free(temp_mat_1);
        free(temp_mat_2);
    }
}

int main() {
	srand(time(NULL));

    // Allocate memories (column)
    int** A = malloc(sizeof(int*) * MAT_SIZE);
    int** B = malloc(sizeof(int*) * MAT_SIZE);
    int** C = malloc(sizeof(int*) * MAT_SIZE);

    // Allocate memories (row)
    for (int i = 0; i < MAT_SIZE; i++)
    {
        A[i] = malloc(sizeof(int) * MAT_SIZE);
        B[i] = malloc(sizeof(int) * MAT_SIZE);
        C[i] = malloc(sizeof(int) * MAT_SIZE);
    }

    // Assign random values to A, B matrix
    for (int i = 0; i < MAT_SIZE; i++)
    {
        for (int j = 0; j < MAT_SIZE; j++)
        {
            A[i][j] = rand() % 1000;
            B[i][j] = rand() % 1000;
        }
    }

    // Print values of A, B matrix
    printf("A\n");
    for (int i = 0; i < MAT_SIZE; i++)
    {
        for (int j = 0; j < MAT_SIZE; j++)
        {
            printf("%d\t", A[i][j]);
        }
        printf("\n");
    }
    printf("\nB\n");
    for (int i = 0; i < MAT_SIZE; i++)
    {
        for (int j = 0; j < MAT_SIZE; j++)
        {
            printf("%d\t", B[i][j]);
        }
        printf("\n");
    }

    // Multiply 2 matrices
    //mul_matrix(MAT_SIZE, A, B, C);
    //divide_n_conquer(MAT_SIZE, A, B, C);
    strassen(MAT_SIZE, A, B, C);


    // Print values of C matrix
    printf("\nC\n");
    for (int i = 0; i < MAT_SIZE; i++)
    {
        for (int j = 0; j < MAT_SIZE; j++)
        {
            printf("%d\t", C[i][j]);
        }
        printf("\n");
    }

    printf("\nCalculation Count: %d\n", count);

}