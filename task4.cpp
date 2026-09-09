#include <iostream>
#include <string>
using namespace std;

// Function to find the first occurrence of a pattern in a text
int findFirstOccurrence(const string& text, const string& pattern) {
    // Edge case: empty pattern
    if (pattern.empty()) {
        return 0;
    }

    int textLen = static_cast<int>(text.length());
    int patLen = static_cast<int>(pattern.length());

    if (patLen > textLen) {
        return -1;
    }

    // Sliding window pattern matching
    for (int i = 0; i <= textLen - patLen; ++i) {
        int j = 0;
        while (j < patLen && text[i + j] == pattern[j]) {
            j++;
        }
        if (j == patLen) {
            return i; // Pattern matched at index i
        }
    }

    return -1; // Pattern not found
}

// Helper function to print test results
void printTestResult(const string& testName, const string& text, const string& pattern, int expected) {
    int result = findFirstOccurrence(text, pattern);
    cout << testName << endl;
    cout << "  Text: \"" << text << "\" | Pattern: \"" << pattern << "\"" << endl;
    cout << "  Result: " << result << " | Expected: " << expected;
    cout << " [" << (result == expected ? "PASS" : "FAIL") << "]" << endl << endl;
}

int main() {
    cout << " Task 4 Test Cases " << endl << endl;

    // Test Case 1: Pattern at the beginning
    printTestResult("Test 1: Pattern at beginning", "hello world", "hello", 0);

    // Test Case 2: Pattern at the end
    printTestResult("Test 2: Pattern at end", "hello world", "world", 6);

    // Test Case 3: Pattern not present
    printTestResult("Test 3: Pattern not present", "hello world", "cpp", -1);

    // Test Case 4: Empty pattern
    printTestResult("Test 4: Empty pattern", "hello world", "", 0);

    return 0;
}