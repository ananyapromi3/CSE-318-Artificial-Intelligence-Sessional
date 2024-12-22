#include <iostream>
#include <vector>
#include <queue>
#include "edge.cpp"
using namespace std;

// Helper functions to check if adding an edge creates a cycle of less than n edges
bool dfsCycleCheck(const vector<vector<int> > &adjList, vector<bool> &visited, int current, int parent)
{
    visited[current] = true;
    for (int neighbor : adjList[current])
    {
        if (neighbor == parent)
        {
            continue;
        }
        if (visited[neighbor] || dfsCycleCheck(adjList, visited, neighbor, current))
        {
            return true;
        }
    }
    return false;
}

bool createsCycle(vector<vector<int> > &adjList, int start, int end, int n)
{
    vector<bool> visited(n, false);
    adjList[start].push_back(end);
    adjList[end].push_back(start);
    bool hasCycle = dfsCycleCheck(adjList, visited, start, -1);
    adjList[start].pop_back();
    adjList[end].pop_back();
    return hasCycle;
}

vector<Edge> constructMST(const vector<Point> &points)
{
    int n = points.size();
    vector<bool> inMST(n, false);
    vector<Edge> mstEdges;
    priority_queue<Edge, vector<Edge>, greater<Edge> > minHeap;
    inMST[0] = true;
    for (int i = 1; i < n; i++)
    {
        minHeap.push(Edge(0, i, calculateDistance(points[0], points[i])));
    }
    while (mstEdges.size() < n - 1)
    {
        Edge edge = minHeap.top();
        minHeap.pop();
        if (inMST[edge.getTo()])
        {
            continue;
        }
        mstEdges.push_back(edge);
        inMST[edge.getTo()] = true;
        for (int i = 0; i < n; i++)
        {
            if (!inMST[i])
            {
                minHeap.push(Edge(edge.getTo(), i, calculateDistance(points[edge.getTo()], points[i])));
            }
        }
    }
    return mstEdges;
}

// DFS traversal on MST to create a TSP tour
void dfs(int node, const vector<vector<int> > &adjList, vector<bool> &visited, vector<int> &tour) 
{
    visited[node] = true;
    tour.push_back(node);
    for (int neighbor : adjList[node]) 
    {
        if (!visited[neighbor]) 
        {
            dfs(neighbor, adjList, visited, tour);
        }
    }
}

void printTour(const vector<int> &tour)
{
    for (int node : tour)
    {
        cout << node << " -> ";
    }
    cout << tour[0] << endl;
}