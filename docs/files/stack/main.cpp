#include <iostream>

class Stack {

    struct Node {
        unsigned int value;
        Node *next;
    };

    Node *top;

public:

    Stack() {
        top = nullptr;
    }

    ~Stack() {
        while (top) {
            Node *temp = top;
            top = top->next;
            delete temp;
        }
    }

    void push(unsigned int value) {
        Node *newNode = new Node;
        newNode->value = value;
        newNode->next = top;
        top = newNode;
    }

    int pop() {
        if (top == nullptr)
            return -1;

        Node *temp = top;
        unsigned int value = top->value;
        top = top->next;
        delete temp;
        return value;
    }

    bool isEmpty() {
        if (top == nullptr)
            return 1;
        else
            return 0;
    }

    unsigned int size() {
        Node *ptr = top;
        unsigned int count {0};
        while (ptr) {
            ++count;
            ptr = ptr->next;
        }
        return count;
    }

};

int main() {
    Stack stack;
    std::cout << "stack.isEmpty(): " << std::boolalpha << stack.isEmpty() << std::endl;

    std::cout << "stack.pop(): " << stack.pop() << std::endl;

    std::cout << "stack.size(): " << stack.size() << std::endl;

    stack.push(12);
    std::cout << "stack.push(12)" << std::endl;

    stack.push(45);
    std::cout << "stack.push(45)" << std::endl;

    stack.push(2300);
    std::cout << "stack.push(2300)" << std::endl;

    std::cout << "stack.size(): " << stack.size() << std::endl;

    stack.push(8);
    std::cout << "stack.push(8)" << std::endl;

    std::cout << "stack.pop(): " << stack.pop() << std::endl;

    std::cout << "stack.pop(): " << stack.pop() << std::endl;

    std::cout << "stack.size(): " << stack.size() << std::endl;

    std::cout << "stack.isEmpty(): " << std::boolalpha << stack.isEmpty() << std::endl;

    return 0;
}