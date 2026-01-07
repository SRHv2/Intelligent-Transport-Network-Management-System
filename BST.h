#ifndef BST_H
#define BST_H
#include <iostream>
#include <string>
using namespace std;

class BST {
    struct Node {
        int id;
        string name;
        Node *l, *r;
    } *root;

    Node* insert(Node* n, int id, string name) {
        if (!n) return new Node{id, name, NULL, NULL};
        if (id < n->id)
            n->l = insert(n->l, id, name);
        else if (id > n->id)
            n->r = insert(n->r, id, name);
        else {
            // ID already exists, update name
            cout << "Station ID " << id << " already exists. Updating name to: " << name << "\n";
            n->name = name;
        }
        return n;
    }

    void inorder(Node* n) {
        if (!n) return;
        inorder(n->l);
        cout << "[ID: " << n->id << " | Name: " << n->name << "] ";
        inorder(n->r);
    }

    void clear(Node* n) {
        if (!n) return;
        clear(n->l);
        clear(n->r);
        delete n;
    }

    // Search helper
    bool searchHelper(Node* n, int id) {
        if (!n) return false;
        if (n->id == id) {
            cout << "Station Found - ID: " << id << ", Name: " << n->name << "\n";
            return true;
        }
        if (id < n->id) return searchHelper(n->l, id);
        return searchHelper(n->r, id);
    }

    // Find minimum node (helper for delete)
    Node* findMin(Node* n) {
        while (n && n->l) n = n->l;
        return n;
    }

    // Delete helper
    Node* deleteNode(Node* n, int id) {
        if (!n) return NULL;
        
        if (id < n->id) {
            n->l = deleteNode(n->l, id);
        } else if (id > n->id) {
            n->r = deleteNode(n->r, id);
        } else {
            // Node found, delete it
            if (!n->l) {
                Node* temp = n->r;
                delete n;
                return temp;
            }
            if (!n->r) {
                Node* temp = n->l;
                delete n;
                return temp;
            }
            
            // Node has two children
            Node* temp = findMin(n->r);
            n->id = temp->id;
            n->name = temp->name;
            n->r = deleteNode(n->r, temp->id);
        }
        return n;
    }

    // Count nodes
    int countNodes(Node* n) {
        if (!n) return 0;
        return 1 + countNodes(n->l) + countNodes(n->r);
    }

    // Height calculation
    int height(Node* n) {
        if (!n) return 0;
        int lh = height(n->l);
        int rh = height(n->r);
        return 1 + (lh > rh ? lh : rh);
    }

public:
    BST() { root = NULL; }
    
    ~BST() { clear(root); }

    void insert(int id, string name) {
        if (name.empty()) {
            cout << "Station name cannot be empty!\n";
            return;
        }
        root = insert(root, id, name);
    }

    // Public search method
    void search(int id) {
        if (!searchHelper(root, id)) {
            cout << "Station ID " << id << " not found in database.\n";
        }
    }

    // Public delete method
    void remove(int id) {
        if (!root) {
            cout << "Database is empty!\n";
            return;
        }
        
        // Check if exists first
        Node* check = root;
        bool found = false;
        while (check) {
            if (check->id == id) {
                found = true;
                break;
            }
            check = (id < check->id) ? check->l : check->r;
        }
        
        if (!found) {
            cout << "✗ Station ID " << id << " not found. Cannot delete.\n";
            return;
        }
        
        root = deleteNode(root, id);
        cout << "Station ID " << id << " deleted successfully.\n";
    }

    void display() {
        if (!root) {
            cout << "No stations in the database.\n";
        } else {
            cout << "Registered Stations (In-Order): ";
            inorder(root);
            cout << endl;
        }
    }

    // Display statistics
    void displayStats() {
        cout << "\n=== BST Statistics ===\n";
        cout << "Total Stations: " << countNodes(root) << "\n";
        cout << "Tree Height: " << height(root) << "\n";
        cout << "======================\n";
    }
};

#endif