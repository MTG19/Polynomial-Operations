#include <iostream>
#include <fstream>
#include <limits>
using namespace std;

// Function to display a polynomial
void displayPolynomial(int* pol, int order) {
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
    cout << " = 0\n";
}

// Function to add two polynomials
int* Sum_of_Polynomials(int* pol1, int order1, int* pol2, int order2, int& orderSum) {
    orderSum = max(order1, order2);
    int* sum = new int[orderSum + 1]{};
    for (int i = 0; i <= order1; i++) sum[i] = pol1[i];
    for (int i = 0; i <= order2; i++) sum[i] += pol2[i];
    return sum;
}

// Function to subtract two polynomials
int* Difference_of_Polynomials(int* pol1, int order1, int* pol2, int order2, int& orderDiff) {
    orderDiff = max(order1, order2);
    int* diff = new int[orderDiff + 1]{};
    for (int i = 0; i <= order1; i++) diff[i] = pol1[i];
    for (int i = 0; i <= order2; i++) diff[i] -= pol2[i];
    return diff;
}

// Function to read polynomial input
void readPolynomial(int*& pol, int& order, istream& input) {
    input >> order;
    pol = new int[order + 1]{};
    for (int i = order; i >= 0; i--) {
        input >> pol[i];  // Read coefficients from highest to lowest degree
    }
}

int main() {
    int order1, order2;
    int* pol1;
    int* pol2;
    int choice;

    cout << "Choose input method:\n1. Manual input\n2. Read from file\nEnter choice: ";
    while (!(cin >> choice) || (choice != 1 && choice != 2)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Please enter a valid choice (1 or 2): ";
    }

    if (choice == 1) {
        // Manual input
        cout << "Enter first polynomial:\n";
        readPolynomial(pol1, order1, cin);

        cout << "Enter second polynomial:\n";
        readPolynomial(pol2, order2, cin);
    } else {
        // File input
        ifstream inputFile;
        string filename;
        while (true) {
            cout << "Enter filename: ";
            cin >> filename;
            inputFile.open(filename);
            if (inputFile) break;
            cout << "File not found! Please enter a valid filename.\n";
        }

        readPolynomial(pol1, order1, inputFile);
        readPolynomial(pol2, order2, inputFile);

        inputFile.close();
    }

    // Display the polynomials
    cout << "First polynomial: ";
    displayPolynomial(pol1, order1);
    cout << "Second polynomial: ";
    displayPolynomial(pol2, order2);

    // Compute sum and difference
    int orderSum, orderDiff;
    int* sum = Sum_of_Polynomials(pol1, order1, pol2, order2, orderSum);
    int* diff = Difference_of_Polynomials(pol1, order1, pol2, order2, orderDiff);

    // Display results
    cout << "Sum of polynomials: ";
    displayPolynomial(sum, orderSum);
    cout << "Difference of polynomials: ";
    displayPolynomial(diff, orderDiff);

    // Free allocated memory
    delete[] pol1;
    delete[] pol2;
    delete[] sum;
    delete[] diff;

    return 0;
}
