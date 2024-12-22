#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include "graph.cpp"
using namespace std;

// Nearest Neighbour Heuristic
vector<int> nearestNeighbourHeuristic(const vector<Point> &points);
// Nearest Insertion Heuristic
vector<int> nearestInsertionHeuristic(const vector<Point> &points);
// Greedy Heuristic
vector<int> greedyHeuristic(const vector<Point> &points);
// MST-based heuristic to generate a TSP tour
vector<int> mstHeuristic(const vector<Point> &points);

vector<int> nearestNeighbourHeuristic(const vector<Point> &points)
{
    vector<int> tour;
    vector<bool> visited(points.size(), false);
    int current = 0;
    tour.push_back(current);
    visited[current] = true;
    for (int i = 1; i < points.size(); i++)
    {
        int next = -1;
        double minDist = numeric_limits<double>::max();
        for (int j = 0; j < points.size(); j++)
        {
            if (!visited[j] && calculateDistance(points[current], points[j]) < minDist)
            {
                minDist = calculateDistance(points[current], points[j]);
                next = j;
            }
        }
        tour.push_back(next);
        visited[next] = true;
        current = next;
    }
    return tour;
}

// Nearest Insertion Heuristic
vector<int> nearestInsertionHeuristic(const vector<Point> &points)
{
    vector<int> tour;
    vector<bool> visited(points.size(), false);
    tour.push_back(0);
    tour.push_back(1);
    visited[0] = true;
    visited[1] = true;
    while (tour.size() < points.size())
    {
        int nearestPoint = -1;
        int bestInsertPos = -1;
        double minDistIncrease = numeric_limits<double>::max();
        for (int i = 0; i < points.size(); i++)
        {
            if (visited[i])
            {
                continue;
            }
            for (int j = 0; j < tour.size() - 1; j++)
            {
                int p1 = tour[j];
                int p2 = tour[j + 1];
                double distIncrease = calculateDistance(points[p1], points[i]) + calculateDistance(points[i], points[p2]) - calculateDistance(points[p1], points[p2]);
                if (distIncrease < minDistIncrease)
                {
                    minDistIncrease = distIncrease;
                    nearestPoint = i;
                    bestInsertPos = j + 1;
                }
            }
        }
        tour.insert(tour.begin() + bestInsertPos, nearestPoint);
        visited[nearestPoint] = true;
    }
    return tour;
}

// Greedy Heuristic
vector<int> greedyHeuristic(const vector<Point> &points)
{
    int n = points.size();
    vector<vector<int>> adjList(n);
    vector<int> degree(n, 0);
    vector<Edge> edges = generateEdges(points);
    vector<int> tour;
    for (const Edge &edge : edges)
    {
        if (degree[edge.getFrom()] < 2 && degree[edge.getTo()] < 2)
        {
            if (!createsCycle(adjList, edge.getFrom(), edge.getTo(), n))
            {
                adjList[edge.getFrom()].push_back(edge.getTo());
                adjList[edge.getTo()].push_back(edge.getFrom());
                degree[edge.getFrom()]++;
                degree[edge.getTo()]++;
            }
        }
    }
    int current = 0;
    for (int i = 0; i < n; i++)
    {
        if (adjList[i].size() < 2)
        {
            current = i;
            break;
        }
    }
    vector<bool> visited(n, false);
    while (tour.size() < n)
    {
        tour.push_back(current);
        visited[current] = true;
        for (int neighbor : adjList[current])
        {
            if (!visited[neighbor])
            {
                current = neighbor;
                break;
            }
        }
    }
    return tour;
}

// MST-based heuristic to generate a TSP tour
vector<int> mstHeuristic(const vector<Point> &points)
{
    int n = points.size();
    vector<Edge> mstEdges = constructMST(points);
    vector<vector<int>> adjList(n);
    for (const Edge &edge : mstEdges)
    {
        adjList[edge.getFrom()].push_back(edge.getTo());
        adjList[edge.getTo()].push_back(edge.getFrom());
    }
    vector<bool> visited(n, false);
    vector<int> tour;
    dfs(0, adjList, visited, tour);
    return tour;
}