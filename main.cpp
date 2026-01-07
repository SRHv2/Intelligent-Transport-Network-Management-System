#include <iostream>
#include <string>
#include <iomanip>
#include "Graph.h"
#include "Queue.h"
#include "Stack.h"
#include "Hash.h"
#include "BST.h"
#include "Heap.h"
#include "Sorting.h"

#ifdef _WIN32
#include <windows.h>
#define SLEEP(ms) Sleep(ms)
#else
#include <unistd.h>
#define SLEEP(ms) usleep((ms) * 1000)
#endif

using namespace std;

void printTestHeader(string title) {
    cout << "\n================================================================" << endl;
    cout << " TESTING MODULE: " << title << endl;
    cout << "================================================================" << endl;
    SLEEP(800); // Cross-platform pause
}

void printSubTest(string testName) {
    cout << "\n[" << testName << "]" << endl;
    SLEEP(300);
}

int main() {
    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    #endif
    
    cout << "\n";
    cout << "╔════════════════════════════════════════════════════════════════╗\n";
    cout << "║           AUTOMATED  SYSTEM TEST                               ║\n";
    cout << "║          Testing All Modules of ITNMS                          ║\n";
    cout << "╚════════════════════════════════════════════════════════════════╝\n";
    SLEEP(1000);
    
    // Initialize all Data Structures
    Graph g(10);  // Using 10 stations for cleaner output
    Queue q;
    Stack st;
    HashTable ht;
    BST tree;
    MinHeap heap;

    // ========================================================================
    // PHASE 1: NETWORK SETUP (Stations before Routes - Logical Order)
    // ========================================================================
    printTestHeader("PHASE 1: NETWORK SETUP");
    
    printSubTest("Test 3: Add Stations");
    cout << "Adding stations 0, 1, 2, 3, 4 to network...\n";
    g.addStation(0);
    st.push("ADD_STATION", 0, 0, 0);
    g.addStation(1);
    st.push("ADD_STATION", 1, 0, 0);
    g.addStation(2);
    st.push("ADD_STATION", 2, 0, 0);
    g.addStation(3);
    st.push("ADD_STATION", 3, 0, 0);
    g.addStation(4);
    st.push("ADD_STATION", 4, 0, 0);
    cout << " All stations successfully added\n";

    printSubTest("Test 1: Add Routes (Edges)");
    cout << "Building connected network topology...\n";
    g.addEdge(0, 1, 10);
    st.push("ADD_EDGE", 0, 1, 10);
    g.addEdge(1, 2, 5);
    st.push("ADD_EDGE", 1, 2, 5);
    g.addEdge(2, 3, 15);
    st.push("ADD_EDGE", 2, 3, 15);
    g.addEdge(3, 0, 20);
    st.push("ADD_EDGE", 3, 0, 20);
    g.addEdge(1, 3, 2); // Shortcut route
    st.push("ADD_EDGE", 1, 3, 2);
    cout << " 5 bidirectional routes established\n";

    //Adding deeper nodes to show BFS and DFS actually work (uncomment to see)
    // g.addEdge(0, 1, 10);
    // g.addEdge(0, 2, 10);
    // // Create depth: 1 leads to 3, and 3 leads to 4
    // g.addEdge(1, 3, 10);
    // g.addEdge(3, 4, 10);
    // // Connecting 2 to 4 to create a cycle/alternative path
    // g.addEdge(2, 4, 10);

    printSubTest("Test 5: Display Network");
    g.display();

    printSubTest("Test 6: System Status");
    g.displaySystemStatus();

    // ========================================================================
    // PHASE 2: GRAPH ALGORITHMS
    // ========================================================================
    printTestHeader("PHASE 2: GRAPH ALGORITHMS");

    printSubTest("Test 7: Breadth-First Search (BFS)");
    cout << "Starting BFS traversal from Station 0:\n";
    g.BFS(0);

    printSubTest("Test 8: Depth-First Search (DFS)");
    cout << "Starting DFS traversal from Station 0:\n";
    g.DFS(0);

    printSubTest("Test 9: Dijkstra's Shortest Path");
    cout << "Computing shortest paths from Station 0:\n";
    g.dijkstra(0);

    printSubTest("Test 10: Minimum Spanning Tree (Prim's)");
    cout << "Finding MST for network optimization:\n";
    g.MST();

    printSubTest("Test 11: Cycle Detection");
    cout << "Checking for cycles in network:\n";
    g.detectCycle();

    printSubTest("Test 12: Busiest Station Analytics");
    cout << "Identifying most connected station:\n";
    g.getBusiestStation();

    // ========================================================================
    // PHASE 3: PASSENGER QUEUE OPERATIONS
    // ========================================================================
    printTestHeader("PHASE 3: PASSENGER TICKETING SYSTEM (QUEUE)");

    printSubTest("Test 13: Enqueue Passengers");
    cout << "Passengers arriving at ticket counter...\n";
    q.enqueue("Fatima Zahra");
    q.enqueue("Rayyan Hasan");
    q.enqueue("Aisha Noor");
    q.enqueue("Diana Prince");

    printSubTest("Test 15: Display Queue");
    q.display();

    printSubTest("Test 14: Process Queue (Dequeue)");
    cout << "Processing passengers in FIFO order...\n";
    q.dequeue();
    q.dequeue();
    cout << "\nRemaining queue:\n";
    q.display();

    // ========================================================================
    // PHASE 4: VEHICLE MANAGEMENT (HASH TABLE)
    // ========================================================================
    printTestHeader("PHASE 4: VEHICLE DATABASE (HASH TABLE)");

    printSubTest("Test 16: Insert Vehicles");
    cout << "Registering vehicles in system...\n";
    ht.insert(101, "Metro Train Express");
    ht.insert(202, "Electric Bus Route 5");
    ht.insert(303, "Tram Line North");
    ht.insert(404, "Shuttle Service A");
    ht.insert(111, "Metro Train Local"); // Collision test (same hash as 101)

    printSubTest("Test 19: Display All Vehicles");
    ht.display();

    printSubTest("Test 17: Search Vehicle");
    cout << "Looking up vehicle records...\n";
    ht.search(202);
    ht.search(999); // Not found test

    printSubTest("Test 18: Remove Vehicle");
    cout << "Decommissioning vehicle 101...\n";
    ht.remove(101);
    cout << "\nUpdated database:\n";
    ht.display();

    // ========================================================================
    // PHASE 5: STATION METADATA (BST)
    // ========================================================================
    printTestHeader("PHASE 5: STATION METADATA (BINARY SEARCH TREE)");

    printSubTest("Test 20: Insert Station Metadata");
    cout << "Storing station information...\n";
    tree.insert(0, "Central Station");
    tree.insert(2, "North Terminal");
    tree.insert(1, "East Plaza");
    tree.insert(3, "West Junction");
    tree.insert(4, "South Hub");

    printSubTest("Test 23: Display BST (In-Order)");
    cout << "Sorted station registry:\n";
    tree.display();

    printSubTest("Test 21: Search Station");
    cout << "Querying station records...\n";
    tree.search(2);
    tree.search(99); // Not found test

    printSubTest("Test 24: BST Statistics");
    tree.displayStats();

    printSubTest("Test 22: Delete Station Metadata");
    cout << "Removing station 1 from registry...\n";
    tree.remove(1);
    cout << "\nUpdated registry:\n";
    tree.display();

    // ========================================================================
    // PHASE 6: PRIORITY QUEUE (MIN HEAP)
    // ========================================================================
    printTestHeader("PHASE 6: PRIORITY QUEUE (MIN HEAP)");

    printSubTest("Test 25: Insert Priorities");
    cout << "Adding vehicle priorities (lower value = higher priority):\n";
    heap.insert(50); // Priority 50
    heap.insert(10); // Highest priority
    heap.insert(30);
    heap.insert(70);
    heap.insert(5);  // New highest priority

    printSubTest("Test 27: Display Heap");
    heap.display();

    printSubTest("Test 26: Extract Min Priority");
    cout << "Dispatching highest priority vehicle...\n";
    int p1 = heap.extractMin();
    cout << " Dispatched: Priority " << p1 << endl;
    
    cout << "\nDispatching next vehicle...\n";
    int p2 = heap.extractMin();
    cout << " Dispatched: Priority " << p2 << endl;
    
    cout << "\nRemaining heap:\n";
    heap.display();

    // ========================================================================
    // PHASE 7: SORTING ALGORITHMS
    // ========================================================================
    printTestHeader("PHASE 7: SORTING ALGORITHMS MODULE");

    int testArr1[] = {64, 34, 25, 12, 22, 11, 90};
    int n1 = 7;
    
    printSubTest("Test 28a: Bubble Sort");
    cout << "Original: ";
    for(int i=0; i<n1; i++) cout << testArr1[i] << " ";
    cout << endl;
    Sorting::bubble(testArr1, n1);
    Sorting::displayAlgorithmInfo("Bubble Sort");
    cout << "Sorted:   ";
    for(int i=0; i<n1; i++) cout << testArr1[i] << " ";
    cout << endl;

    int testArr2[] = {64, 34, 25, 12, 22, 11, 90};
    printSubTest("Test 28b: Selection Sort");
    Sorting::selection(testArr2, n1);
    cout << "Sorted:   ";
    for(int i=0; i<n1; i++) cout << testArr2[i] << " ";
    cout << endl;

    int testArr3[] = {64, 34, 25, 12, 22, 11, 90};
    printSubTest("Test 28c: Insertion Sort");
    Sorting::insertion(testArr3, n1);
    cout << "Sorted:   ";
    for(int i=0; i<n1; i++) cout << testArr3[i] << " ";
    cout << endl;

    int testArr4[] = {64, 34, 25, 12, 22, 11, 90};
    printSubTest("Test 28d: Merge Sort");
    Sorting::mergeSort(testArr4, 0, n1-1);
    Sorting::displayAlgorithmInfo("Merge Sort");
    cout << "Sorted:   ";
    for(int i=0; i<n1; i++) cout << testArr4[i] << " ";
    cout << endl;

    int testArr5[] = {64, 34, 25, 12, 22, 11, 90};
    printSubTest("Test 28e: Quick Sort");
    Sorting::quickSort(testArr5, 0, n1-1);
    cout << "Sorted:   ";
    for(int i=0; i<n1; i++) cout << testArr5[i] << " ";
    cout << endl;

    int testArr6[] = {64, 34, 25, 12, 22, 11, 90};
    printSubTest("Test 28f: Heap Sort");
    Sorting::heapSort(testArr6, n1);
    Sorting::displayAlgorithmInfo("Heap Sort");
    cout << "Sorted:   ";
    for(int i=0; i<n1; i++) cout << testArr6[i] << " ";
    cout << endl;

    // ========================================================================
    // PHASE 8: SEARCHING ALGORITHMS
    // ========================================================================
    printTestHeader("PHASE 8: SEARCHING ALGORITHMS MODULE");

    int searchArr[] = {11, 12, 22, 25, 34, 64, 90}; // Sorted for binary search
    int target1 = 25;
    int target2 = 99;

    printSubTest("Test 29a: Linear Search");
    Sorting::displayAlgorithmInfo("Linear Search");
    cout << "Searching for " << target1 << " in array...\n";
    int idx1 = Sorting::linearSearch(searchArr, 7, target1);
    if(idx1 != -1) cout << " Found at index: " << idx1 << endl;
    
    cout << "Searching for " << target2 << " (not present)...\n";
    int idx2 = Sorting::linearSearch(searchArr, 7, target2);
    if(idx2 == -1) cout << " Not found (expected)\n";

    printSubTest("Test 29b: Binary Search");
    Sorting::displayAlgorithmInfo("Binary Search");
    cout << "Searching for " << target1 << " in sorted array...\n";
    int idx3 = Sorting::binarySearch(searchArr, 0, 6, target1);
    if(idx3 != -1) cout << " Found at index: " << idx3 << endl;
    
    cout << "Searching for " << target2 << " (not present)...\n";
    int idx4 = Sorting::binarySearch(searchArr, 0, 6, target2);
    if(idx4 == -1) cout << " Not found (expected)\n";

    // ========================================================================
    // PHASE 9: UNDO SYSTEM & HISTORY
    // ========================================================================
    printTestHeader("PHASE 9: UNDO SYSTEM & ACTION HISTORY (STACK)");

    printSubTest("Test 31: View Action History");
    st.display();

    printSubTest("Test 30: Undo Last 3 Actions");
    for(int i = 0; i < 3; i++) {
        cout << "\nUndo operation " << (i+1) << ":\n";
        Action last = st.pop();
        if (last.type == "ADD_EDGE") {
            g.removeEdge(last.u, last.v);
            cout << " Undid: Removed route " << last.u << " ↔ " << last.v << endl;
        } else if (last.type == "REM_EDGE") {
            g.addEdge(last.u, last.v, last.w);
            cout << " Undid: Restored route " << last.u << " ↔ " << last.v << endl;
        } else if (last.type == "ADD_STATION") {
            cout << " Undid: Deactivated station " << last.u << endl;
        } else {
            cout << "⚠ Nothing more to undo.\n";
            break;
        }
    }

    cout << "\nNetwork after undo operations:\n";
    g.display();

    // ========================================================================
    // PHASE 10: EDGE CASE TESTING
    // ========================================================================
    printTestHeader("PHASE 10: EDGE CASE & ERROR HANDLING TESTS");

    printSubTest("Test: Empty Operations");
    Queue emptyQ;
    emptyQ.dequeue(); // Should handle gracefully
    emptyQ.display();

    MinHeap emptyHeap;
    int emptyResult = emptyHeap.extractMin();
    cout << "Empty heap extract result: " << emptyResult << " (expected: -1)\n";

    printSubTest("Test: Invalid Inputs");
    g.addEdge(-1, 5, 10); // Invalid station
    g.addEdge(0, 20, 10); // Station out of range
    g.BFS(99);            // Invalid start station

    printSubTest("Test: Duplicate Operations");
    ht.insert(202, "Duplicate Vehicle"); // Should update
    tree.insert(2, "Updated Station Name"); // Should update

    printSubTest("Test 4: Delete Station");
    cout << "Testing station deactivation...\n";
    g.deleteStation(2);
    cout << "\nNetwork after deletion:\n";
    g.display();

    return 0;
}