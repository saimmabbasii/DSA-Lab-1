#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

// Function that performs histogram analysis to find the mode(s) of an array
vector<int> histogramMode(const vector<int>& arr) {
    if (arr.empty()) {
        return {}; // Return empty vector for empty array
    }

    // Step 1: Build frequency histogram
    unordered_map<int, int> histogram;
    int maxFrequency = 0;

    for (int num : arr) {
        histogram[num]++;
        maxFrequency = max(maxFrequency, histogram[num]);
    }

    // Step 2: Extract elements matching the highest histogram frequency
    vector<int> modes;
    for (const auto& entry : histogram) {
        if (entry.second == maxFrequency) {
            modes.push_back(entry.first);
        }
    }

    // Sort modes for clean output
    sort(modes.begin(), modes.end());
    return modes;
}

// Helper function to print histogram test results
void printHistogramResult(const string& testName, const vector<int>& modes) {
    cout << testName << ": ";
    if (modes.empty()) {
        cout << "[Empty Array / No Mode]";
    } else {
        cout << "[ ";
        for (int val : modes) {
            cout << val << " ";
        }
        cout << "]";
    }
    cout << endl;
}

int main() {
    cout << "=== Task 6: Histogram Analysis Test Cases ===" << endl;

    // Test Case 1: Array with unique mode (7 appears 3 times)
    vector<int> arr1 = {4, 7, 2, 7, 9, 7, 1};
    vector<int> res1 = histogramMode(arr1);
    printHistogramResult("Test 1 (Unique Mode)", res1);

    // Test Case 2: Array with multiple modes (5 and 8 both appear 3 times)
    vector<int> arr2 = {5, 8, 5, 3, 8, 5, 8, 12};
    vector<int> res2 = histogramMode(arr2);
    printHistogramResult("Test 2 (Multiple Modes)", res2);

    // Test Case 3: Empty array
    vector<int> arr3 = {};
    vector<int> res3 = histogramMode(arr3);
    printHistogramResult("Test 3 (Empty Array)", res3);

    return 0;
}