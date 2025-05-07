#include <iostream>
#include <cstdlib>

class Graph {

    unsigned **matrix {};

public:

    // Attributes
    unsigned numVertices {};
    unsigned i, j {};

    // Constructor
    Graph() {
        std::cout << "Enter the number of vertices: ";
        std::cin >> numVertices;

        matrix = new unsigned*[numVertices];

        for (i = 0; i < numVertices; ++i) {
            matrix[i] = new unsigned[numVertices];
            for (j = 0; j < numVertices; ++j) {
                matrix[i][j] = 0;
            }
        }

        srand(time(NULL));
        // total possible edges for a directed, complete graph
        unsigned totalPossibleEdges {numVertices * (numVertices - 1)};
        while (totalPossibleEdges) {
            i = (rand() * 123 + j) % numVertices;
            j = (rand() * i) % numVertices;
            if (i == j) continue;
            matrix[i][j] = 1;
            --totalPossibleEdges;
        }
    }

    // Destructor
    ~Graph() {
        for (i = 0; i < numVertices; ++i) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }

    // Methods
    void print() {
        for (i = 0; i < numVertices; ++i) {
            for (j = 0; j < numVertices; ++j) {
                if (matrix[i][j]) {
                    std::cout << i << " -> " << j << std::endl;
                }
            }
        }
    }

    int findPath(unsigned vertex) {
        if (vertex < 0 || vertex >= numVertices) {
            return -1;
        }

        bool found {};
        unsigned count {};
        std::cout << vertex;
        while (1) {
            found = 0;
            for (j = 0; j < numVertices; ++j) {
                if (matrix[vertex][j]) {
                    vertex = j;
                    found = 1;
                    ++count;
                    std::cout << " -> " << vertex;
                }
            }
            if (!found) {
                std::cout << std::endl;
                return 0;
            }
            if (count > numVertices) {
                std::cout << std::endl;
                return 2;
            }
        }
        return 0;
    }
};

int main() {

    Graph graph;

    graph.print();

    unsigned vertex {};
    int result {};
    while (1) {
        std::cout << "Enter starting vertex: ";
        std::cin >> vertex;
        std::cin.clear();
        result = graph.findPath(vertex);

        char choice {};
        std::cout << "Continue? [y/n]: ";
        std::cin >> choice;
        std::cin.clear();
        if (choice == 'n') break;
    }

    std::cout << result << std::endl;

    return 0;
}