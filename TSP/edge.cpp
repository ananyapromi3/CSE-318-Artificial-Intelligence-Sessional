#include <iostream>
#include <vector>
#include <algorithm>
#include "point.cpp"
using namespace std;

class Edge
{
private:
    int from;
    int to;
    double weight;

public:
    Edge(int from, int to, double weight)
    {
        this->from = from;
        this->to = to;
        this->weight = weight;
    }
    int getFrom() const { return from; }
    int getTo() const { return to; }
    double getWeight() const { return weight; }
    bool operator<(const Edge &other) const
    {
        return weight < other.weight;
    }
    bool operator>(const Edge &other) const
    {
        return weight > other.weight;
    }
};

// Helper function to generate all edges between points and sort by distance
vector<Edge> generateEdges(const vector<Point> &points)
{
    vector<Edge> edges;
    for (int i = 0; i < points.size(); ++i)
    {
        for (int j = i + 1; j < points.size(); ++j)
        {
            double dist = calculateDistance(points[i], points[j]);
            edges.push_back(Edge(i, j, dist));
        }
    }
    sort(edges.begin(), edges.end());
    return edges;
}
