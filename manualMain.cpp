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
#include <windows.h>
using namespace std;

// Helper function to clear input buffer
void clearInputBuffer() {
    cin.clear();
    cin.ignore(10000, '\n');
}

// Helper function to display menu
void displayMenu() {
    cout << "\n";
    cout << "╔════════════════════════════════════════════════════════════════╗\n";
    cout << "║    INTELLIGENT TRANSPORT NETWORK MANAGEMENT SYSTEM (ITNMS)    ║\n";
    cout << "╚════════════════════════════════════════════════════════════════╝\n";
    cout << "\n┌─── NETWORK MANAGEMENT ───────────────────────────────────────┐\n";
    cout << "│ 1. Add Station            2. Delete Station                  │\n";
    cout << "│ 3. Add Route              4. Delete Route                    │\n";
    cout << "│ 5. Display Network        6. System Status                   │\n";
    cout << "└──────────────────────────────────────────────────────────────┘\n";
    cout << "\n┌─── GRAPH ALGORITHMS ─────────────────────────────────────────┐\n";
    cout << "│ 7. BFS Traversal          8. DFS Traversal                   │\n";
    cout << "│ 9. Shortest Path (Dijkstra)  10. MST (Prim's)               │\n";
    cout << "│ 11. Detect Cycle          12. Busiest Station                │\n";
    cout << "└──────────────────────────────────────────────────────────────┘\n";
    cout << "\n┌─── PASSENGER & VEHICLE MANAGEMENT ───────────────────────────┐\n";
    cout << "│ 13. Add Passenger to Queue   14. Process Queue               │\n";
    cout << "│ 15. Display Queue            16. Insert Vehicle (Hash)       │\n";
    cout << "│ 17. Search Vehicle           18. Remove Vehicle              │\n";
    cout << "│ 19. Display Vehicles                                         │\n";
    cout << "└──────────────────────────────────────────────────────────────┘\n";
    cout << "\n┌─── STATION METADATA (BST) ───────────────────────────────────┐\n";
    cout << "│ 20. Insert Station Metadata  21. Search Station              │\n";
    cout << "│ 22. Delete Station Metadata  23. Display All Stations        │\n";
    cout << "│ 24. BST Statistics                                           │\n";
    cout << "└──────────────────────────────────────────────────────────────┘\n";
    cout << "\n┌─── PRIORITY QUEUE (HEAP) ────────────────────────────────────┐\n";
    cout << "│ 25. Insert Priority          26. Extract Min Priority        │\n";
    cout << "│ 27. Display Heap                                             │\n";
    cout << "└──────────────────────────────────────────────────────────────┘\n";
    cout << "\n┌─── SORTING & SEARCHING MODULE ───────────────────────────────┐\n";
    cout << "│ 28. Sorting Module           29. Searching Module            │\n";
    cout << "└──────────────────────────────────────────────────────────────┘\n";
    cout << "\n┌─── SYSTEM OPERATIONS ────────────────────────────────────────┐\n";
    cout << "│ 30. Undo Last Action         31. View Action History         │\n";
    cout << "│ 0. Exit System                                               │\n";
    cout << "└──────────────────────────────────────────────────────────────┘\n";
    cout << "\nEnter your choice: ";
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    Graph g(10);
    Queue q;
    Stack st;
    HashTable ht;
    BST tree;
    MinHeap heap;

    int ch;
    
    cout << "\n";
    cout << "╔════════════════════════════════════════════════════════════════╗\n";
    cout << "║                         WELCOME TO                             ║\n";
    cout << "║    INTELLIGENT TRANSPORT NETWORK MANAGEMENT SYSTEM (ITNMS)    ║\n";
    cout << "║                                                                ║\n";
    cout << "║              CS221 - Data Structures Project                  ║\n";
    cout << "╚════════════════════════════════════════════════════════════════╝\n";

    do {
        displayMenu();
        cin >> ch;

        // Input validation
        if (cin.fail()) {
            cout << "\n⚠ Invalid input! Please enter a number.\n";
            clearInputBuffer();
            cout << "\nPress Enter to continue...";
            cin.get();
            continue;
        }

        cout << "\n";

        switch (ch) {
            case 1: { // Add Station
                int id;
                cout << "Enter Station ID to activate: ";
                cin >> id;
                
                if (cin.fail()) {
                    cout << "⚠ Invalid input!\n";
                    clearInputBuffer();
                } else {
                    g.addStation(id);
                    st.push("ADD_STATION", id, 0, 0);
                }
                break;
            }

            case 2: { // Delete Station
                int id;
                cout << "Enter Station ID to deactivate: ";
                cin >> id;
                
                if (cin.fail()) {
                    cout << "⚠ Invalid input!\n";
                    clearInputBuffer();
                } else {
                    g.deleteStation(id);
                    st.push("REM_STATION", id, 0, 0);
                }
                break;
            }

            case 3: { // Add Route
                int u, v, w;
                cout << "Enter Start Station ID: ";
                cin >> u;
                cout << "Enter End Station ID: ";
                cin >> v;
                cout << "Enter Route Weight: ";
                cin >> w;
                
                if (cin.fail()) {
                    cout << "⚠ Invalid input!\n";
                    clearInputBuffer();
                } else {
                    g.addEdge(u, v, w);
                    st.push("ADD_EDGE", u, v, w);
                }
                break;
            }

            case 4: { // Delete Route
                int u, v;
                cout << "Enter Start Station ID: ";
                cin >> u;
                cout << "Enter End Station ID: ";
                cin >> v;
                
                if (cin.fail()) {
                    cout << "⚠ Invalid input!\n";
                    clearInputBuffer();
                } else {
                    int w = g.removeEdge(u, v);
                    if (w != -1) {
                        st.push("REM_EDGE", u, v, w);
                    }
                }
                break;
            }

            case 5: // Display Network
                g.display();
                break;

            case 6: // System Status
                g.displaySystemStatus();
                break;

            case 7: { // BFS
                int s;
                cout << "Enter starting station for BFS: ";
                cin >> s;
                
                if (cin.fail()) {
                    cout << "⚠ Invalid input!\n";
                    clearInputBuffer();
                } else {
                    g.BFS(s);
                }
                break;
            }

            case 8: { // DFS
                int s;
                cout << "Enter starting station for DFS: ";
                cin >> s;
                
                if (cin.fail()) {
                    cout << "⚠ Invalid input!\n";
                    clearInputBuffer();
                } else {
                    g.DFS(s);
                }
                break;
            }

            case 9: { // Dijkstra
                int s;
                cout << "Enter starting station for Shortest Path: ";
                cin >> s;
                
                if (cin.fail()) {
                    cout << "⚠ Invalid input!\n";
                    clearInputBuffer();
                } else {
                    g.dijkstra(s);
                }
                break;
            }

            case 10: // MST
                g.MST();
                break;

            case 11: // Detect Cycle
                g.detectCycle();
                break;

            case 12: // Busiest Station
                g.getBusiestStation();
                break;

            case 13: { // Add Passenger
                string name;
                cout << "Enter passenger name: ";
                clearInputBuffer();
                getline(cin, name);
                q.enqueue(name);
                break;
            }

            case 14: // Process Queue
                q.dequeue();
                break;

            case 15: // Display Queue
                q.display();
                break;

            case 16: { // Insert Vehicle
                int id;
                string type;
                cout << "Enter Vehicle ID: ";
                cin >> id;
                
                if (cin.fail()) {
                    cout << "⚠ Invalid input!\n";
                    clearInputBuffer();
                    break;
                }
                
                clearInputBuffer();
                cout << "Enter Vehicle Type (e.g., Bus, Metro, Tram): ";
                getline(cin, type);
                ht.insert(id, type);
                break;
            }

            case 17: { // Search Vehicle
                int id;
                cout << "Enter Vehicle ID to search: ";
                cin >> id;
                
                if (cin.fail()) {
                    cout << "⚠ Invalid input!\n";
                    clearInputBuffer();
                } else {
                    ht.search(id);
                }
                break;
            }

            case 18: { // Remove Vehicle
                int id;
                cout << "Enter Vehicle ID to remove: ";
                cin >> id;
                
                if (cin.fail()) {
                    cout << "⚠ Invalid input!\n";
                    clearInputBuffer();
                } else {
                    ht.remove(id);
                }
                break;
            }

            case 19: // Display Vehicles
                ht.display();
                break;

            case 20: { // Insert Station Metadata
                int id;
                string name;
                cout << "Enter Station ID: ";
                cin >> id;
                
                if (cin.fail()) {
                    cout << "⚠ Invalid input!\n";
                    clearInputBuffer();
                    break;
                }
                
                clearInputBuffer();
                cout << "Enter Station Name: ";
                getline(cin, name);
                tree.insert(id, name);
                break;
            }

            case 21: { // Search Station
                int id;
                cout << "Enter Station ID to search: ";
                cin >> id;
                
                if (cin.fail()) {
                    cout << "⚠ Invalid input!\n";
                    clearInputBuffer();
                } else {
                    tree.search(id);
                }
                break;
            }

            case 22: { // Delete Station Metadata
                int id;
                cout << "Enter Station ID to delete: ";
                cin >> id;
                
                if (cin.fail()) {
                    cout << "⚠ Invalid input!\n";
                    clearInputBuffer();
                } else {
                    tree.remove(id);
                }
                break;
            }

            case 23: // Display BST
                tree.display();
                break;

            case 24: // BST Statistics
                tree.displayStats();
                break;

            case 25: { // Insert Priority
                int p;
                cout << "Enter priority value (lower = higher priority): ";
                cin >> p;
                
                if (cin.fail()) {
                    cout << "⚠ Invalid input!\n";
                    clearInputBuffer();
                } else {
                    heap.insert(p);
                }
                break;
            }

            case 26: { // Extract Min
                int min = heap.extractMin();
                if (min != -1) {
                    cout << "✓ Extracted Highest Priority: " << min << endl;
                }
                break;
            }

            case 27: // Display Heap
                heap.display();
                break;

            case 28: { // Sorting Module
                int n;
                cout << "Enter number of elements: ";
                cin >> n;
                
                if (cin.fail() || n <= 0) {
                    cout << "⚠ Invalid input!\n";
                    clearInputBuffer();
                    break;
                }
                
                int* arr = new int[n];
                cout << "Enter " << n << " elements: ";
                for (int i = 0; i < n; i++) {
                    cin >> arr[i];
                    if (cin.fail()) {
                        cout << "⚠ Invalid input!\n";
                        clearInputBuffer();
                        delete[] arr;
                        break;
                    }
                }

                cout << "\nSelect Sorting Algorithm:\n";
                cout << "1. Bubble Sort    2. Selection Sort\n";
                cout << "3. Insertion Sort 4. Merge Sort\n";
                cout << "5. Quick Sort     6. Heap Sort\n";
                cout << "Choice: ";
                
                int algo;
                cin >> algo;
                
                if (cin.fail()) {
                    cout << "⚠ Invalid choice!\n";
                    clearInputBuffer();
                    delete[] arr;
                    break;
                }

                string algoName;
                switch (algo) {
                    case 1: Sorting::bubble(arr, n); algoName = "Bubble Sort"; break;
                    case 2: Sorting::selection(arr, n); algoName = "Selection Sort"; break;
                    case 3: Sorting::insertion(arr, n); algoName = "Insertion Sort"; break;
                    case 4: Sorting::mergeSort(arr, 0, n - 1); algoName = "Merge Sort"; break;
                    case 5: Sorting::quickSort(arr, 0, n - 1); algoName = "Quick Sort"; break;
                    case 6: Sorting::heapSort(arr, n); algoName = "Heap Sort"; break;
                    default: cout << "⚠ Invalid algorithm choice!\n"; delete[] arr; break;
                }

                if (algo >= 1 && algo <= 6) {
                    Sorting::displayAlgorithmInfo(algoName);
                    cout << "Sorted array: ";
                    for (int i = 0; i < n; i++) {
                        cout << arr[i] << " ";
                    }
                    cout << endl;
                }
                
                delete[] arr;
                break;
            }

            case 29: { // Searching Module
                int n, target;
                cout << "Enter array size: ";
                cin >> n;
                
                if (cin.fail() || n <= 0) {
                    cout << "⚠ Invalid input!\n";
                    clearInputBuffer();
                    break;
                }
                
                int* arr = new int[n];
                cout << "Enter " << n << " elements: ";
                for (int i = 0; i < n; i++) {
                    cin >> arr[i];
                    if (cin.fail()) {
                        cout << "⚠ Invalid input!\n";
                        clearInputBuffer();
                        delete[] arr;
                        break;
                    }
                }
                
                cout << "Enter value to search: ";
                cin >> target;
                
                if (cin.fail()) {
                    cout << "⚠ Invalid input!\n";
                    clearInputBuffer();
                    delete[] arr;
                    break;
                }
                
                cout << "\nSelect Search Algorithm:\n";
                cout << "1. Linear Search\n";
                cout << "2. Binary Search (array must be sorted!)\n";
                cout << "Choice: ";
                
                int searchType;
                cin >> searchType;
                
                if (cin.fail()) {
                    cout << "⚠ Invalid choice!\n";
                    clearInputBuffer();
                    delete[] arr;
                    break;
                }

                int result;
                string searchName;
                
                if (searchType == 1) {
                    result = Sorting::linearSearch(arr, n, target);
                    searchName = "Linear Search";
                } else if (searchType == 2) {
                    result = Sorting::binarySearch(arr, 0, n - 1, target);
                    searchName = "Binary Search";
                } else {
                    cout << "⚠ Invalid choice!\n";
                    delete[] arr;
                    break;
                }

                Sorting::displayAlgorithmInfo(searchName);
                
                if (result != -1) {
                    cout << "✓ Element " << target << " found at index " << result << endl;
                } else {
                    cout << "✗ Element " << target << " not found in array.\n";
                }
                
                delete[] arr;
                break;
            }

            case 30: { // Undo
                Action last = st.pop();
                if (last.type == "ADD_EDGE") {
                    g.removeEdge(last.u, last.v);
                    cout << "✓ Undo: Removed route " << last.u << " ↔ " << last.v << endl;
                } else if (last.type == "REM_EDGE") {
                    g.addEdge(last.u, last.v, last.w);
                    cout << "✓ Undo: Restored route " << last.u << " ↔ " << last.v 
                         << " (Weight: " << last.w << ")\n";
                } else if (last.type == "ADD_STATION") {
                    g.deleteStation(last.u);
                    cout << "✓ Undo: Deactivated station " << last.u << endl;
                } else if (last.type == "REM_STATION") {
                    g.addStation(last.u);
                    cout << "✓ Undo: Reactivated station " << last.u << endl;
                } else {
                    cout << "⚠ Nothing to undo.\n";
                }
                break;
            }

            case 31: // View History
                st.display();
                break;

            case 0: // Exit
                cout << "\n";
                cout << "╔════════════════════════════════════════════════════════════════╗\n";
                cout << "║          Thank you for using ITNMS!                           ║\n";
                cout << "║          Goodbye!                                             ║\n";
                cout << "╚════════════════════════════════════════════════════════════════╝\n";
                break;

            default:
                cout << "⚠ Invalid choice! Please select a valid option (0-31).\n";
                break;
        }

        if (ch != 0) {
            cout << "\nPress Enter to continue...";
            clearInputBuffer();
            cin.get();
        }

    } while (ch != 0);

    return 0;
}