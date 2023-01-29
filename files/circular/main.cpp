#include <iostream>

class CircleLink {

    // Attributes
    struct Node {
        unsigned value;
        Node *previous;
        Node *next;
    };

    Node *head;

public:

    // Constructor
    CircleLink(unsigned initialValue) {
        head = new Node;
        head->value = initialValue;
        head->next = head;
        head->previous = head;
    }

    // Destructor
    ~CircleLink() {
        Node *slowPtr, *fastPtr, *temp;

        slowPtr = head;
        fastPtr = head->next;

        do {
            temp = slowPtr;
            slowPtr = slowPtr->next;
            fastPtr = fastPtr->next->next;
            delete temp;
        } while (slowPtr != fastPtr);
    }

    // Methods
    void addNode(unsigned value) {
        Node *newNode = new Node;
        newNode->value = value;

        if (head->next == head) {
            newNode->previous = head;
            newNode->next = head;
            head->previous = newNode;
            head->next = newNode;
        } else {
            newNode->next = head;
            newNode->previous = head->previous;
            head->previous->next = newNode;
            head->previous = newNode;
        }
    }

    void rotate(int ticks) {
        if (ticks < 0) {
            for (int i = 0; i > ticks; --i)
                head = head->previous;
        } else {
            for (int i = 0; i < ticks; ++i)
                head = head->next;
        }
    }

    void print(bool reverse = false) {
        Node *ptr = head;

        if (reverse) {
            do {
                std::cout << ptr->value << std::endl;
                ptr = ptr->previous;
            } while (ptr != head);
        } else {
            do {
                std::cout << ptr->value << std::endl;
                ptr = ptr->next;
            } while (ptr != head);
        }
    }

};

int main() {
    CircleLink list(1);

    for (int i = 2; i < 20; ++i) {
        list.addNode(i);
    }

    list.print();

    list.rotate(6);

    list.print(true);
    return 0;
}