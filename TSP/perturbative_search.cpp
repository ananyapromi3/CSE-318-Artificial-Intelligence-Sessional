#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include "constructive_search.cpp"
using namespace std;

// 2-opt function
vector<int> twoOpt(const vector<Point> &points, vector<int> tour);
// Node Shift heuristic function
vector<int> nodeShift(const vector<Point> &points, vector<int> tour);
// Node Swap heuristic function
vector<int> nodeSwap(const vector<Point> &points, vector<int> tour);

// 2-opt function
vector<int> twoOpt(const vector<Point> &points, vector<int> tour)
{
    double bestDist = calculateTourDistance(points, tour);
    bool improvement = true;
    while (improvement)
    {
        improvement = false;
        for (int i = 1; i < tour.size() - 2; i++)
        {
            for (int j = i + 1; j < tour.size() - 1; j++)
            {
                if (j == i + 1)
                {
                    continue;
                }
                vector<int> newTour = tour;
                reverse(newTour.begin() + i, newTour.begin() + j + 1);
                double newDist = calculateTourDistance(points, newTour);
                if (newDist < bestDist)
                {
                    tour = newTour;
                    bestDist = newDist;
                    improvement = true;
                }
            }
        }
    }
    return tour;
}

// Node Shift heuristic function
vector<int> nodeShift(const vector<Point> &points, vector<int> tour)
{
    double bestDist = calculateTourDistance(points, tour);
    bool improvement = true;
    while (improvement)
    {
        improvement = false;
        for (int i = 0; i < tour.size(); ++i)
        {
            for (int j = 0; j < tour.size(); ++j)
            {
                if (i == j)
                {
                    continue;
                }
                vector<int> newTour = tour;
                int node = newTour[i];
                newTour.erase(newTour.begin() + i);
                newTour.insert(newTour.begin() + j, node);
                double newDist = calculateTourDistance(points, newTour);
                if (newDist < bestDist)
                {
                    bestDist = newDist;
                    tour = newTour;
                    improvement = true;
                }
            }
        }
    }
    return tour;
}

// Node Swap heuristic function
vector<int> nodeSwap(const vector<Point> &points, vector<int> tour)
{
    double bestDist = calculateTourDistance(points, tour);
    bool improvement = true;
    while (improvement)
    {
        improvement = false;
        for (int i = 0; i < tour.size(); ++i)
        {
            for (int j = i + 1; j < tour.size(); ++j)
            {
                vector<int> newTour = tour;
                swap(newTour[i], newTour[j]);
                double newDist = calculateTourDistance(points, newTour);
                if (newDist < bestDist)
                {
                    bestDist = newDist;
                    tour = newTour;
                    improvement = true;
                }
            }
        }
    }
    return tour;
}