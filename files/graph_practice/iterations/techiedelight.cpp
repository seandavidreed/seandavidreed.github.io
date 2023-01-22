#include <iostream>

typedef struct _vertex {
    int value;
    _vertex *next;
} vertex;

typedef struct _edge {
    int src, dest;
} edge;

class Graph {

    vertex *fetchVertex(int dest, vertex *head) {
        vertex *newVertex = new vertex;
        newVertex->value = dest;
        newVertex->next = head;
        
        return newVertex;
    }

    int numVertices;

public:

    vertex **head;

    // Constructor
    Graph(edge edges[], int n, int numVertices) {
        head = new vertex*[numVertices]{};
        this->numVertices = numVertices;

        // Initialize head pointer for all vertices
        for (int i = 0; i < numVertices; ++i) {
            head[i] = nullptr;
        }

        // Add edges to the directed graph
        for (unsigned int i = 0; i < n; ++i) {
            int src = edges[i].src;
            int dest = edges[i].dest;

            vertex *newVertex = fetchVertex(dest, head[src]);

            head[src] = newVertex;

            // uncomment the following code for undirected graph

            /*
            newVertex = fetchVertex(dest, head[dest]);
            head[dest] = newVertex;
            */
        }
    }

    // Destructor
    ~Graph() {
        for (unsigned int i = 0; i < numVertices; ++i) {
            delete[] head[i]; 
        }
        delete[] head;
    }
};

void printList(vertex *ptr) {
    while (ptr != nullptr) {
        std::cout << " -> " << ptr->value;
        ptr = ptr->next;
    }
    std::cout << std::endl;
}


int main() {
    // an array of graph edges as per the diagram
    edge edges[] = {
        {0, 1}, {1, 2}, {2, 0}, {2, 1}, {3, 2}, {4, 5}, {5, 4}
    };

    // total number of vertices in the graph
    int numVertices {6};

    // calculate the total number of edges
    int n = sizeof(edges) / sizeof(edges[0]);

    // construct graph
    Graph graph(edges, n, numVertices);

    // print adjacency list representation of a graph
    for (unsigned int i = 0; i < numVertices; ++i) {
        // print given vertex
        std::cout << i;

        // print all its neighboring vertices
        printList(graph.head[i]);
    }
    return 0;
}