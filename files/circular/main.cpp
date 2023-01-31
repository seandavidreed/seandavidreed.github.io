#include <iostream>

class CircleLink {

    struct Node {
        unsigned value;
        Node *previous;
        Node *next;
    };

public:
    // Attributes
    Node *head;
    unsigned numNodes;

    // Constructor
    CircleLink() {
        head = nullptr;
        numNodes = 0;
    }

    // Destructor
    ~CircleLink() {
        Node *destroy;
        for (int i = 0; i < numNodes; ++i) {
            destroy = head;
            head = head->next;
            delete destroy;
        }
    }

    // Methods
    void addNode(unsigned value) {
        Node *newNode = new Node;
        newNode->value = value;

        if (head == nullptr) {
            head = newNode;
            head->previous = newNode;
            head->next = newNode;
        } else {
            newNode->next = head;
            newNode->previous = head->previous;
            head->previous->next = newNode;
            head->previous = newNode;
        }

        ++numNodes;
    }

    void deleteNode(unsigned value) {
        Node *ptr = head;
        for (int i = 0; i < numNodes; ++i) {
            if (ptr->value == value) {
                ptr->previous->next = ptr->next;
                ptr->next->previous = ptr->previous;
                delete ptr;
                --numNodes;
                return;
            }

            ptr = ptr->next;
        }
    }

    void mitosis(CircleLink& newList) {

        if (numNodes == 1) {
            newList.head = head;
            std::cerr << "Error: Cannot divide a single-node list!" << std::endl;
            return;
        }

        Node *ptr1, *ptr2;
        unsigned count = 0;

        ptr1 = head;
        ptr2 = head;

        // Get number of nodes in the circular list
        do {
            ptr1 = ptr1->next;
            ptr2 = ptr2->next->next;
            ++count;
        } while (ptr1 != ptr2);

        // Find halfway point and iterate there
        count = (count + 1) / 2;
        for (int i = 0; i < count; ++i) {
            ptr1 = ptr1->next;
        }

        newList.numNodes = numNodes - count;
        numNodes = count;

        Node *newHead = ptr1;
        Node *newTail = head->previous;
        Node *tail = ptr1->previous;

        newHead->previous = newTail;
        newTail->next = newHead;
        newList.head = newHead;

        tail->next = head;
        head->previous = tail;
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
    CircleLink list;

    for (int i = 0; i < 20; ++i) {
        list.addNode(i);
    }

    std::cout << "Print List:" << std::endl;
    list.print();
    std::cout << std::endl;

    std::cout << "Rotate by +6:" << std::endl;
    list.rotate(6);

    std::cout << "Print List in reverse direction:" << std::endl;
    list.print(true);
    std::cout << std::endl;

    std::cout << "Rotate by -6:" << std::endl;
    list.rotate(-6);

    std::cout << "Print List with deleted node:" << std::endl;
    list.deleteNode(7);
    list.print();

    std::cout << "Perform Mitosis First Time:" << std::endl;

    CircleLink newList;
    list.mitosis(newList);

    list.print();
    std::cout << std::endl;

    newList.print();
    std::cout << std::endl;

    std::cout << "Perform Mitosis Second Time:" << std::endl;
    CircleLink newList2;
    list.mitosis(newList2);

    list.print();
    std::cout << std::endl;

    newList2.print();
    std::cout << std::endl;

    std::cout << "Perform Mitosis Third Time:" << std::endl;
    CircleLink newList3;
    list.mitosis(newList3);

    list.print();
    std::cout << std::endl;

    newList3.print();
    std::cout << std::endl;

    std::cout << "Perform Mitosis Fourth Time:" << std::endl;
    CircleLink newList4;
    list.mitosis(newList4);

    list.print();
    std::cout << std::endl;

    newList4.print();
    std::cout << std::endl;

    std::cout << "Perform Mitosis Fifth Time:" << std::endl;
    CircleLink newList5;
    list.mitosis(newList5);

    list.print();
    std::cout << std::endl;

    newList5.print();
    std::cout << std::endl;

    std::cout << "Perform Mitosis Sixth Time:" << std::endl;
    CircleLink newList6;
    list.mitosis(newList6);

    list.print();
    std::cout << std::endl;
    newList.print();
    std::cout << std::endl;
    newList2.print();
    std::cout << std::endl;
    newList3.print();
    std::cout << std::endl;
    newList4.print();
    std::cout << std::endl;
    newList5.print();
    std::cout << std::endl;
    newList6.print();
    std::cout << std::endl;
    std::cout << std::endl;


    return 0;
}