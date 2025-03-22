إليك وصفًا مناسبًا لمشروعك لوضعه في **GitHub**:  

---

# **Polynomial Operations Using Pointers**  
This project implements polynomial operations using **dynamic memory allocation** in C++. The program allows users to input two polynomials and perform the following operations:  

## **Features**  
✔️ **Display a polynomial** in a readable mathematical format.  
✔️ **Add two polynomials** and display the result.  
✔️ **Subtract two polynomials** (subtract the first from the second).  
✔️ **Handle polynomials of different orders** dynamically.  
✔️ **Support both manual input and file input**.  

## **Input Format**  
- The user enters the **order of each polynomial**.  
- The coefficients are entered from **constant term to highest-degree term** (e.g., for `2x² + 3x + 1`, input is `1 3 2`).  
- The program supports input from a **file or manual entry**.  

## **Output Format**  
- The polynomials are displayed in a **mathematical format** (e.g., `2x^2 + 3x + 1 = 0`).  
- The **sum and difference** of the polynomials are displayed correctly.  

## **Example 1**  
### **Input:**  
```
Order of first polynomial: 2  
Enter polynomial: 0 1 3 2  
Order of second polynomial: 4  
Enter polynomial: 8 0 4 0 0 3  
```  
### **Output:**  
```
First polynomial: 2x^2 + 3x + 1 = 0  
Second polynomial: 3x^4 + 4x = 8  
Sum of polynomials: 3x^4 + 2x^2 + 7x + 1 = 8  
Difference of polynomials: 3x^4 - 2x^2 + x - 1 = 8  
```  

## **Technologies Used**  
- **C++**
- **Dynamic Memory Allocation**  
- **File Handling (optional input method)**  


## **Test Cases**  
✔️ The program includes **test cases** to validate polynomial operations, ensuring correctness in different scenarios.

---
