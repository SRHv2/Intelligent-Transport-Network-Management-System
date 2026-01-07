#ifndef SORTING_H
#define SORTING_H
#include <iostream>
using namespace std;

class Sorting {
public:
    // Bubble Sort - O(n²)
    static void bubble(int a[], int n) {
        for (int i = 0; i < n - 1; i++) {
            bool swapped = false;
            for (int j = 0; j < n - i - 1; j++) {
                if (a[j] > a[j + 1]) {
                    swap(a[j], a[j + 1]);
                    swapped = true;
                }
            }
            if (!swapped) break; // Optimization: already sorted
        }
    }

    // Selection Sort - O(n²)
    static void selection(int a[], int n) {
        for (int i = 0; i < n - 1; i++) {
            int minIdx = i;
            for (int j = i + 1; j < n; j++) {
                if (a[j] < a[minIdx]) {
                    minIdx = j;
                }
            }
            if (minIdx != i) {
                swap(a[i], a[minIdx]);
            }
        }
    }

    // Insertion Sort - O(n²)
    static void insertion(int a[], int n) {
        for (int i = 1; i < n; i++) {
            int key = a[i];
            int j = i - 1;
            while (j >= 0 && a[j] > key) {
                a[j + 1] = a[j];
                j--;
            }
            a[j + 1] = key;
        }
    }

    // Merge helper
    static void merge(int a[], int l, int m, int r) {
        int n1 = m - l + 1;
        int n2 = r - m;
        int* L = new int[n1];
        int* R = new int[n2];

        for (int i = 0; i < n1; i++) L[i] = a[l + i];
        for (int j = 0; j < n2; j++) R[j] = a[m + 1 + j];

        int i = 0, j = 0, k = l;
        while (i < n1 && j < n2) {
            a[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
        }
        while (i < n1) a[k++] = L[i++];
        while (j < n2) a[k++] = R[j++];

        delete[] L;
        delete[] R;
    }

    // Merge Sort - O(n log n)
    static void mergeSort(int a[], int l, int r) {
        if (l < r) {
            int m = l + (r - l) / 2; // Prevent overflow
            mergeSort(a, l, m);
            mergeSort(a, m + 1, r);
            merge(a, l, m, r);
        }
    }

    // Quick Sort partition
    static int partition(int a[], int l, int r) {
        int pivot = a[r];
        int i = l - 1;
        for (int j = l; j < r; j++) {
            if (a[j] < pivot) {
                swap(a[++i], a[j]);
            }
        }
        swap(a[i + 1], a[r]);
        return i + 1;
    }

    // Quick Sort - O(n log n) average
    static void quickSort(int a[], int l, int r) {
        if (l < r) {
            int p = partition(a, l, r);
            quickSort(a, l, p - 1);
            quickSort(a, p + 1, r);
        }
    }

    // Heapify helper
    static void heapify(int a[], int n, int i) {
        int largest = i;
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        
        if (l < n && a[l] > a[largest]) largest = l;
        if (r < n && a[r] > a[largest]) largest = r;
        
        if (largest != i) {
            swap(a[i], a[largest]);
            heapify(a, n, largest);
        }
    }

    // Heap Sort - O(n log n)
    static void heapSort(int a[], int n) {
        // Build max heap
        for (int i = n / 2 - 1; i >= 0; i--) {
            heapify(a, n, i);
        }
        
        // Extract elements from heap
        for (int i = n - 1; i > 0; i--) {
            swap(a[0], a[i]);
            heapify(a, i, 0);
        }
    }

    // Linear Search - O(n)
    static int linearSearch(int a[], int n, int k) {
        for (int i = 0; i < n; i++) {
            if (a[i] == k) {
                return i;
            }
        }
        return -1;
    }

    // Binary Search - O(log n) - requires sorted array
    static int binarySearch(int a[], int l, int r, int k) {
        if (l <= r) {
            int m = l + (r - l) / 2;
            if (a[m] == k) return m;
            if (a[m] > k) return binarySearch(a, l, m - 1, k);
            return binarySearch(a, m + 1, r, k);
        }
        return -1;
    }

    // Display algorithm info
    static void displayAlgorithmInfo(string algo) {
        cout << "\n=== " << algo << " Algorithm ===\n";
        
        if (algo == "Bubble Sort") {
            cout << "Time Complexity: O(n²) - Best: O(n) when sorted\n";
            cout << "Space Complexity: O(1)\n";
            cout << "Stable: Yes\n";
        } else if (algo == "Selection Sort") {
            cout << "Time Complexity: O(n²)\n";
            cout << "Space Complexity: O(1)\n";
            cout << "Stable: No\n";
        } else if (algo == "Insertion Sort") {
            cout << "Time Complexity: O(n²) - Best: O(n) when sorted\n";
            cout << "Space Complexity: O(1)\n";
            cout << "Stable: Yes\n";
        } else if (algo == "Merge Sort") {
            cout << "Time Complexity: O(n log n)\n";
            cout << "Space Complexity: O(n)\n";
            cout << "Stable: Yes\n";
        } else if (algo == "Quick Sort") {
            cout << "Time Complexity: O(n log n) average, O(n²) worst\n";
            cout << "Space Complexity: O(log n)\n";
            cout << "Stable: No\n";
        } else if (algo == "Heap Sort") {
            cout << "Time Complexity: O(n log n)\n";
            cout << "Space Complexity: O(1)\n";
            cout << "Stable: No\n";
        } else if (algo == "Linear Search") {
            cout << "Time Complexity: O(n)\n";
            cout << "Space Complexity: O(1)\n";
        } else if (algo == "Binary Search") {
            cout << "Time Complexity: O(log n)\n";
            cout << "Space Complexity: O(1) iterative, O(log n) recursive\n";
            cout << "Note: Requires sorted array!\n";
        }
        cout << "==============================\n";
    }
};

#endif