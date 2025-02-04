#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>

#define MAX_HISTORY 100
#define MAX_MATRIX_SIZE 10

typedef struct {
    char operation[30];
    float num1;
    float num2;
    float result;
} Calculation;

// ---------------- Menu and History Functions ----------------

void show_menu() {
    printf("\n*** Advanced Calculator ***\n");
    printf("1. Add\n");
    printf("2. Subtract\n");
    printf("3. Multiply\n");
    printf("4. Divide\n");
    printf("5. Power (x^y)\n");
    printf("6. Square Root\n");
    printf("7. Average\n");
    printf("8. Factorial\n");
    printf("9. Matrix Addition\n");
    printf("10. Matrix Multiplication\n");
    printf("11. Matrix Inversion\n");
    printf("12. Matrix Determinant\n");
    printf("13. Matrix Rank\n");
    printf("14. Matrix Transpose\n");
    printf("15. Complex Number Operations (Add, Subtract, Multiply, Divide)\n");
    printf("16. Exponential (exp)\n");
    printf("17. Logarithm (log)\n");
    printf("18. Gamma Function\n");
    printf("19. Bessel Function\n");
    printf("20. Unit Conversion (meters to cm, km to miles, degrees to radians)\n");
    printf("21. Statistical Operations (Median, Variance, Std Dev, Correlation, Linear Regression)\n");
    printf("22. Show History\n");
    printf("23. Clear History\n");
    printf("24. Trigonometric Operations (Sin, Cos, Tan)\n");
    printf("25. Exit\n");
    printf("Choose an option (1-25): ");
}

void save_history_to_file(Calculation history[], int count) {
    FILE *file = fopen("history.txt", "w");
    if (file == NULL) {
        printf("Error opening file to save history!\n");
        return;
    }
    for (int i = 0; i < count; i++) {
        fprintf(file, "%s: %.2f and %.2f = %.2f\n", history[i].operation, history[i].num1, history[i].num2, history[i].result);
    }
    fclose(file);
}

void load_history_from_file(Calculation history[], int *count) {
    FILE *file = fopen("history.txt", "r");
    if (file == NULL) {
        // printf("No history file found.\n");
        return;
    }
    while (fscanf(file, "%s: %f and %f = %f\n", history[*count].operation, &history[*count].num1, &history[*count].num2, &history[*count].result) != EOF) {
        (*count)++;
    }
    fclose(file);
}

void show_history(Calculation history[], int count) {
    if (count == 0) {
        printf("No history available.\n");
    } else {
        for (int i = 0; i < count; i++) {
            printf("%d. %s: %.2f and %.2f = %.2f\n", i + 1, history[i].operation, history[i].num1, history[i].num2, history[i].result);
        }
    }
}

void clear_history(Calculation history[], int *count) {
    *count = 0;
    save_history_to_file(history, *count); // Clear the file as well
    printf("History cleared.\n");
}

// ---------------- Basic Mathematical Functions ----------------

long long factorial(int n) {
    if (n <= 1)
        return 1;
    return n * factorial(n - 1);
}

// ---------------- Matrix Operations ----------------

// Matrix Addition
void matrix_addition() {
    int rows, cols;
    printf("Enter the number of rows and columns for matrices: ");
    scanf("%d %d", &rows, &cols);
    float matrix1[rows][cols], matrix2[rows][cols], result[rows][cols];

    printf("Enter elements of first matrix:\n");
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++){
            printf("Matrix1[%d][%d]: ", i+1, j+1);
            scanf("%f", &matrix1[i][j]);
        }

    printf("Enter elements of second matrix:\n");
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++){
            printf("Matrix2[%d][%d]: ", i+1, j+1);
            scanf("%f", &matrix2[i][j]);
        }

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            result[i][j] = matrix1[i][j] + matrix2[i][j];

    printf("Result of Matrix Addition:\n");
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            printf("%.2f ", result[i][j]);
        }
        printf("\n");
    }
}

// Matrix Multiplication
void matrix_multiplication() {
    int rows1, cols1, rows2, cols2;
    printf("Enter dimensions of first matrix (rows cols): ");
    scanf("%d %d", &rows1, &cols1);
    printf("Enter dimensions of second matrix (rows cols): ");
    scanf("%d %d", &rows2, &cols2);
    if (cols1 != rows2) {
        printf("Error: Incompatible dimensions for multiplication.\n");
        return;
    }
    float matrix1[rows1][cols1], matrix2[rows2][cols2], result[rows1][cols2];
    printf("Enter elements of first matrix:\n");
    for (int i = 0; i < rows1; i++)
        for (int j = 0; j < cols1; j++){
            printf("Matrix1[%d][%d]: ", i+1, j+1);
            scanf("%f", &matrix1[i][j]);
        }
    printf("Enter elements of second matrix:\n");
    for (int i = 0; i < rows2; i++)
        for (int j = 0; j < cols2; j++){
            printf("Matrix2[%d][%d]: ", i+1, j+1);
            scanf("%f", &matrix2[i][j]);
        }
    for (int i = 0; i < rows1; i++){
        for (int j = 0; j < cols2; j++){
            result[i][j] = 0;
            for (int k = 0; k < cols1; k++){
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
    printf("Result of Matrix Multiplication:\n");
    for (int i = 0; i < rows1; i++){
        for (int j = 0; j < cols2; j++){
            printf("%.2f ", result[i][j]);
        }
        printf("\n");
    }
}

// Matrix Inversion (using Gaussian elimination for square matrix)
void matrix_inversion() {
    int n;
    printf("Enter the size of the square matrix: ");
    scanf("%d", &n);
    float matrix[n][n], inverse[n][n], temp;
    int i, j, k;
    printf("Enter elements of matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++){
            printf("Matrix[%d][%d]: ", i+1, j+1);
            scanf("%f", &matrix[i][j]);
        }
    // Initialize inverse as identity matrix
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            inverse[i][j] = (i == j) ? 1 : 0;
    // Forward elimination
    for (i = 0; i < n; i++){
        temp = matrix[i][i];
        if (temp == 0) {
            printf("Matrix is singular and cannot be inverted.\n");
            return;
        }
        for (j = 0; j < n; j++){
            matrix[i][j] /= temp;
            inverse[i][j] /= temp;
        }
        for (j = i+1; j < n; j++){
            temp = matrix[j][i];
            for (k = 0; k < n; k++){
                matrix[j][k] -= matrix[i][k] * temp;
                inverse[j][k] -= inverse[i][k] * temp;
            }
        }
    }
    // Back substitution
    for (i = n-1; i >= 0; i--){
        for (j = i-1; j >= 0; j--){
            temp = matrix[j][i];
            for (k = 0; k < n; k++){
                matrix[j][k] -= matrix[i][k] * temp;
                inverse[j][k] -= inverse[i][k] * temp;
            }
        }
    }
    printf("Inverse Matrix:\n");
    for (i = 0; i < n; i++){
        for (j = 0; j < n; j++){
            printf("%.2f ", inverse[i][j]);
        }
        printf("\n");
    }
}

// Matrix Determinant (recursive method)
float matrix_determinant(int n, float matrix[n][n]) {
    if (n == 1)
        return matrix[0][0];
    float det = 0, temp[n][n];
    int sign = 1;
    for (int f = 0; f < n; f++){
        // Build submatrix for minor
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

// Matrix Rank (using row echelon form)
void matrix_rank() {
    int rows, cols;
    printf("Enter the number of rows and columns of the matrix: ");
    scanf("%d %d", &rows, &cols);
    float matrix[rows][cols];
    printf("Enter the elements of the matrix:\n");
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++){
            printf("Element[%d][%d]: ", i+1, j+1);
            scanf("%f", &matrix[i][j]);
        }
    int rank = cols;
    for (int row = 0; row < rank; row++){
        if (fabs(matrix[row][row]) > 1e-6) {
            for (int col = 0; col < rows; col++){
                if (col != row) {
                    float mult = matrix[col][row] / matrix[row][row];
                    for (int i = 0; i < rank; i++){
                        matrix[col][i] -= mult * matrix[row][i];
                    }
                }
            }
        } else {
            rank--;
            for (int i = 0; i < rows; i++){
                matrix[i][row] = matrix[i][row+1];
            }
            row--;
        }
    }
    printf("Rank of the matrix: %d\n", rank);
}

// Matrix Transpose
void matrix_transpose() {
    int rows, cols;
    printf("Enter the number of rows and columns of the matrix: ");
    scanf("%d %d", &rows, &cols);
    float matrix[rows][cols], transpose[cols][rows];
    printf("Enter the elements of the matrix:\n");
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++){
            printf("Element[%d][%d]: ", i+1, j+1);
            scanf("%f", &matrix[i][j]);
        }
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            transpose[j][i] = matrix[i][j];
        }
    }
    printf("Transpose of the matrix:\n");
    for (int i = 0; i < cols; i++){
        for (int j = 0; j < rows; j++){
            printf("%.2f ", transpose[i][j]);
        }
        printf("\n");
    }
}

// ---------------- Complex Number Operations ----------------

void complex_operations() {
    double complex num1, num2, result;
    double real1, imag1, real2, imag2;
    int operation;
    printf("Enter the real and imaginary parts of the first complex number (real imag): ");
    scanf("%lf %lf", &real1, &imag1);
    printf("Enter the real and imaginary parts of the second complex number (real imag): ");
    scanf("%lf %lf", &real2, &imag2);
    num1 = real1 + imag1 * I;
    num2 = real2 + imag2 * I;
    printf("Choose operation (1: Add, 2: Subtract, 3: Multiply, 4: Divide): ");
    scanf("%d", &operation);
    switch(operation) {
        case 1:
            result = num1 + num2;
            break;
        case 2:
            result = num1 - num2;
            break;
        case 3:
            result = num1 * num2;
            break;
        case 4:
            if(cabs(num2) == 0) {
                printf("Error: Division by zero!\n");
                return;
            }
            result = num1 / num2;
            break;
        default:
            printf("Invalid operation.\n");
            return;
    }
    printf("Result: %.2f + %.2fi\n", creal(result), cimag(result));
}

// ---------------- Special Mathematical Functions ----------------

// Exponential
void exponential_operations() {
    double x;
    printf("Enter a number: ");
    scanf("%lf", &x);
    printf("exp(%.2f) = %.2f\n", x, exp(x));
}

// Logarithm
void logarithmic_operations() {
    double x;
    printf("Enter a positive number: ");
    scanf("%lf", &x);
    if (x <= 0) {
        printf("Error: Logarithm undefined for zero or negative numbers.\n");
        return;
    }
    printf("log(%.2f) = %.2f\n", x, log(x));
}

// Gamma Function using tgamma from math.h
void gamma_function() {
    double x;
    printf("Enter a number: ");
    scanf("%lf", &x);
    printf("Gamma(%.2f) = %.2f\n", x, tgamma(x));
}

// Bessel Function J0 (from math.h; ensure your compiler supports it)
void bessel_function() {
    double x;
    printf("Enter a number: ");
    scanf("%lf", &x);
    printf("Bessel J0(%.2f) = %.2f\n", x, j0(x));
}

// ---------------- Unit Conversion ----------------

void unit_conversion() {
    int option;
    float value;
    printf("Choose conversion type:\n");
    printf("1. Meters to Centimeters\n");
    printf("2. Kilometers to Miles\n");
    printf("3. Degrees to Radians\n");
    printf("4. Radians to Degrees\n");
    printf("Your choice: ");
    scanf("%d", &option);
    printf("Enter the value: ");
    scanf("%f", &value);
    switch(option) {
        case 1:
            printf("%.2f meters = %.2f centimeters\n", value, value * 100);
            break;
        case 2:
            printf("%.2f kilometers = %.2f miles\n", value, value * 0.621371);
            break;
        case 3:
            printf("%.2f degrees = %.2f radians\n", value, value * (M_PI / 180));
            break;
        case 4:
            printf("%.2f radians = %.2f degrees\n", value, value * (180 / M_PI));
            break;
        default:
            printf("Invalid conversion option.\n");
    }
}

// ---------------- Statistical Operations ----------------

void statistical_operations() {
    int option;
    printf("Choose statistical operation:\n");
    printf("1. Descriptive Statistics (Median, Variance, Standard Deviation)\n");
    printf("2. Correlation and Linear Regression\n");
    printf("Your choice: ");
    scanf("%d", &option);

    if(option == 1) {
        int n;
        printf("Enter number of elements: ");
        scanf("%d", &n);
        float data[n];
        printf("Enter %d numbers:\n", n);
        for (int i = 0; i < n; i++){
            scanf("%f", &data[i]);
        }
        // Compute mean
        float sum = 0;
        for (int i = 0; i < n; i++){
            sum += data[i];
        }
        float mean = sum / n;
        // Compute variance
        float variance = 0;
        for (int i = 0; i < n; i++){
            variance += (data[i] - mean) * (data[i] - mean);
        }
        variance /= n;
        float std_dev = sqrt(variance);
        // Compute median (sort the array)
        for (int i = 0; i < n - 1; i++){
            for (int j = i + 1; j < n; j++){
                if(data[i] > data[j]) {
                    float temp = data[i];
                    data[i] = data[j];
                    data[j] = temp;
                }
            }
        }
        float median;
        if(n % 2 == 0)
            median = (data[n/2 - 1] + data[n/2]) / 2;
        else
            median = data[n/2];
        printf("Mean = %.2f\n", mean);
        printf("Median = %.2f\n", median);
        printf("Variance = %.2f\n", variance);
        printf("Standard Deviation = %.2f\n", std_dev);
    } else if(option == 2) {
        int n;
        printf("Enter number of data points: ");
        scanf("%d", &n);
        float x[n], y[n];
        printf("Enter %d values for X:\n", n);
        for (int i = 0; i < n; i++){
            scanf("%f", &x[i]);
        }
        printf("Enter %d values for Y:\n", n);
        for (int i = 0; i < n; i++){
            scanf("%f", &y[i]);
        }
        // Compute means
        float sum_x = 0, sum_y = 0;
        for (int i = 0; i < n; i++){
            sum_x += x[i];
            sum_y += y[i];
        }
        float mean_x = sum_x / n, mean_y = sum_y / n;
        // Compute covariance and variance_x
        float covariance = 0, variance_x = 0;
        for (int i = 0; i < n; i++){
            covariance += (x[i] - mean_x) * (y[i] - mean_y);
            variance_x += (x[i] - mean_x) * (x[i] - mean_x);
        }
        covariance /= n;
        variance_x /= n;
        // Slope (b) and intercept (a)
        float b = covariance / variance_x;
        float a = mean_y - b * mean_x;
        // Compute correlation coefficient
        float std_x = 0, std_y = 0;
        for (int i = 0; i < n; i++){
            std_x += (x[i] - mean_x) * (x[i] - mean_x);
            std_y += (y[i] - mean_y) * (y[i] - mean_y);
        }
        std_x = sqrt(std_x / n);
        std_y = sqrt(std_y / n);
        float correlation = covariance / (std_x * std_y);
        printf("Correlation coefficient = %.2f\n", correlation);
        printf("Linear Regression Line: Y = %.2f + %.2f * X\n", a, b);
    } else {
        printf("Invalid statistical operation option.\n");
    }
}

// ---------------- Trigonometric Operations ----------------

void trigonometric_operations() {
    float angle;
    int trig_choice;
    printf("Enter the angle in radians: ");
    scanf("%f", &angle);
    printf("Choose operation: 1. Sin, 2. Cos, 3. Tan: ");
    scanf("%d", &trig_choice);
    switch(trig_choice) {
        case 1:
            printf("Sin(%.2f) = %.2f\n", angle, sin(angle));
            break;
        case 2:
            printf("Cos(%.2f) = %.2f\n", angle, cos(angle));
            break;
        case 3:
            printf("Tan(%.2f) = %.2f\n", angle, tan(angle));
            break;
        default:
            printf("Invalid choice for trigonometric operation.\n");
    }
}

// ---------------- Main Function ----------------

int main() {
    Calculation history[MAX_HISTORY];
    int history_count = 0;
    load_history_from_file(history, &history_count);

    while (1) {
        show_menu();
        int choice;
        scanf("%d", &choice);
        float num1, num2, result;

        if (choice == 25) {
            save_history_to_file(history, history_count);
            printf("Goodbye!\n");
            break;
        }
        if (choice == 1) {
            printf("Enter two numbers: ");
            scanf("%f %f", &num1, &num2);
            result = num1 + num2;
            history[history_count++] = (Calculation){"Addition", num1, num2, result};
            printf("Result: %.2f\n", result);
        } else if (choice == 2) {
            printf("Enter two numbers: ");
            scanf("%f %f", &num1, &num2);
            result = num1 - num2;
            history[history_count++] = (Calculation){"Subtraction", num1, num2, result};
            printf("Result: %.2f\n", result);
        } else if (choice == 3) {
            printf("Enter two numbers: ");
            scanf("%f %f", &num1, &num2);
            result = num1 * num2;
            history[history_count++] = (Calculation){"Multiplication", num1, num2, result};
            printf("Result: %.2f\n", result);
        } else if (choice == 4) {
            printf("Enter two numbers: ");
            scanf("%f %f", &num1, &num2);
            if(num2 == 0) {
                printf("Error: Cannot divide by zero.\n");
                continue;
            }
            result = num1 / num2;
            history[history_count++] = (Calculation){"Division", num1, num2, result};
            printf("Result: %.2f\n", result);
        } else if (choice == 5) {
            printf("Enter base and exponent: ");
            scanf("%f %f", &num1, &num2);
            result = pow(num1, num2);
            history[history_count++] = (Calculation){"Power", num1, num2, result};
            printf("Result: %.2f\n", result);
        } else if (choice == 6) {
            printf("Enter a number for square root: ");
            scanf("%f", &num1);
            if(num1 < 0) {
                printf("Error: Negative input for square root.\n");
                continue;
            }
            result = sqrt(num1);
            history[history_count++] = (Calculation){"Square Root", num1, 0, result};
            printf("Result: %.2f\n", result);
        } else if (choice == 7) {
            printf("Enter two numbers for average: ");
            scanf("%f %f", &num1, &num2);
            result = (num1 + num2) / 2;
            history[history_count++] = (Calculation){"Average", num1, num2, result};
            printf("Result: %.2f\n", result);
        } else if (choice == 8) {
            printf("Enter a number for factorial: ");
            scanf("%f", &num1);
            if(num1 < 0) {
                printf("Error: Factorial of negative number not defined.\n");
                continue;
            }
            long long fact = factorial((int)num1);
            history[history_count++] = (Calculation){"Factorial", num1, 0, (float)fact};
            printf("Result: %lld\n", fact);
        } else if (choice == 9) {
            matrix_addition();
        } else if (choice == 10) {
            matrix_multiplication();
        } else if (choice == 11) {
            matrix_inversion();
        } else if (choice == 12) {
            printf("Enter size of square matrix: ");
            int n;
            scanf("%d", &n);
            float matrix[n][n];
            printf("Enter elements of the matrix:\n");
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++){
                    scanf("%f", &matrix[i][j]);
                }
            result = matrix_determinant(n, matrix);
            printf("Determinant: %.2f\n", result);
        } else if (choice == 13) {
            matrix_rank();
        } else if (choice == 14) {
            matrix_transpose();
        } else if (choice == 15) {
            complex_operations();
        } else if (choice == 16) {
            exponential_operations();
        } else if (choice == 17) {
            logarithmic_operations();
        } else if (choice == 18) {
            gamma_function();
        } else if (choice == 19) {
            bessel_function();
        } else if (choice == 20) {
            unit_conversion();
        } else if (choice == 21) {
            statistical_operations();
        } else if (choice == 22) {
            show_history(history, history_count);
        } else if (choice == 23) {
            clear_history(history, &history_count);
        } else if (choice == 24) {
            trigonometric_operations();
        } else {
            printf("Invalid option. Please try again.\n");
        }
        printf("Operation complete.\n");
    }
    return 0;
}
