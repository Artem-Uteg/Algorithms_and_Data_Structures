#include<iostream>
#include<string>

using namespace std;

struct Node {
    int value;
    Node* previos;
};

struct Stack {
public:
    int lenght = 0;
    Node* stack = new Node();

    bool is_empty() { return stack -> previos == nullptr; }
    
    int back() { return stack -> value; }
    int size() { return lenght; }
    
    void push(int number) {
        ++lenght;
        Node* New  = new Node();
        New -> value = number;
        New -> previos = stack;
        stack = New;
    }
    
    int pop() {
        --lenght;
        Node* tail = stack -> previos;
        int del_element = stack -> value;
        delete stack;
        stack = tail;
        return del_element;
    }

    void clear() {
        while (lenght > 0) {
            --lenght;
            Node* tail = stack -> previos;
            delete stack;
            stack = tail;
        }
    }
};

int main() {
    Stack stack;
    
    int number;
    string command;

    while (true) {
        cin >> command;

        if (command == "push") {
            cin >> number;
            cout << "ok" << '\n';
            stack.push(number);

        } else if (command == "pop") {
            if (stack.is_empty()) cout << "error" << '\n';
            else cout << stack.pop() << '\n';
        
        } else if (command == "back") {
            if (stack.is_empty()) cout << "error" << '\n';
            else cout << stack.back() << '\n';
        
        } else if (command == "size") {
            cout << stack.size() << '\n';
        
        } else if (command == "clear") {
            cout << "ok" << '\n';
            stack.clear();
        
        } else {
            cout << "bye" << '\n';
            return 0;
        }
    }
}
 
