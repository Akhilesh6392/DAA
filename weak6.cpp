struct Edge {
    int src, dest;
};
 
// A class to represent a graph object
class Graph
{
public:
    // a vector of vectors to represent an adjacency list in C++
    vector<vector<int>> adjList;
 
    // Graph Constructor
    Graph(vector<Edge> const &edges, int N)
    {
        // resize the vector to hold `N` elements each of type `vector<int>`
        adjList.resize(N);
 
        // add edges to the directed graph
        for (auto &edge: edges) {
            adjList[edge.src].push_back(edge.dest);
        }
    }
};
 
// Function to perform BFS traversal from a given source vertex in a graph to
// determine if a destination vertex is reachable from the source or not
bool isConnected(Graph const &graph, int src, int dest,
                vector<bool> &discovered)
{
    // create a queue for doing BFS
    queue<int> q;
 
    // mark the source vertex as discovered
    discovered[src] = true;
 
    // enqueue source vertex
    q.push(src);
 
    // loop till queue is empty
    while (!q.empty())
    {
        // dequeue front node and print it
        int v = q.front();
        q.pop();
 
        // if destination vertex is found
        if (v == dest) {
            return true;
        }
 
        // do for every edge `v —> u`
        for (int u: graph.adjList[v])
        {
            if (!discovered[u])
            {
                // mark it as discovered and enqueue it
                discovered[u] = true;
                q.push(u);
            }
        }
    }
 
    return false;
}
 */
 /*****************************************************************************************************/
 #include <iostream>
#include <vector>
using namespace std;
 
// Data structure to store a graph edge
struct Edge {
    int src, dest;
};
 
// A class to represent a graph object
class Graph
{
public:
    // a vector of vectors to represent an adjacency list in C++
    vector<vector<int>> adjList;
 
    // Graph Constructor
    Graph(vector<Edge> const &edges, int N)
    {
        // resize the vector to hold `N` elements of type `vector<int>`
        adjList.resize(N);
 
        // add edges to the directed graph
        for (auto &edge: edges) {
            adjList[edge.src].push_back(edge.dest);
        }
    }
};
 
// Function to perform DFS traversal in a directed graph to find the
// complete path between source and destination vertices
bool isConnected(Graph const &graph, int src, int dest,
        vector<bool> &discovered, vector<int> &path)
{
    // mark the current node as discovered
    discovered[src] = true;
 
    // include the current node in the path
    path.push_back(src);
 
    // if destination vertex is found
    if (src == dest) {
        return true;
    }
 
    // do for every edge `src —> i`
    for (int i: graph.adjList[src])
    {
        // if `u` is not yet discovered
        if (!discovered[i])
        {
            // return true if the destination is found
            if (isConnected(graph, i, dest, discovered, path)) {
                return true;
            }
        }
    }
 
    // backtrack: remove the current node from the path
    path.pop_back();
 
    // return false if destination vertex is not reachable from src
    return false;
}
 
// Utility function to print a path
void printPath(vector<int> const &path)
{
    for (int i: path) {
        cout << i << ' ';
    }
    cout << endl;
}
 
int main()
{
    // vector of graph edges as per the above diagram
    vector<Edge> edges = {
        {0, 3}, {1, 0}, {1, 2}, {1, 4}, {2, 7}, {3, 4},
        {3, 5}, {4, 3}, {4, 6}, {5, 6}, {6, 7}
    };
 
    // total number of nodes in the graph (labeled from 0 to `N-1`)
    int N = 8;
 
    // build a graph from the given edges
    Graph graph(edges, N);
 
    // to keep track of whether a vertex is discovered or not
    vector<bool> discovered(N);
 
    // source and destination vertex
    int src = 0, dest = 7;
 
    // vector to store the complete path between source and destination
    vector<int> path;
 
    // perform DFS traversal from the source vertex to check the connectivity
    // and store path from the source vertex to the destination vertex
    if (isConnected(graph, src, dest, discovered, path))
    {
        cout << "A path exists from vertex " << src << " to vertex " << dest;
        cout << "\nThe complete path is "; printPath(path);
    }
    else {
        cout << "No path exists between vertices " << src << " and " << dest;
    }
 
    return 0;
}

/****************************************II problem*************************************************************/
#include <iostream>
#include <queue>
#define V 5
 
using namespace std;
 
// This function returns true if graph
// G[V][V] is Bipartite, else false
bool isBipartite(int G[][V], int src)
{
    // Create a color array to store colors
    // assigned to all vertices. Vertex
    // number is used as index in this array.
    // The value '-1' of colorArr[i]
    // is used to indicate that no color
    // is assigned to vertex 'i'. The value 1
    // is used to indicate first color
    // is assigned and value 0 indicates
    // second color is assigned.
    int colorArr[V];
    for (int i = 0; i < V; ++i)
        colorArr[i] = -1;
 
    // Assign first color to source
    colorArr[src] = 1;
 
    // Create a queue (FIFO) of vertex
    // numbers and enqueue source vertex
    // for BFS traversal
    queue <int> q;
    q.push(src);
 
    // Run while there are vertices
    // in queue (Similar to BFS)
    while (!q.empty())
    {
        // Dequeue a vertex from queue ( Refer http://goo.gl/35oz8 )
        int u = q.front();
        q.pop();
 
        // Return false if there is a self-loop
        if (G[u][u] == 1)
        return false;
 
        // Find all non-colored adjacent vertices
        for (int v = 0; v < V; ++v)
        {
            // An edge from u to v exists and
            // destination v is not colored
            if (G[u][v] && colorArr[v] == -1)
            {
                // Assign alternate color to this adjacent v of u
                colorArr[v] = 1 - colorArr[u];
                q.push(v);
            }
 
            // An edge from u to v exists and destination
            // v is colored with same color as u
            else if (G[u][v] && colorArr[v] == colorArr[u])
                return false;
        }
    }
 
    // If we reach here, then all adjacent 
    // vertices can be colored with alternate color
    return true;
}
 
// Driver program to test above function
int main()
{
    int G[][V] = {{0, 1, 1, 0, 1},
        {1, 0, 1, 1, 1},
        {1, 1, 0, 1, 0},
        {0, 1, 1, 0, 1},
        {0, 1, 0, 1, 0}
    };
 
    isBipartite(G, 0) ? cout << "Yes" : cout << "No";
    return 0;
}
