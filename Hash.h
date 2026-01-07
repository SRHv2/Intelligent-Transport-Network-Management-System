#ifndef HASH_H
#define HASH_H
#include <iostream>
#include <string>
using namespace std;

class HashTable {
    static const int SIZE = 10;
    struct Node {
        int id;
        string type;
        Node* next;
    };
    Node* table[SIZE];
    
    int hash(int k) {
        return k % SIZE;
    }

public:
    HashTable() {
        for (int i = 0; i < SIZE; i++) {
            table[i] = NULL;
        }
    }

    // FIXED: Added destructor to prevent memory leaks
    ~HashTable() {
        for (int i = 0; i < SIZE; i++) {
            Node* curr = table[i];
            while (curr) {
                Node* temp = curr;
                curr = curr->next;
                delete temp;
            }
        }
    }

    void insert(int id, string t) {
        if (t.empty()) {
            cout << "Vehicle type cannot be empty!\n";
            return;
        }
        
        int i = hash(id);
        
        // Check if ID already exists
        Node* check = table[i];
        while (check) {
            if (check->id == id) {
                cout << "Vehicle ID " << id << " already exists! Updating type to: " << t << "\n";
                check->type = t;
                return;
            }
            check = check->next;
        }
        
        // Insert new node at head
        table[i] = new Node{id, t, table[i]};
        cout << "Vehicle ID " << id << " (" << t << ") added successfully.\n";
    }

    void search(int id) {
        int i = hash(id);
        Node* c = table[i];
        
        while (c) {
            if (c->id == id) {
                cout << "✓ Vehicle Found - ID: " << id << ", Type: " << c->type << endl;
                return;
            }
            c = c->next;
        }
        
        cout << "✗ Vehicle ID " << id << " not found in database.\n";
    }

    void remove(int id) {
        int i = hash(id);
        Node* c = table[i];
        Node* p = NULL;
        
        while (c) {
            if (c->id == id) {
                if (p) {
                    p->next = c->next;
                } else {
                    table[i] = c->next;
                }
                cout << "Vehicle ID " << id << " (" << c->type << ") removed successfully.\n";
                delete c;
                return;
            }
            p = c;
            c = c->next;
        }
        
        cout << "✗ Vehicle ID " << id << " not found. Cannot remove.\n";
    }

    // Display all vehicles
    void display() {
        cout << "\n=== Vehicle Database ===\n";
        bool hasVehicles = false;
        
        for (int i = 0; i < SIZE; i++) {
            Node* curr = table[i];
            if (curr) {
                cout << "Hash Slot [" << i << "]: ";
                while (curr) {
                    cout << "(ID:" << curr->id << ", Type:" << curr->type << ") ";
                    curr = curr->next;
                    hasVehicles = true;
                }
                cout << endl;
            }
        }
        
        if (!hasVehicles) {
            cout << "No vehicles in database.\n";
        }
        cout << "=======================\n";
    }

    // Count total vehicles
    int count() {
        int total = 0;
        for (int i = 0; i < SIZE; i++) {
            Node* curr = table[i];
            while (curr) {
                total++;
                curr = curr->next;
            }
        }
        return total;
    }
};

#endif