#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

class Point
{
private:
    int id;
    double x;
    double y;

public:
    // Constructor
    Point(int id, double x, double y) 
    {
        this->id = id;
        this->x = x;
        this->y = y;
    }

    // Getters
    int getId() const { return id; }
    double getX() const { return x; }
    double getY() const { return y; }
};

// Distance calculation between two points
double calculateDistance(const Point &p1, const Point &p2)
{
    double xDiff = p1.getX() - p2.getX();
    double yDiff = p1.getY() - p2.getY();
    return sqrt(xDiff * xDiff + yDiff * yDiff);
}

// Function to calculate the total distance of a tour
double calculateTourDistance(const vector<Point> &points, const vector<int> &tour)
{
    double totalDistance = 0.0;
    for (int i = 0; i < tour.size() - 1; ++i)
    {
        totalDistance += calculateDistance(points[tour[i]], points[tour[i + 1]]);
    }
    totalDistance += calculateDistance(points[tour[tour.size() - 1]], points[tour[0]]); // Return to the starting point
    return totalDistance;
}