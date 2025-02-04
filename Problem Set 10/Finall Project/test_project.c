#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <complex.h>

// Assume that the following functions have been implemented in the main calculator code:

// Factorial function (recursive)
long long factorial(int n) {
    if (n <= 1)
        return 1;
    return n * factorial(n - 1);
}

// Matrix determinant function (recursive)
float matrix_determinant(int n, float matrix[n][n]) {
    if (n == 1)
        return matrix[0][0];
    float det = 0, temp[n][n];
    int sign = 1;
    for (int f = 0; f < n; f++){
        // Construct the submatrix (minor)
        for (int i = 1; i < n; i++){
            int colIndex = 0;
            for (int j = 0; j < n; j++){
                if (j == f)
                    continue;
                temp[i-1][colIndex] = matrix[i][j];
                colIndex++;
            }
        }
        det += sign * matrix[0][f] * matrix_determinant(n-1, temp);
        sign = -sign;
    }
    return det;
}

// Matrix rank computation using row echelon form (testable version)
int compute_matrix_rank(int rows, int cols, float matrix[rows][cols]) {
    // Copy matrix to a temporary array
    float temp[rows][cols];
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            temp[i][j] = matrix[i][j];
        }
    }
    int rank = cols;
    for (int row = 0; row < rank; row++){
        if (fabs(temp[row][row]) > 1e-6) {
            for (int col = 0; col < rows; col++){
                if (col != row) {
                    float mult = temp[col][row] / temp[row][row];
                    for (int i = 0; i < rank; i++){
                        temp[col][i] -= mult * temp[row][i];
                    }
                }
            }
        } else {
            rank--;
            for (int i = 0; i < rows; i++){
                temp[i][row] = temp[i][row+1];
            }
            row--;
        }
    }
    return rank;
}

// Matrix transpose function
void compute_matrix_transpose(int rows, int cols, float matrix[rows][cols], float transpose[cols][rows]) {
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            transpose[j][i] = matrix[i][j];
        }
    }
}

// ---------------- Unit Test Functions ----------------

// Factorial test
void test_factorial() {
    assert(factorial(0) == 1);
    assert(factorial(1) == 1);
    assert(factorial(5) == 120);
    printf("Factorial tests passed.\n");
}

// Matrix determinant test
void test_matrix_determinant() {
    int n = 2;
    float matrix[2][2] = { {4, 6}, {3, 8} }; // Determinant should be 14
    float det = matrix_determinant(n, matrix);
    assert(fabs(det - 14.0) < 1e-6);
    printf("Matrix determinant tests passed.\n");
}

// Matrix rank test
void test_matrix_rank() {
    int rows = 3, cols = 3;
    float matrix[3][3] = {
        {1, 2, 3},
        {2, 4, 6},
        {1, 1, 1}
    };
    // In this matrix, the second row is a multiple of the first row; therefore, the rank should be 2.
    int rank = compute_matrix_rank(rows, cols, matrix);
    assert(rank == 2);
    printf("Matrix rank tests passed.\n");
}

// Matrix transpose test
void test_matrix_transpose() {
    int rows = 2, cols = 3;
    float matrix[2][3] = {
        {1, 2, 3},
        {4, 5, 6}
    };
    float transpose[3][2];
    compute_matrix_transpose(rows, cols, matrix, transpose);
    // We expect the transpose to be: { {1,4}, {2,5}, {3,6} }
    assert(fabs(transpose[0][0] - 1.0) < 1e-6);
    assert(fabs(transpose[0][1] - 4.0) < 1e-6);
    assert(fabs(transpose[1][0] - 2.0) < 1e-6);
    assert(fabs(transpose[1][1] - 5.0) < 1e-6);
    assert(fabs(transpose[2][0] - 3.0) < 1e-6);
    assert(fabs(transpose[2][1] - 6.0) < 1e-6);
    printf("Matrix transpose tests passed.\n");
}

// Complex number operations test
void test_complex_operations() {
    double complex num1 = 1.0 + 2.0 * I;
    double complex num2 = 3.0 + 4.0 * I;
    double complex sum = num1 + num2;       // Expecting 4+6i
    double complex diff = num1 - num2;      // Expecting -2-2i
    double complex prod = num1 * num2;      // Expecting (1*3 - 2*4) + (1*4 + 2*3)i = -5 + 10i
    double complex quot = num1 / num2;      // Calculating division

    assert(fabs(creal(sum) - 4.0) < 1e-6 && fabs(cimag(sum) - 6.0) < 1e-6);
    assert(fabs(creal(diff) + 2.0) < 1e-6 && fabs(cimag(diff) + 2.0) < 1e-6);
    assert(fabs(creal(prod) + 5.0) < 1e-6 && fabs(cimag(prod) - 10.0) < 1e-6);
    // For division, approximate check
    double complex expected_quot = ( (1.0*3.0+2.0*4.0) / 25.0 ) + ( (2.0*3.0-1.0*4.0) / 25.0 ) * I;
    assert(fabs(creal(quot) - creal(expected_quot)) < 1e-6);
    assert(fabs(cimag(quot) - cimag(expected_quot)) < 1e-6);
    printf("Complex number operations tests passed.\n");
}

// Special mathematical functions tests

void test_exponential() {
    double x = 1.0;
    double exp_val = exp(x);
    assert(fabs(exp_val - 2.7182818) < 1e-6);
    printf("Exponential function tests passed.\n");
}

void test_logarithm() {
    double x = 2.7182818;
    double log_val = log(x);
    assert(fabs(log_val - 1.0) < 1e-6);
    printf("Logarithm function tests passed.\n");
}

void test_gamma_function() {
    double x = 5.0; // Gamma(5) = 4! = 24
    double gamma_val = tgamma(x);
    assert(fabs(gamma_val - 24.0) < 1e-6);
    printf("Gamma function tests passed.\n");
}

void test_bessel_function() {
    double x = 0.0; // J0(0) = 1
    double bessel_val = j0(x);
    assert(fabs(bessel_val - 1.0) < 1e-6);
    printf("Bessel function tests passed.\n");
}

// Unit conversion tests
float meters_to_cm(float m) { return m * 100.0; }
float km_to_miles(float km) { return km * 0.621371; }
float deg_to_rad(float deg) { return deg * (M_PI / 180); }
float rad_to_deg(float rad) { return rad * (180 / M_PI); }

void test_unit_conversion() {
    assert(fabs(meters_to_cm(1.0) - 100.0) < 1e-6);
    assert(fabs(km_to_miles(1.0) - 0.621371) < 1e-6);
    assert(fabs(deg_to_rad(180.0) - M_PI) < 1e-6);
    assert(fabs(rad_to_deg(M_PI) - 180.0) < 1e-6);
    printf("Unit conversion tests passed.\n");
}

// Descriptive statistics test: mean, median, variance, and standard deviation
void test_statistical_descriptive() {
    int n = 5;
    float data[] = {1, 2, 3, 4, 5}; // mean=3, median=3, variance=2, std deviation = sqrt(2)
    float sum = 0;
    for (int i = 0; i < n; i++) sum += data[i];
    float mean = sum / n;
    assert(fabs(mean - 3.0) < 1e-6);

    float median = (n % 2 == 1) ? data[n/2] : (data[n/2 - 1] + data[n/2]) / 2;
    assert(fabs(median - 3.0) < 1e-6);

    float var = 0;
    for (int i = 0; i < n; i++) var += pow(data[i] - mean, 2);
    var /= n;
    assert(fabs(var - 2.0) < 1e-6);

    float std = sqrt(var);
    assert(fabs(std - sqrt(2.0)) < 1e-6);
    printf("Statistical descriptive tests passed.\n");
}

int main() {
    test_factorial();
    test_matrix_determinant();
    test_matrix_rank();
    test_matrix_transpose();
    test_complex_operations();
    test_exponential();
    test_logarithm();
    test_gamma_function();
    test_bessel_function();
    test_unit_conversion();
    test_statistical_descriptive();
    printf("All tests passed.\n");
    return 0;
}
