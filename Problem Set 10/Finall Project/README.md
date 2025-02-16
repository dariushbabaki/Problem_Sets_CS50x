# Advanced Calculator
#### Video Demo: <https://youtube.com/shorts/Ymf0ax5b5LE?si=S9PMPePeVQ5x0-Tm>
#### Description:

The **Advanced Calculator** is a C-based project designed to provide a powerful tool for performing a variety of mathematical operations. This calculator not only supports basic arithmetic functions such as addition, subtraction, multiplication, and division, but also handles more advanced calculations like trigonometric functions (sine, cosine, tangent), logarithmic and exponential functions, square roots, and power operations. The calculator is user-friendly and performs calculations with both integer and floating-point numbers.

## Functionality:

### 1. **Basic Arithmetic Operations**:
   - The core functionality of the calculator includes basic arithmetic operations:
     - **Addition**: Adds two numbers together.
     - **Subtraction**: Subtracts one number from another.
     - **Multiplication**: Multiplies two numbers.
     - **Division**: Divides one number by another, with checks for division by zero.

   These operations are implemented as separate functions in the `project.c` file and return the result of the operation.

### 2. **Trigonometric Functions**:
   - The calculator supports the following trigonometric operations:
     - **Sine** (`sin`): Returns the sine of an angle (in radians).
     - **Cosine** (`cos`): Returns the cosine of an angle (in radians).
     - **Tangent** (`tan`): Returns the tangent of an angle (in radians).

   These operations are implemented using the standard C math library to handle the calculations.

### 3. **Logarithmic and Exponential Functions**:
   - The advanced calculator can compute the **natural logarithm** (`log`) and **exponential** (`exp`) functions.
     - **Logarithm**: Calculates the natural logarithm of a given number.
     - **Exponential**: Computes the exponential of a given number.

### 4. **Square Root and Power Operations**:
   - The calculator can compute the **square root** of a number and raise a number to a specified **power**.
     - **Square Root** (`sqrt`): Calculates the square root of a number.
     - **Power** (`pow`): Raises a base to a specific exponent.

## File Structure:

This project consists of two main files:

### 1. **`project.c`**:
   - This is the core file that implements all the mathematical functions required by the advanced calculator.
   - It includes the functions for arithmetic operations, trigonometric functions, logarithmic and exponential functions, square root, and power functions.
   - Each function is clearly defined, and mathematical operations are handled using the standard C math library functions (e.g., `sin()`, `cos()`, `log()`, `sqrt()`).

### 2. **`test_project.c`**:
   - This file contains unit tests for each function implemented in `project.c`.
   - The unit tests are designed to verify the correctness of each operation. For instance, it tests the result of adding two numbers, calculating the sine of an angle, and verifying that the square root of a number is computed correctly.
   - The tests are written using standard C testing practices to ensure that every aspect of the calculator functions as expected.

## Development and Design Choices:

While developing this project, the following design choices were made:

### 1. **Modular Design**:
   - The project was divided into multiple functions, each responsible for a specific type of calculation. This modular approach makes the code easier to manage and test. By separating the logic for arithmetic operations, trigonometric functions, and other mathematical calculations, the code becomes more maintainable and scalable.

### 2. **Error Handling**:
   - **Division by Zero**: One key challenge during development was handling the potential error of division by zero. I implemented a check to ensure that the divisor is not zero before performing the division. If the divisor is zero, the program displays an error message and avoids crashing.

   - **Invalid Input Handling**: Another challenge was ensuring that invalid input (such as negative numbers for square roots or logarithms) is handled gracefully. I added checks to ensure that the inputs are valid and provide error messages if the user attempts an invalid operation.

### 3. **Using the Standard C Math Library**:
   - The calculator leverages the C math library (`math.h`) for complex mathematical functions like sine, cosine, logarithms, square roots, and exponentiation. This allowed for accurate and efficient calculations without needing to manually implement these mathematical operations.

### 4. **Testing**:
   - To ensure the reliability of the project, I wrote unit tests for each of the functions implemented in `project.c`. The tests were designed to cover a variety of inputs, including edge cases like negative numbers, large numbers, and division by zero. This helped catch any potential bugs and ensured the correctness of the project.

## Challenges Faced:

During the development of this project, I encountered several challenges:

### 1. **Handling Complex Mathematical Operations**:
   - Implementing trigonometric and logarithmic functions was straightforward with the math library. However, ensuring that the calculator provided correct results, especially for edge cases like negative numbers or undefined results (such as dividing by zero), was a bit tricky. I had to carefully consider how to handle such cases to avoid crashes or incorrect outputs.

### 2. **Input Validation**:
   - Ensuring that the user inputs valid numbers and operations was another significant challenge. I had to handle situations where the user might input non-numeric characters or attempt operations that are mathematically undefined. Input validation was essential to make the calculator robust.

### 3. **Testing the Functions**:
   - Writing comprehensive unit tests that cover all possible edge cases was challenging. I had to carefully think through all possible inputs to ensure that the calculator works as expected under various conditions.

## Conclusion:

The **Advanced Calculator** project provides a comprehensive solution for performing basic and advanced mathematical operations. It features robust error handling, accurate computations using the C math library, and thorough unit testing to verify the correctness of each function. This project has not only honed my skills in C programming but also taught me valuable lessons about modular design, error handling, and testing in software development.

This calculator can be further expanded to include additional functions, such as handling different types of units (e.g., converting between radians and degrees for trigonometric functions) or supporting more complex mathematical operations. The project lays the foundation for building more sophisticated tools in the future.
