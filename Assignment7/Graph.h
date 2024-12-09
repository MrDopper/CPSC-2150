#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
class Edge{
public:
    // assume u and v are two vertices 
    // vertices are zero-indexed
    int u;
    int v;

    Edge(){
        u = -1; // invalid vertex index
        v = -1; // invalid vertex index
    }

    Edge(int _u, int _v){
        u = _u;
        v = _v;
    }
};

class Graph
{
private:
    vector<int> vertices;
    vector<vector<int>> adjacencyList;
    vector<Edge> edgeList;

public:
    Graph()
    {
    }

    Graph(vector<vector<bool>> adjacencyMatrix)
    {
        // adjacencyMatrix has dimension n x n with zeroes along the main diagonal
        // assume row 0 is for vertex 0, row 1 is for vertex 1 and so on

        // TASKS: add methods to do the following:
        // build vertices, adjacencyList and edgeList from adjacencyMatrix.

        BuildVertices(adjacencyMatrix.size());
        BuildAdjacencyList(adjacencyMatrix);
        BuildEdgeList();
    }

    void BuildVertices(int numberOfVertices)
    {
        for (int i = 0; i < numberOfVertices; i++)
        {
            vertices.push_back(i);
        }
    }

    void BuildAdjacencyList(vector<vector<bool>> adjacencyMatrix)
    {
        
    }

    void BuildEdgeList()
    {
        // build edge list from adjacency list
                        
    }

    void ShowVertices()
    {
        cout << "Vertices: ";
        for (int i = 0; i < vertices.size(); i++)
        {
            cout << vertices[i] << ", ";
        }
        cout << endl;
    }

    void ShowAdjacencyList()
    {
        // display adjacency list
    }

    void ShowEdgeList()
    {
        // display edge list
        
    }

    int VertexCount()
    {
        // returns the number of vertices in the graph
        
    }

    int EdgeCount()
    {
        // returns the number of edges in the graph
        
    }

    void ShowNeighbors(int v)
    {
        // display neighbors of vertex v i.e. all friends of v
        
    }

    int Degree(int v)
    {
        // return the degree of vertex v i.e. number of friends of v
        
    }

    void ShowDegrees()
    {
        // display degrees of all vertices sorted in descending order of degree
        cout << "Degrees of vertices:\n";
        
    }

    bool HasEdge(int v1, int v2)
    {
        // returns true if there is an edge between vertices v1 n v2; false otherwise
    }

    void DFS(int v1, int v2, vector<bool> &visited, vector<int> &path)
    {
        // depth first search to find a path from v1 to v2

    }

    vector<int> Path(int v1, int v2){
        // returns the path (all vertices that fall along the path) from vertex v1 to vertex v2
        // if there is no path, return an empty vector

        if(v1 < 0 || v1 >= adjacencyList.size() || v2 < 0 || v2 >= adjacencyList.size() || v1 == v2){
            cout << "Invalid vertex index!\n";
            return vector<int>();
        }

        
        vector<bool> visited(vertices.size(), false);
        vector<int> path;
        DFS(v1, v2, visited, path);
        if(!visited[v2]){
            path.clear();
        }
        return path;
    }

    void ShowPath(int v1, int v2, vector<int> path){
        if(v1 < 0 || v1 >= adjacencyList.size() || v2 < 0 || v2 >= adjacencyList.size()){
            cout << "Invalid vertex index!\n";
            return;
        }

        if(path.size() == 0){
            cout << "No path from " << v1 << " to " << v2 << endl;
            return;
        }

        cout << "Path from " << v1 << " to " << v2 << ": ";
        for(int i = 0; i < path.size(); i++){
            cout << path[i] << ", ";
        }
        cout << endl;
    }

    bool HasCycle(){
        // return true if graph has a cycle (starting from a node we follow edges to return back to the same vertex); false otherwise
        
    }

    
};

#endif