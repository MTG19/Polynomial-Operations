#include <iostream>
#include <fstream>
#include <limits>
using namespace std;

// Function to display a polynomial
void displayPolynomial(int* pol, int order, int constantTerm) {
    bool firstTerm = true;
    for (int i = order; i >= 0; --i) {
        if (pol[i] != 0) {
            if (!firstTerm) {
                cout << (pol[i] > 0 ? " + " : " - ");
            } else if (pol[i] < 0) {
                cout << "-";
            }
            cout << abs(pol[i]);
            if (i > 0) cout << "x" << (i > 1 ? "^" + to_string(i) : "");
            firstTerm = false;
        }
    }
    if (firstTerm) cout << "0";
    cout << " = " << constantTerm << "\n";
}

// Function to add two polynomials
int* Sum_of_Polynomials(int* pol1, int order1, int* pol2, int order2, int& orderSum, int constantTerm1, int constantTerm2, int& constantSum) {
    orderSum = max(order1, order2);
    int* sum = new int[orderSum + 1]{0};
    for (int i = 0; i <= order1; i++) sum[i] += pol1[i];
    for (int i = 0; i <= order2; i++) sum[i] += pol2[i];
    constantSum = constantTerm1 + constantTerm2;  // Update constant term
    return sum;
}

// Function to subtract two polynomials (pol2 - pol1)
int* Difference_of_Polynomials(int* pol1, int order1, int* pol2, int order2, int& orderDiff, int constantTerm1, int constantTerm2, int& constantDiff) {
    orderDiff = max(order1, order2);
    int* diff = new int[orderDiff + 1]{0};
    for (int i = 0; i <= order1; i++) diff[i] -= pol1[i];  // Subtract pol1
    for (int i = 0; i <= order2; i++) diff[i] += pol2[i];  // Add pol2
    constantDiff = constantTerm2 - constantTerm1;  // Update constant term
    return diff;
}

// Function to read polynomial input
bool readPolynomial(int*& pol, int& order, int& constantTerm, istream& input) {
    input >> order;
    if (order < 0) {
        cout << "Error: Order cannot be negative.\n";
        return false;
    }
    input >> constantTerm;  // Read the constant term first
    pol = new int[order + 1]{};
    for (int i = 0; i <= order; i++) {  // Read coefficients from x^0 to x^order
        if (!(input >> pol[i])) {
            cout << "Error: Not enough coefficients provided.\n";
            delete[] pol;
            return false;
        }
    }
    return true;
}

int main() {
    int choice;
    int repeat;
    cout<<"\n_________________________________________\n"
            "Welcome to Polynomial Operations Program!\n"
            "_________________________________________\n";

    do {
        int order1, order2;
        int constantTerm1, constantTerm2;
        int* pol1 = nullptr;
        int* pol2 = nullptr;

        cout << "\nChoose input method:\n1. Manual input\n2. Read from file\nEnter choice: ";
        while (!(cin >> choice) || (choice != 1 && choice != 2)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please enter a valid choice (1 or 2): ";
        }

        if (choice == 1) {
            // Manual input
            cout << "\nEnter first polynomial order: ";
            cin >> order1;
            if (order1 < 0) {
                cout << "Error: Order cannot be negative.\n";
                return 1;
            }
            cout << "Enter the constant term (after '=') followed by " << (order1 + 1) << " coefficients (from x^0 to x^" << order1 << "): ";
            pol1 = new int[order1 + 1]{};
            cin >> constantTerm1;
            for (int i = 0; i <= order1; i++) {
                if (!(cin >> pol1[i])) {
                    cout << "Error: Not enough coefficients provided.\n";
                    delete[] pol1;
                    return 1;
                }
            }

            cout << "Enter second polynomial order: ";
            cin >> order2;
            if (order2 < 0) {
                cout << "Error: Order cannot be negative.\n";
                delete[] pol1;
                return 1;
            }
            cout << "Enter the constant term (after '=') followed by " << (order2 + 1) << " coefficients (from x^0 to x^" << order2 << "): ";
            pol2 = new int[order2 + 1]{};
            cin >> constantTerm2;
            for (int i = 0; i <= order2; i++) {
                if (!(cin >> pol2[i])) {
                    cout << "Error: Not enough coefficients provided.\n";
                    delete[] pol1;
                    delete[] pol2;
                    return 1;
                }
            }
        } else {
            // File input
            ifstream inputFile;
            string filename;
            while (true) {
                cout << "\nEnter filename: ";
                cin >> filename;
                inputFile.open(filename);
                if (inputFile) break;
                cout << "File not found! Please enter a valid filename.\n";
            }

            if (!readPolynomial(pol1, order1, constantTerm1, inputFile)) {
                return 1;
            }
            if (!readPolynomial(pol2, order2, constantTerm2, inputFile)) {
                delete[] pol1;
                return 1;
            }

            inputFile.close();
        }

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
        // Ask the user if they want to perform another operation
        cout << "_________________________________________\n\n"
                "Do you want to perform another operation? \n1.Yes\n2.No\nEnter choice (1/2): ";

        while (!(cin >> repeat) || (repeat != 1 && repeat != 2)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please enter a valid choice (1 or 2): ";
        }


    } while (repeat == 1 );
    cout << "\n_____________________________\n"
              "Exiting the Program. Goodbye!\n"
              "_____________________________\n";

    return 0;
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

***/
