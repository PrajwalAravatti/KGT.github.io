#include <iostream>
#include <vector>

using namespace std;

void Merge(const vector<int> &B, const vector<int> &C, vector<int> &A) {
    int p = B.size();
    int q = C.size();
    int i = 0, j = 0, k = 0;

    // Compare elements from B and C and merge them into array A
    while (i < p && j < q) {
        if (B[i] <= C[j]) {
            A[k] = B[i];
            i++;
        } 
        else {
            A[k] = C[j];
            j++;
        }
        k++;
    }
    // Copy remaining elements of B, if any
    while (i < p) {
        A[k] = B[i];
        i++;
        k++;
    }
    // Copy remaining elements of C, if any
    while (j < q) {
        A[k] = C[j];
        j++;
        k++;
    }
}
void MergeSort(vector<int> &A) {
    int n = A.size();
    
    if (n <= 1) {
        return;
    }

    int mid = n / 2;

    // Divide the array into two halves
    vector<int> B(A.begin(), A.begin() + mid);
    vector<int> C(A.begin() + mid, A.end());

    // Recursively sort both halves
    MergeSort(B);
    MergeSort(C);

    // Merge the sorted halves into the original array
    Merge(B, C, A);
}

int main() {
    vector<int> A = {38, 27, 43, 3, 9, 82, 10};

    cout << "Original Array: ";
    for (int num : A) {
        cout << num << "   ";
    }
    cout << endl;

    MergeSort(A);

    cout << "Sorted Array: ";
    for (int num : A) {
        cout << num << "   ";
    }
    cout << endl;

    return 0;
}

