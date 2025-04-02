
#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>
#include <type_traits>

template <typename T>
class Matrix {
private:
    std::vector<std::vector<T>> data;
    int size;

public:
    // Constructor
    Matrix(int n) : size(n) {
        data.resize(n, std::vector<T>(n));
    }

    // Default constructor
    Matrix() : size(0) {}

    // Get size
    int getSize() const {
        return size;
    }

    // Access element (for reading)
    const T& operator()(int row, int col) const {
        return data[row][col];
    }

    // Access element (for writing)
    T& operator()(int row, int col) {
        return data[row][col];
    }

    // Set data from vector
    void setData(const std::vector<std::vector<T>>& newData) {
        data = newData;
        size = newData.size();
    }

    // Get raw data
    const std::vector<std::vector<T>>& getData() const {
        return data;
    }

    // Matrix addition
    Matrix<T> operator+(const Matrix<T>& other) const {
        if (size != other.size) {
            throw std::invalid_argument("Matrix dimensions do not match for addition");
        }

        Matrix<T> result(size);
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                result(i, j) = data[i][j] + other(i, j);
            }
        }
        return result;
    }

    // Matrix multiplication
    Matrix<T> operator*(const Matrix<T>& other) const {
        if (size != other.size) {
            throw std::invalid_argument("Matrix dimensions do not match for multiplication");
        }

        Matrix<T> result(size);
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                result(i, j) = 0;
                for (int k = 0; k < size; k++) {
                    result(i, j) += data[i][k] * other(k, j);
                }
            }
        }
        return result;
    }

    // Calculate sum of diagonals
    std::pair<T, T> sumDiagonals() const {
        T mainDiagonal = 0;
        T secondaryDiagonal = 0;

        for (int i = 0; i < size; i++) {
            mainDiagonal += data[i][i];
            secondaryDiagonal += data[i][size - 1 - i];
        }

        return std::make_pair(mainDiagonal, secondaryDiagonal);
    }

    // Swap rows
    bool swapRows(int row1, int row2) {
        if (row1 < 0 || row1 >= size || row2 < 0 || row2 >= size) {
            return false;
        }

        std::swap(data[row1], data[row2]);
        return true;
    }

    // Swap columns
    bool swapColumns(int col1, int col2) {
        if (col1 < 0 || col1 >= size || col2 < 0 || col2 >= size) {
            return false;
        }

        for (int i = 0; i < size; i++) {
            std::swap(data[i][col1], data[i][col2]);
        }
        return true;
    }

    // Update element
    bool updateElement(int row, int col, T value) {
        if (row < 0 || row >= size || col < 0 || col >= size) {
            return false;
        }

        data[row][col] = value;
        return true;
    }

    // Display the matrix
    void display() const {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (std::is_same<T, int>::value) {
                    std::cout << std::setw(4) << data[i][j];
                } else {
                    std::cout << std::fixed << std::setprecision(2) << std::setw(8) << data[i][j];
                }
            }
            std::cout << std::endl;
        }
    }
};

// Input stream operator for Matrix
template <typename T>
std::istream& operator>>(std::istream& in, Matrix<T>& matrix) {
    int n = matrix.getSize();
    std::vector<std::vector<T>> tempData(n, std::vector<T>(n));
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            T value;
            in >> value;
            tempData[i][j] = value;
        }
    }
    
    matrix.setData(tempData);
    return in;
}

// Output stream operator for Matrix
template <typename T>
std::ostream& operator<<(std::ostream& out, const Matrix<T>& matrix) {
    int n = matrix.getSize();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (std::is_same<T, int>::value) {
                out << std::setw(4) << matrix(i, j);
            } else {
                out << std::fixed << std::setprecision(2) << std::setw(8) << matrix(i, j);
            }
        }
        out << std::endl;
    }
    return out;
}

// Functions for polymorphism requirement (directly using std::vector)
// Function to swap rows in a vector-based matrix
template <typename T>
bool swapVectorRows(std::vector<std::vector<T>>& matrix, int row1, int row2) {
    int size = matrix.size();
    if (row1 < 0 || row1 >= size || row2 < 0 || row2 >= size) {
        return false;
    }
    
    std::swap(matrix[row1], matrix[row2]);
    return true;
}

// Function to swap columns in a vector-based matrix
template <typename T>
bool swapVectorColumns(std::vector<std::vector<T>>& matrix, int col1, int col2) {
    int size = matrix.size();
    if (col1 < 0 || col1 >= size || col2 < 0 || col2 >= size) {
        return false;
    }
    
    for (int i = 0; i < size; i++) {
        std::swap(matrix[i][col1], matrix[i][col2]);
    }
    return true;
}

// Function to update an element in a vector-based matrix
template <typename T>
bool updateVectorElement(std::vector<std::vector<T>>& matrix, int row, int col, T value) {
    int size = matrix.size();
    if (row < 0 || row >= size || col < 0 || col >= size) {
        return false;
    }
    
    matrix[row][col] = value;
    return true;
}

// Function to display a vector-based matrix
template <typename T>
void displayVectorMatrix(const std::vector<std::vector<T>>& matrix) {
    for (const auto& row : matrix) {
        for (const auto& elem : row) {
            if (std::is_same<T, int>::value) {
                std::cout << std::setw(4) << elem;
            } else {
                std::cout << std::fixed << std::setprecision(2) << std::setw(8) << elem;
            }
        }
        std::cout << std::endl;
    }
}

// Function to parse matrix data from string input
template <typename T>
bool parseMatrixDataFromString(const std::string& input, int matrixSize, 
                               Matrix<T>& matrix1, Matrix<T>& matrix2) {
    std::istringstream iss(input);
    
    // Create matrices of appropriate size
    matrix1 = Matrix<T>(matrixSize);
    matrix2 = Matrix<T>(matrixSize);
    
    // Read data for both matrices
    iss >> matrix1 >> matrix2;
    
    return true;
}

int main() {
    // For this part I set default values just for testing purposes but the functions asks you for an input file anyways
    // Set default values
    int matrixSize = 4;  // Default size based on sample input
    int dataType = 0;    // 0 for int, 1 for double
    std::string matrixData = 
        "01 02 03 04 "
        "05 06 07 08 "
        "09 10 11 12 "
        "13 14 15 16 "
        "13 14 15 16 "
        "09 10 11 12 "
        "05 06 07 08 "
        "01 02 03 04";

    std::cout << "Matrix Operations Program\n" << std::endl;
    
    // Ask if the user wants to use the default data or load from a file
    char loadChoice;
    std::cout << "Do you want to load matrix data from a file? (y/n): ";
    std::cin >> loadChoice;
    
    if (loadChoice == 'y' || loadChoice == 'Y') {
        std::string filename;
        std::cout << "Enter the filename: ";
        std::cin >> filename;
        
        std::ifstream inFile(filename);
        if (!inFile.is_open()) {
            std::cerr << "Error: Could not open file " << filename << std::endl;
            return 1;
        }
        
        // Read the first line to get matrix size and type
        inFile >> matrixSize >> dataType;
        
        // Read the rest of the file into a string
        std::string line;
        matrixData = "";
        while (std::getline(inFile, line)) {
            matrixData += line + " ";
        }
        
        inFile.close();
    } else {
        std::cout << "Using default matrix data (4x4 integer matrices)" << std::endl;
    }
    
    // Process matrix data based on data type
    if (dataType == 0) { // Integer matrices
        Matrix<int> matrix1, matrix2;
        parseMatrixDataFromString<int>(matrixData, matrixSize, matrix1, matrix2);
        
        int choice = 0;
        while (choice != 8) {
            std::cout << "\nMatrix Operations Menu:" << std::endl;
            std::cout << "1. Display matrices" << std::endl;
            std::cout << "2. Add matrices" << std::endl;
            std::cout << "3. Multiply matrices" << std::endl;
            std::cout << "4. Calculate diagonal sums" << std::endl;
            std::cout << "5. Swap rows" << std::endl;
            std::cout << "6. Swap columns" << std::endl;
            std::cout << "7. Update element" << std::endl;
            std::cout << "8. Exit" << std::endl;
            std::cout << "Enter your choice: ";
            std::cin >> choice;
            
            switch (choice) {
                case 1: {
                    std::cout << "\nMatrix 1:" << std::endl;
                    std::cout << matrix1;
                    std::cout << "\nMatrix 2:" << std::endl;
                    std::cout << matrix2;
                    break;
                }
                case 2: {
                    try {
                        Matrix<int> result = matrix1 + matrix2;
                        std::cout << "\nMatrix 1 + Matrix 2:" << std::endl;
                        std::cout << result;
                    } catch (const std::exception& e) {
                        std::cerr << "Error: " << e.what() << std::endl;
                    }
                    break;
                }
                case 3: {
                    try {
                        Matrix<int> result = matrix1 * matrix2;
                        std::cout << "\nMatrix 1 * Matrix 2:" << std::endl;
                        std::cout << result;
                    } catch (const std::exception& e) {
                        std::cerr << "Error: " << e.what() << std::endl;
                    }
                    break;
                }
                case 4: {
                    auto diagonals1 = matrix1.sumDiagonals();
                    auto diagonals2 = matrix2.sumDiagonals();
                    
                    std::cout << "\nMatrix 1 Diagonals:" << std::endl;
                    std::cout << "Main diagonal sum: " << diagonals1.first << std::endl;
                    std::cout << "Secondary diagonal sum: " << diagonals1.second << std::endl;
                    
                    std::cout << "\nMatrix 2 Diagonals:" << std::endl;
                    std::cout << "Main diagonal sum: " << diagonals2.first << std::endl;
                    std::cout << "Secondary diagonal sum: " << diagonals2.second << std::endl;
                    break;
                }
                case 5: {
                    int matrixChoice, row1, row2;
                    std::cout << "Which matrix (1 or 2)? ";
                    std::cin >> matrixChoice;
                    std::cout << "Enter the two row indices to swap (0-based): ";
                    std::cin >> row1 >> row2;
                    
                    if (matrixChoice == 1) {
                        if (matrix1.swapRows(row1, row2)) {
                            std::cout << "Rows swapped successfully. New Matrix 1:" << std::endl;
                            std::cout << matrix1;
                        } else {
                            std::cout << "Invalid row indices." << std::endl;
                        }
                    } else if (matrixChoice == 2) {
                        if (matrix2.swapRows(row1, row2)) {
                            std::cout << "Rows swapped successfully. New Matrix 2:" << std::endl;
                            std::cout << matrix2;
                        } else {
                            std::cout << "Invalid row indices." << std::endl;
                        }
                    } else {
                        std::cout << "Invalid matrix choice." << std::endl;
                    }
                    break;
                }
                case 6: {
                    int matrixChoice, col1, col2;
                    std::cout << "Which matrix (1 or 2)? ";
                    std::cin >> matrixChoice;
                    std::cout << "Enter the two column indices to swap (0-based): ";
                    std::cin >> col1 >> col2;
                    
                    if (matrixChoice == 1) {
                        if (matrix1.swapColumns(col1, col2)) {
                            std::cout << "Columns swapped successfully. New Matrix 1:" << std::endl;
                            std::cout << matrix1;
                        } else {
                            std::cout << "Invalid column indices." << std::endl;
                        }
                    } else if (matrixChoice == 2) {
                        if (matrix2.swapColumns(col1, col2)) {
                            std::cout << "Columns swapped successfully. New Matrix 2:" << std::endl;
                            std::cout << matrix2;
                        } else {
                            std::cout << "Invalid column indices." << std::endl;
                        }
                    } else {
                        std::cout << "Invalid matrix choice." << std::endl;
                    }
                    break;
                }
                case 7: {
                    int matrixChoice, row, col, value;
                    std::cout << "Which matrix (1 or 2)? ";
                    std::cin >> matrixChoice;
                    std::cout << "Enter row, column (0-based), and new value: ";
                    std::cin >> row >> col >> value;
                    
                    if (matrixChoice == 1) {
                        if (matrix1.updateElement(row, col, value)) {
                            std::cout << "Element updated successfully. New Matrix 1:" << std::endl;
                            std::cout << matrix1;
                        } else {
                            std::cout << "Invalid indices." << std::endl;
                        }
                    } else if (matrixChoice == 2) {
                        if (matrix2.updateElement(row, col, value)) {
                            std::cout << "Element updated successfully. New Matrix 2:" << std::endl;
                            std::cout << matrix2;
                        } else {
                            std::cout << "Invalid indices." << std::endl;
                        }
                    } else {
                        std::cout << "Invalid matrix choice." << std::endl;
                    }
                    break;
                }
                case 8:
                    std::cout << "Exiting program." << std::endl;
                    break;
                default:
                    std::cout << "Invalid choice. Please try again." << std::endl;
            }
        }
    } else if (dataType == 1) { // Double matrices
        Matrix<double> matrix1, matrix2;
        parseMatrixDataFromString<double>(matrixData, matrixSize, matrix1, matrix2);
        
        int choice = 0;
        while (choice != 8) {
            std::cout << "\nMatrix Operations Menu:" << std::endl;
            std::cout << "1. Display matrices" << std::endl;
            std::cout << "2. Add matrices" << std::endl;
            std::cout << "3. Multiply matrices" << std::endl;
            std::cout << "4. Calculate diagonal sums" << std::endl;
            std::cout << "5. Swap rows" << std::endl;
            std::cout << "6. Swap columns" << std::endl;
            std::cout << "7. Update element" << std::endl;
            std::cout << "8. Exit" << std::endl;
            std::cout << "Enter your choice: ";
            std::cin >> choice;
            
            switch (choice) {
                case 1: {
                    std::cout << "\nMatrix 1:" << std::endl;
                    std::cout << matrix1;
                    std::cout << "\nMatrix 2:" << std::endl;
                    std::cout << matrix2;
                    break;
                }
                case 2: {
                    try {
                        Matrix<double> result = matrix1 + matrix2;
                        std::cout << "\nMatrix 1 + Matrix 2:" << std::endl;
                        std::cout << result;
                    } catch (const std::exception& e) {
                        std::cerr << "Error: " << e.what() << std::endl;
                    }
                    break;
                }
                case 3: {
                    try {
                        Matrix<double> result = matrix1 * matrix2;
                        std::cout << "\nMatrix 1 * Matrix 2:" << std::endl;
                        std::cout << result;
                    } catch (const std::exception& e) {
                        std::cerr << "Error: " << e.what() << std::endl;
                    }
                    break;
                }
                case 4: {
                    auto diagonals1 = matrix1.sumDiagonals();
                    auto diagonals2 = matrix2.sumDiagonals();
                    
                    std::cout << "\nMatrix 1 Diagonals:" << std::endl;
                    std::cout << "Main diagonal sum: " << diagonals1.first << std::endl;
                    std::cout << "Secondary diagonal sum: " << diagonals1.second << std::endl;
                    
                    std::cout << "\nMatrix 2 Diagonals:" << std::endl;
                    std::cout << "Main diagonal sum: " << diagonals2.first << std::endl;
                    std::cout << "Secondary diagonal sum: " << diagonals2.second << std::endl;
                    break;
                }
                case 5: {
                    int matrixChoice, row1, row2;
                    std::cout << "Which matrix (1 or 2)? ";
                    std::cin >> matrixChoice;
                    std::cout << "Enter the two row indices to swap (0-based): ";
                    std::cin >> row1 >> row2;
                    
                    if (matrixChoice == 1) {
                        if (matrix1.swapRows(row1, row2)) {
                            std::cout << "Rows swapped successfully. New Matrix 1:" << std::endl;
                            std::cout << matrix1;
                        } else {
                            std::cout << "Invalid row indices." << std::endl;
                        }
                    } else if (matrixChoice == 2) {
                        if (matrix2.swapRows(row1, row2)) {
                            std::cout << "Rows swapped successfully. New Matrix 2:" << std::endl;
                            std::cout << matrix2;
                        } else {
                            std::cout << "Invalid row indices." << std::endl;
                        }
                    } else {
                        std::cout << "Invalid matrix choice." << std::endl;
                    }
                    break;
                }
                case 6: {
                    int matrixChoice, col1, col2;
                    std::cout << "Which matrix (1 or 2)? ";
                    std::cin >> matrixChoice;
                    std::cout << "Enter the two column indices to swap (0-based): ";
                    std::cin >> col1 >> col2;
                    
                    if (matrixChoice == 1) {
                        if (matrix1.swapColumns(col1, col2)) {
                            std::cout << "Columns swapped successfully. New Matrix 1:" << std::endl;
                            std::cout << matrix1;
                        } else {
                            std::cout << "Invalid column indices." << std::endl;
                        }
                    } else if (matrixChoice == 2) {
                        if (matrix2.swapColumns(col1, col2)) {
                            std::cout << "Columns swapped successfully. New Matrix 2:" << std::endl;
                            std::cout << matrix2;
                        } else {
                            std::cout << "Invalid column indices." << std::endl;
                        }
                    } else {
                        std::cout << "Invalid matrix choice." << std::endl;
                    }
                    break;
                }
                case 7: {
                    int matrixChoice, row, col;
                    double value;
                    std::cout << "Which matrix (1 or 2)? ";
                    std::cin >> matrixChoice;
                    std::cout << "Enter row, column (0-based), and new value: ";
                    std::cin >> row >> col >> value;
                    
                    if (matrixChoice == 1) {
                        if (matrix1.updateElement(row, col, value)) {
                            std::cout << "Element updated successfully. New Matrix 1:" << std::endl;
                            std::cout << matrix1;
                        } else {
                            std::cout << "Invalid indices." << std::endl;
                        }
                    } else if (matrixChoice == 2) {
                        if (matrix2.updateElement(row, col, value)) {
                            std::cout << "Element updated successfully. New Matrix 2:" << std::endl;
                            std::cout << matrix2;
                        } else {
                            std::cout << "Invalid indices." << std::endl;
                        }
                    } else {
                        std::cout << "Invalid matrix choice." << std::endl;
                    }
                    break;
                }
                case 8:
                    std::cout << "Exiting program." << std::endl;
                    break;
                default:
                    std::cout << "Invalid choice. Please try again." << std::endl;
            }
        }
    } else {
        std::cerr << "Error: Invalid matrix type. Type must be 0 (int) or 1 (double)." << std::endl;
        return 1;
    }
    
    return 0;
}