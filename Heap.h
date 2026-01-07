#ifndef HEAP_H
#define HEAP_H
#include <iostream>
using namespace std;

class MinHeap {
    static const int MAX_SIZE = 100;
    int h[MAX_SIZE];
    int sz;

    void heapify(int i) {
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        int smallest = i;
        
        if (l < sz && h[l] < h[smallest]) smallest = l;
        if (r < sz && h[r] < h[smallest]) smallest = r;
        
        if (smallest != i) {
            swap(h[i], h[smallest]);
            heapify(smallest);
        }
    }

public:
    MinHeap() { sz = 0; }

    void insert(int v) {
        if (sz >= MAX_SIZE) {
            cout << "⚠ Heap is full! Cannot insert " << v << "\n";
            return;
        }
        
        int i = sz++;
        h[i] = v;
        
        // Bubble up
        while (i > 0 && h[(i - 1) / 2] > h[i]) {
            swap(h[i], h[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
        
        cout << "Priority " << v << " inserted successfully.\n";
    }

    int extractMin() {
        if (sz <= 0) {
            cout << "⚠ Heap is empty!\n";
            return -1;
        }
        
        int root = h[0];
        h[0] = h[--sz];
        heapify(0);
        
        return root;
    }

    int peek() {
        if (sz <= 0) {
            cout << "⚠ Heap is empty!\n";
            return -1;
        }
        return h[0];
    }

    bool isEmpty() {
        return sz == 0;
    }

    int size() {
        return sz;
    }

    void display() {
        if (sz == 0) {
            cout << "Heap is empty.\n";
            return;
        }
        
        cout << "Heap Contents (Min at top): ";
        for (int i = 0; i < sz; i++) {
            cout << h[i] << " ";
        }
        cout << endl;
    }

    // Clear all elements
    void clear() {
        sz = 0;
        cout << "Heap cleared.\n";
    }
};

#endif