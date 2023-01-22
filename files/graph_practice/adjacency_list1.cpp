#include <iostream>

class Graph {

    struct Vertex {
        int value;
        Vertex *next;
    };

public:

    // Attributes
    Vertex **head;
    int numVertices;

    // Constructor
    Graph() {
        std::cout << "Number of Vertices: ";
        std::cin >> numVertices;

        head = new Vertex*[numVertices]{};
        
        // initialize head pointer for all vertices
        for (int i = 0; i < numVertices; ++i) {
            head[i] = nullptr;
        }

        // receive edges
        int v1, v2;
        std::cout << "Enter edges <vertex> <vertex>:" << std::endl;
        while (1) {
            std::cin >> v1 >> v2;

            // check for invalid user input
            if (v1 >= numVertices || v2 >= numVertices || v1 < 0 || v2 < 0) {
                std::cout << "Invalid Input: out of range" << std::endl;
                continue;
            }

            // end input if user enters 0 0
            if (v1 == 0 && v2 == 0) break;

            Vertex *vertex = new Vertex;
            vertex->value = v2;
            vertex->next = head[v1];
            head[v1] = vertex;

            // Create undirected graph
            // vertex = new Vertex;
            // vertex->value = v1;
            // vertex->next = head[v2];
            // head[v2] = vertex;
        }
    }

    // Destructor
    ~Graph() {
        for (int i = 0; i < numVertices; ++i) {
            delete[] head[i];
        }

        delete[] head;
    }

    // Methods
    void print() {
        Vertex *ptr {};

        for (int i = 0; i < numVertices; ++i) {
            std::cout << i;
            ptr = head[i];
            while (ptr != nullptr) {
                std::cout << " -> " << ptr->value;
                ptr = ptr->next;
            }
            std::cout << std::endl;
        }
    }
};

int main() {

    Graph graph;

    graph.print();

    std::cout << "Number of Vertices: " << graph.numVertices << std::endl;

    return 0;
}