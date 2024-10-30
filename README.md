Overview

This project implements a C program that performs Lagrange interpolation to find the constant term (c) from a set of points provided in a JSON file. The points consist of values in different numerical bases, which are converted to decimal before interpolation.

Prerequisites

Before running the program, ensure you have the following installed:

A C compiler (such as GCC) that supports C99.
The json-c library for handling JSON data.
The math.h library for mathematical operations.
Setup

Clone the Repository: Clone this repository to your local machine.
Install Dependencies: Make sure you have the json-c library installed. On Windows, you may need to follow specific instructions to set up this library.
Prepare Input File: Create a JSON file named input.json in the same directory as your compiled program. The file should contain the data structure as outlined in the project description.
Running the Program

Open a terminal or command prompt.
Navigate to the directory where the program is located.
Compile the program using your C compiler. For example, with GCC:
gcc -o lagrange_interpolation lagrange_interpolation.c -ljson-c -lm
Run the compiled program:
./lagrange_interpolation (on Unix-based systems)
lagrange_interpolation.exe (on Windows)
Explanation of Code

Include Headers: The program includes necessary libraries for input/output, JSON handling, mathematical operations, and string manipulation.
Define Structure: A structure named Point is defined to hold the x and y coordinates of each point.
Convert to Decimal: A function convert_to_decimal is defined to convert values from a given base (e.g., binary, octal, hexadecimal) to decimal. It iterates over each character of the value, converting it to its respective decimal equivalent.
Lagrange Interpolation: A function lagrange_interpolation computes the constant term using the Lagrange interpolation formula, which combines all points to derive the polynomial.
Main Function: The main function:
Opens and reads the JSON input file.
Parses the JSON data to retrieve the number of points and their respective values.
Converts each value to decimal and stores them in the points array.
Checks if enough points are available for interpolation.
Calls the interpolation function to calculate and print the constant term (c).
Output

Upon successful execution, the program prints the decoded points and the resulting constant term (c) based on the Lagrange interpolation.

Troubleshooting

Ensure that the input.json file is correctly formatted.
Check for any errors related to file reading or JSON parsing.
Verify that the base values in the JSON correspond correctly to the provided number values.
Conclusion

This program effectively demonstrates how to perform Lagrange interpolation using values in various bases, showcasing the integration of JSON data handling in C.






