#ifndef QUEUE_H
#define QUEUE_H
#include <iostream>
#include <string>
using namespace std;

class Queue {
    struct Node {
        string name;
        Node* next;
    } *front, *rear;
    
    int count; // Track queue size

public:
    Queue() {
        front = rear = NULL;
        count = 0;
    }

    ~Queue() {
        while (front) {
            Node* t = front;
            front = front->next;
            delete t;
        }
    }

    void enqueue(string n) {
        if (n.empty()) {
            cout << "⚠ Cannot enqueue empty name!\n";
            return;
        }
        
        Node* t = new Node{n, NULL};
        if (!rear) {
            front = rear = t;
        } else {
            rear->next = t;
            rear = t;
        }
        count++;
        cout << "✓ Passenger '" << n << "' added to queue (Position: " << count << ")\n";
    }

    void dequeue() {
        if (!front) {
            cout << "⚠ Queue is empty! No passengers to process.\n";
            return;
        }
        
        Node* t = front;
        cout << "✓ Processing passenger: " << t->name << endl;
        front = front->next;
        delete t;
        count--;
        
        if (!front) {
            rear = NULL;
        }
    }

    void display() {
        if (!front) {
            cout << "Queue is empty.\n";
            return;
        }
        
        cout << "\n=== Passenger Queue (Front → Rear) ===\n";
        Node* c = front;
        int pos = 1;
        while (c) {
            cout << pos++ << ". " << c->name;
            if (c->next) cout << " → ";
            c = c->next;
        }
        cout << "\nTotal passengers waiting: " << count << "\n";
        cout << "======================================\n";
    }

    bool isEmpty() {
        return front == NULL;
    }

    int size() {
        return count;
    }

    string peek() {
        if (!front) {
            return "";
        }
        return front->name;
    }
};

#endif