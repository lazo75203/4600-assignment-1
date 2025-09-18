#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <queue>  // For std::queue
#include <utility> // For std::pair
#include <set> // For std::set (visited nodes)
using namespace std;

class DirectedGraph {
private:
    map<char, list<pair<char, int>>> adjList;  // adjacency list with weights

public:
    // Function to add an edge from source to destination with a given weight
    void addEdge(char source, char destination, int weight) {
        adjList[source].push_back(make_pair(destination, weight));
    }

    // Function to print the graph
    void printGraph() {
        for (const auto& node : adjList) {
            cout << "Node " << node.first << " has edges to: ";
            if (node.second.empty()) {
                cout << "No outgoing edges.";
            } else {
                for (const auto& edge : node.second) {
                    cout << "(" << edge.first << ", weight: " << edge.second << ") ";
                }
            }
            cout << endl;
        }
    }

    // Breadth-First Search (BFS) algorithm to find 'G' starting from 'A'
    void bfs(char start, char target) {
        // To keep track of visited nodes
        set<char> visited;
        
        // Queue for BFS
        queue<char> q;

        // Start with the source node
        visited.insert(start);
        q.push(start);

        cout << "BFS starting from node " << start << ": ";

        while (!q.empty()) {
            char node = q.front();
            q.pop();

            // If we found the target node, stop and print a message
            if (node == target) {
                cout << "Node " << target << " found!" << endl;
                return;
            }

            cout << node << " ";  // Print the node
            
            // Visit all the neighbors of the current node
            for (const auto& neighbor : adjList[node]) {
                char neighborNode = neighbor.first;
                if (visited.find(neighborNode) == visited.end()) {
                    visited.insert(neighborNode);
                    q.push(neighborNode);
                }
            }
        }

        // If the target node is not found
        cout << "Node " << target << " not found." << endl;
    }
    
    // Depth-First Search (DFS) algorithm to find 'G' starting from 'A'
    void dfs(char start, char target) {
        set<char> visited;
        cout << "DFS starting from node " << start << ": ";
        dfsHelper(start, visited, target);
        cout << endl;
    }

    // Helper function for DFS
    void dfsHelper(char node, set<char>& visited, char target) {
        // If we found the target node, stop and print a message
        if (node == target) {
            cout << "Node " << target << " found!" << endl;
            return;
        }

        // Mark the node as visited and print it
        visited.insert(node);
        cout << node << " ";

        // Visit all the neighbors of the current node
        for (const auto& neighbor : adjList[node]) {
            char neighborNode = neighbor.first;
            if (visited.find(neighborNode) == visited.end()) {
                dfsHelper(neighborNode, visited, target);
            }
        }
    }
};

int main() {
    DirectedGraph g;

    // Add edges to the graph
    g.addEdge('A', 'B', 5);
    g.addEdge('A', 'C', 3);
    g.addEdge('B', 'C', 2);
    g.addEdge('C', 'D', 6);
    g.addEdge('D', 'A', 1);
    g.addEdge('C', 'G', 4);  // Adding the path to G
    g.addEdge('D', 'G', 7);  // Adding another path to G

    // Print the graph
    g.printGraph();

    // Perform BFS starting from node 'A' and search for node 'G'
    g.bfs('A', 'G');
    
    // Perform DFS starting from node 'A' and search for node 'G'
    g.dfs('A', 'G');

    return 0;
}
