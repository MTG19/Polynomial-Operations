#include <iostream>  // Include the input/output stream library
#include <fstream>   // Include the file stream library for file handling
#include <limits>    // Include the limits library for handling input validation
using namespace std; // Use the standard namespace

// Function to display a polynomial in a readable format
void displayPolynomial(int* pol, int order, int constantTerm) {
    bool firstTerm = true; // Flag to check if it's the first term in the polynomial
    for (int i = order; i >= 0; --i) { // Loop from the highest degree to the lowest
        if (pol[i] != 0) { // Only display terms with non-zero coefficients
            if (!firstTerm) { // If it's not the first term, add a "+" or "-" sign
                cout << (pol[i] > 0 ? " + " : " - ");
            } else if (pol[i] < 0) { // If it's the first term and negative, add a "-" sign
                cout << "-";
            }
            cout << abs(pol[i]); // Display the absolute value of the coefficient
            if (i > 0) cout << "x" << (i > 1 ? "^" + to_string(i) : ""); // Display "x" and the degree if needed
            firstTerm = false; // Mark that the first term has been displayed
        }
    }
    if (firstTerm) cout << "0"; // If all coefficients are zero, display "0"
    cout << " = " << constantTerm << "\n"; // Display the constant term after "="
}

// Function to add two polynomials
int* Sum_of_Polynomials(int* pol1, int order1, int* pol2, int order2, int& orderSum, int constantTerm1, int constantTerm2, int& constantSum) {
    orderSum = max(order1, order2); // The order of the sum is the maximum of the two orders
    int* sum = new int[orderSum + 1]{0}; // Dynamically allocate memory for the sum polynomial
    for (int i = 0; i <= order1; i++) sum[i] += pol1[i]; // Add coefficients of the first polynomial
    for (int i = 0; i <= order2; i++) sum[i] += pol2[i]; // Add coefficients of the second polynomial
    constantSum = constantTerm1 + constantTerm2; // Update the constant term of the sum
    return sum; // Return the sum polynomial
}

// Function to subtract two polynomials (pol2 - pol1)
int* Difference_of_Polynomials(int* pol1, int order1, int* pol2, int order2, int& orderDiff, int constantTerm1, int constantTerm2, int& constantDiff) {
    orderDiff = max(order1, order2); // The order of the difference is the maximum of the two orders
    int* diff = new int[orderDiff + 1]{0}; // Dynamically allocate memory for the difference polynomial
    for (int i = 0; i <= order1; i++) diff[i] -= pol1[i]; // Subtract coefficients of the first polynomial
    for (int i = 0; i <= order2; i++) diff[i] += pol2[i]; // Add coefficients of the second polynomial
    constantDiff = constantTerm2 - constantTerm1; // Update the constant term of the difference
    return diff; // Return the difference polynomial
}

// Function to read polynomial input from a stream (file or manual input)
bool readPolynomial(int*& pol, int& order, int& constantTerm, istream& input) {
    input >> order; // Read the order of the polynomial
    if (order < 0) { // Check if the order is negative
        cout << "Error: Order cannot be negative.\n";
        return false; // Return false if the order is invalid
    }
    input >> constantTerm; // Read the constant term (after '=')
    pol = new int[order + 1]{}; // Dynamically allocate memory for the polynomial coefficients
    for (int i = 0; i <= order; i++) { // Read coefficients from x^0 to x^order
        if (!(input >> pol[i])) { // Check if the input is valid
            cout << "Error: Not enough coefficients provided.\n";
            delete[] pol; // Free allocated memory
            return false; // Return false if there's an error
        }
    }
    return true; // Return true if the polynomial is read successfully
}

int main() {
    int choice; // Variable to store the user's choice (manual or file input)
    int repeat; // Variable to store the user's choice to repeat or exit
    cout << "\n_________________________________________\n"
            "Welcome to Polynomial Operations Program!\n"
            "_________________________________________\n";

    do {
        int order1, order2; // Variables to store the orders of the two polynomials
        int constantTerm1, constantTerm2; // Variables to store the constant terms of the two polynomials
        int* pol1 = nullptr; // Pointer to store the coefficients of the first polynomial
        int* pol2 = nullptr; // Pointer to store the coefficients of the second polynomial
        bool errorOccurred = false; // Flag to track if an error occurred during input

        cout << "\nChoose input method:\n1. Manual input\n2. Read from file\nEnter choice: ";
        while (!(cin >> choice) || (choice != 1 && choice != 2)) { // Validate the user's choice
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
            cout << "Please enter a valid choice (1 or 2): ";
        }

        if (choice == 1) {
            // Manual input
            cout << "\nEnter first polynomial order: ";
            cin >> order1; // Read the order of the first polynomial
            if (order1 < 0) { // Check if the order is negative
                cout << "Error: Order cannot be negative.\n";
                errorOccurred = true; // Set the error flag
            } else {
                cout << "Enter the constant term (after '=') followed by " << (order1 + 1) << " coefficients (from x^0 to x^" << order1 << "): ";
                pol1 = new int[order1 + 1]{}; // Allocate memory for the first polynomial
                cin >> constantTerm1; // Read the constant term
                for (int i = 0; i <= order1; i++) { // Read the coefficients
                    if (!(cin >> pol1[i])) { // Check if the input is valid
                        cout << "Error: Not enough coefficients provided.\n";
                        delete[] pol1; // Free allocated memory
                        errorOccurred = true; // Set the error flag
                        break; // Exit the loop
                    }
                }
            }

            if (!errorOccurred) { // If no error occurred for the first polynomial
                cout << "Enter second polynomial order: ";
                cin >> order2; // Read the order of the second polynomial
                if (order2 < 0) { // Check if the order is negative
                    cout << "Error: Order cannot be negative.\n";
                    delete[] pol1; // Free memory allocated for the first polynomial
                    errorOccurred = true; // Set the error flag
                } else {
                    cout << "Enter the constant term (after '=') followed by " << (order2 + 1) << " coefficients (from x^0 to x^" << order2 << "): ";
                    pol2 = new int[order2 + 1]{}; // Allocate memory for the second polynomial
                    cin >> constantTerm2; // Read the constant term
                    for (int i = 0; i <= order2; i++) { // Read the coefficients
                        if (!(cin >> pol2[i])) { // Check if the input is valid
                            cout << "Error: Not enough coefficients provided.\n";
                            delete[] pol1; // Free memory allocated for the first polynomial
                            delete[] pol2; // Free memory allocated for the second polynomial
                            errorOccurred = true; // Set the error flag
                            break; // Exit the loop
                        }
                    }
                }
            }
        } else {
            // File input
            ifstream inputFile; // File stream object
            string filename; // Variable to store the filename
            while (true) {
                cout << "\nEnter filename: ";
                cin >> filename; // Read the filename
                inputFile.open(filename); // Open the file
                if (inputFile) break; // Exit the loop if the file is opened successfully
                cout << "File not found! Please enter a valid filename.\n";
            }

            if (!readPolynomial(pol1, order1, constantTerm1, inputFile)) { // Read the first polynomial from the file
                errorOccurred = true; // Set the error flag
            } else if (!readPolynomial(pol2, order2, constantTerm2, inputFile)) { // Read the second polynomial from the file
                delete[] pol1; // Free memory allocated for the first polynomial
                errorOccurred = true; // Set the error flag
            }

            inputFile.close(); // Close the file
        }

        if (!errorOccurred) { // If no error occurred during input
            // Display the polynomials
            cout << "\nFirst polynomial: ";
            displayPolynomial(pol1, order1, constantTerm1);
            cout << "Second polynomial: ";
            displayPolynomial(pol2, order2, constantTerm2);

            // Compute sum and difference
            int orderSum, orderDiff;
            int constantSum, constantDiff;
            int* sum = Sum_of_Polynomials(pol1, order1, pol2, order2, orderSum, constantTerm1, constantTerm2, constantSum);
            int* diff = Difference_of_Polynomials(pol1, order1, pol2, order2, orderDiff, constantTerm1, constantTerm2, constantDiff);

            // Display results
            cout << "Sum of polynomials: ";
            displayPolynomial(sum, orderSum, constantSum);
            cout << "Difference of polynomials: ";
            displayPolynomial(diff, orderDiff, constantDiff);

            // Free allocated memory
            delete[] pol1;
            delete[] pol2;
            delete[] sum;
            delete[] diff;
        }

        // Ask the user if they want to perform another operation
        cout << "_________________________________________\n\n"
                "Do you want to perform another operation? \n1.Yes\n2.No\nEnter choice (1/2): ";

        while (!(cin >> repeat) || (repeat != 1 && repeat != 2)) { // Validate the user's choice
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
            cout << "Please enter a valid choice (1 or 2): ";
        }

    } while (repeat == 1); // Repeat the loop if the user chooses to continue

    cout << "\n_____________________________\n"
              "Exiting the Program. Goodbye!\n"
              "_____________________________\n";

    return 0; // End of the program
}

/***
________________________________________________________________
Test Case 1:
Input:
Order of first polynomial: 2
Enter polynomial: 0 1 3 2
Order of second polynomial: 4
Enter polynomial: 8 0 4 0 0 3

Output:
First polynomial: 2x^2 + 3x + 1 = 0
Second polynomial: 3x^4 + 4x = 8
Sum of polynomials: 3x^4 + 2x^2 + 7x + 1 = 8
Difference of polynomials: 3x^4 - 2x^2 + x - 1 = 8
________________________________________________________________
Test Case 2:
Input:
Order of first polynomial: 3
Enter polynomial: 0 5 0 1 4
Order of second polynomial: 3
Enter polynomial: 0 2 3 0 6

Output:
First polynomial: 4x^3 + x^2 + 5 = 0
Second polynomial: 6x^3 + 3x + 2 = 0
Sum of polynomials: 10x^3 + x^2 + 3x + 7 = 0
Difference of polynomials: 2x^3 - x^2 + 3x - 3 = 0
________________________________________________________________
Test Case 3: Equal Degrees
Input:
Order of first polynomial: 2
Enter polynomial: 0 1 3 2
Order of second polynomial: 2
Enter polynomial: 0 2 1 4

Output:
First polynomial: 2x^2 + 3x + 1 = 2
Second polynomial: 4x^2 + 1x + 2 = 5
Sum of polynomials: 6x^2 + 4x + 3 = 7
Difference of polynomials: 2x^2 - 2x + 1 = 3
________________________________________________________________
Test Case 4: First Polynomial Degree > Second Polynomial Degree
Input:
Order of first polynomial: 3
Enter polynomial: 0 1 0 2 3
Order of second polynomial: 2
Enter polynomial: 0 2 1 4

Output:
First polynomial: 3x^3 + 2x^2 + 1 = 0
Second polynomial: 4x^2 + 1x + 2 = 0
Sum of polynomials: 3x^3 + 6x^2 + 1x + 3 = 0
Difference of polynomials: -3x^3 + 2x^2 + 1x + 1 = 0
________________________________________________________________
Test Case 5: Second Polynomial Degree > First Polynomial Degree
Input:
Order of first polynomial: 2
Enter polynomial: 0 1 3 2
Order of second polynomial: 4
Enter polynomial: 8 0 4 0 0 3

Output:
First polynomial: 2x^2 + 3x + 1 = 0
Second polynomial: 3x^4 + 4x = 8
Sum of polynomials: 3x^4 + 2x^2 + 7x + 1 = 8
Difference of polynomials: 3x^4 - 2x^2 + 1x - 1 = 8
________________________________________________________________
Test Case 6: Negative Coefficients
Input:
Order of first polynomial: 2
Enter polynomial: 0 -1 3 -2
Order of second polynomial: 2
Enter polynomial: 0 2 -1 4

Output:
First polynomial: -2x^2 + 3x - 1 = 0
Second polynomial: 4x^2 - 1x + 2 = 0
Sum of polynomials: 2x^2 + 2x + 1 = 0
Difference of polynomials: 6x^2 - 4x + 3 = 0
________________________________________________________________
Test Case 7: Constant Term is Negative
Input:
Order of first polynomial: 2
Enter polynomial: 0 1 3 2 -5
Order of second polynomial: 2
Enter polynomial: 0 2 1 4 -3

Output:
First polynomial: 2x^2 + 3x + 1 = -5
Second polynomial: 4x^2 + 1x + 2 = -3
Sum of polynomials: 6x^2 + 4x + 3 = -8
Difference of polynomials: 2x^2 - 2x + 1 = 2
________________________________________________________________
Test Case 8: Negative Order (Invalid Input)
Input:
Order of first polynomial: -2
Enter polynomial: 0 1 3 2 -5
Order of second polynomial: 2
Enter polynomial: 0 2 1 4 -3

Output:
Error: Order cannot be negative.
________________________________________________________________
Test Case 9: Insufficient Coefficients
Input:
Order of first polynomial: 2
Enter polynomial: 0 1
Order of second polynomial: 2
Enter polynomial: 0 2 -1 4

Output:
Error: Not enough coefficients provided.
________________________________________________________________
***/
