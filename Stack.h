#ifndef STACK_H
#define STACK_H
#include <iostream>
#include <string>
using namespace std;

struct Action {
    string type;
    int u, v, w;
};

class Stack {
    static const int MAX_SIZE = 100;
    Action data[MAX_SIZE];
    int top;

public:
    Stack() { top = -1; }

    void push(string t, int u = 0, int v = 0, int w = 0) {
        if (top >= MAX_SIZE - 1) {
            cout << "⚠ Stack overflow! Cannot store more actions.\n";
            return;
        }
        data[++top] = {t, u, v, w};
    }

    Action pop() {
        if (top < 0) {
            return {"NONE", 0, 0, 0};
        }
        return data[top--];
    }

    Action peek() {
        if (top < 0) {
            return {"NONE", 0, 0, 0};
        }
        return data[top];
    }

    bool isEmpty() {
        return top < 0;
    }

    int size() {
        return top + 1;
    }

    void display() {
        if (top < 0) {
            cout << "No action history.\n";
            return;
        }
        
        cout << "\n=== Action History (Most Recent First) ===\n";
        for (int i = top; i >= 0; i--) {
            cout << (top - i + 1) << ". ";
            if (data[i].type == "ADD_EDGE") {
                cout << "Added route: " << data[i].u << " ↔ " << data[i].v 
                     << " (Weight: " << data[i].w << ")\n";
            } else if (data[i].type == "REM_EDGE") {
                cout << "Removed route: " << data[i].u << " ↔ " << data[i].v 
                     << " (Weight: " << data[i].w << ")\n";
            } else if (data[i].type == "ADD_STATION") {
                cout << "Added station: " << data[i].u << "\n";
            } else if (data[i].type == "REM_STATION") {
                cout << "Removed station: " << data[i].u << "\n";
            } else {
                cout << "Action: " << data[i].type << "\n";
            }
        }
        cout << "==========================================\n";
    }

    void clear() {
        top = -1;
        cout << "Action history cleared.\n";
    }
};

#endif