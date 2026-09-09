#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;
typedef vector<vector<int>> Matrix;

Matrix create(int n) { return Matrix(n, vector<int>(n, 0)); }

Matrix combine(const Matrix& A, const Matrix& B, bool isAdd) {
    int n = A.size();
    Matrix C = create(n);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            C[i][j] = isAdd ? A[i][j] + B[i][j] : A[i][j] - B[i][j];
    return C;
}

Matrix standardMultiply(const Matrix& A, const Matrix& B) {
    int n = A.size();
    Matrix C = create(n);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            for (int k = 0; k < n; ++k)
                C[i][j] += A[i][k] * B[k][j];
    return C;
}

Matrix strassenMultiply(const Matrix& A, const Matrix& B) {
    int n = A.size();
    if (n == 1) return {{A[0][0] * B[0][0]}};

    int k = n / 2;
    Matrix A11 = create(k), A12 = create(k), A21 = create(k), A22 = create(k);
    Matrix B11 = create(k), B12 = create(k), B21 = create(k), B22 = create(k);

    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < k; ++j) {
            A11[i][j] = A[i][j];         A12[i][j] = A[i][j + k];
            A21[i][j] = A[i + k][j];     A22[i][j] = A[i + k][j + k];
            B11[i][j] = B[i][j];         B12[i][j] = B[i][j + k];
            B21[i][j] = B[i + k][j];     B22[i][j] = B[i + k][j + k];
        }
    }

    Matrix M1 = strassenMultiply(combine(A11, A22, true), combine(B11, B22, true));
    Matrix M2 = strassenMultiply(combine(A21, A22, true), B11);
    Matrix M3 = strassenMultiply(A11, combine(B12, B22, false));
    Matrix M4 = strassenMultiply(A22, combine(B21, B11, false));
    Matrix M5 = strassenMultiply(combine(A11, A12, true), B22);
    Matrix M6 = strassenMultiply(combine(A21, A11, false), combine(B11, B12, true));
    Matrix M7 = strassenMultiply(combine(A12, A22, false), combine(B21, B22, true));

    Matrix C11 = combine(combine(combine(M1, M4, true), M5, false), M7, true);
    Matrix C12 = combine(M3, M5, true);
    Matrix C21 = combine(M2, M4, true);
    Matrix C22 = combine(combine(combine(M1, M3, true), M2, false), M6, true);

    Matrix C = create(n);
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < k; ++j) {
            C[i][j] = C11[i][j];         C[i][j + k] = C12[i][j];
            C[i + k][j] = C21[i][j];     C[i + k][j + k] = C22[i][j];
        }
    }
    return C;
}

void fillRandom(Matrix& M) {
    for (auto& row : M) for (int& val : row) val = rand() % 10;
}

void printAndVerify(const string& label, const Matrix& A, const Matrix& B) {
    Matrix stdRes = standardMultiply(A, B);
    Matrix strRes = strassenMultiply(A, B);
    cout << "=== " << label << " ===" << endl;
    for (const auto& row : strRes) {
        for (int v : row) cout << setw(4) << v;
        cout << endl;
    }
    cout << "Match Naive: " << (stdRes == strRes ? "PASS" : "FAIL") << endl << endl;
}

int main() {
    srand(time(0));
    printAndVerify("2x2 Test", {{1, 2}, {3, 4}}, {{5, 6}, {7, 8}});

    Matrix A4 = create(4), B4 = create(4);
    fillRandom(A4); fillRandom(B4);
    printAndVerify("4x4 Random Test", A4, B4);

    return 0;
}