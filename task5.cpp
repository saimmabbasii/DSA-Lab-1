#include <iostream>
#include <vector>
using namespace std;

// Function to generate Pascal's Triangle up to n rows (0-indexed or 1-indexed)
// Here, n represents the total number of rows generated.
vector<vector<int>> generatePascalsTriangle(int numRows) {
    vector<vector<int>> triangle;

    if (numRows <= 0) {
        return triangle; // Return empty vector for n = 0
    }

    for (int i = 0; i < numRows; ++i) {
        vector<int> row(i + 1, 1); // Start each row filled with 1s

        // Fill in the middle values (sum of two elements from previous row)
        for (int j = 1; j < i; ++j) {
            row[j] = triangle[i - 1][j - 1] + triangle[i - 1][j];
        }

        triangle.push_back(row);
    }

    return triangle;
}

// Helper function to print Pascal's Triangle
void printTriangle(int n, const vector<vector<int>>& triangle) {
    cout << "--- Pascal's Triangle for n = " << n << " ---" << endl;
    if (triangle.empty()) {
        cout << "[Empty Triangle]" << endl;
        return;
    }

    for (int i = 0; i < static_cast<int>(triangle.size()); ++i) {
        // Simple spacing for structure formatting
        for (int s = 0; s < (static_cast<int>(triangle.size()) - i - 1); ++s) {
            cout << " ";
        }
        for (int val : triangle[i]) {
            cout << val << " ";
        }
        cout << endl;
    }
}

int main() {
    // Test Case 1: n = 0
    vector<vector<int>> res0 = generatePascalsTriangle(0);
    printTriangle(0, res0);
    cout << endl;

    // Test Case 2: n = 1
    vector<vector<int>> res1 = generatePascalsTriangle(1);
    printTriangle(1, res1);
    cout << endl;

    // Test Case 3: n = 5
    vector<vector<int>> res5 = generatePascalsTriangle(5);
    printTriangle(5, res5);
    cout << endl;

    // Verification check for Row 5 (index 4 of 5 rows): {1, 4, 6, 4, 1}
    cout << "=== Verification Check ===" << endl;
    if (res5.size() >= 5) {
        cout << "Row 5 output: { ";
        for (int val : res5[4]) {
            cout << val << " ";
        }
        cout << "}" << endl;
    }

    return 0;
}