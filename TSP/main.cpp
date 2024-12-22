#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include <filesystem>
#include "perturbative_search.cpp"
#define PRINT_TOUR 0
using namespace std;
namespace fs = filesystem;
const int p = 3;
const int c = 4;
double tourCosts[p][c];

// Function to parse the .tsp file
vector<Point> parseTSPFile(const string &filename)
{
    vector<Point> points;
    ifstream file(filename);
    string line;
    bool inNodeSection = false;

    while (getline(file, line))
    {
        if (line == "NODE_COORD_SECTION")
        {
            inNodeSection = true;
            continue;
        }
        if (line == "EOF")
        {
            break;
        }
        if (inNodeSection)
        {
            istringstream iss(line);
            int id;
            double x, y;
            iss >> id >> x >> y;
            points.push_back(Point(id, x, y));
        }
    }
    return points;
}

// Function to run and print results for each heuristic combination
void runHeuristics(const vector<Point> &points, const string &datasetName)
{
    int temp;

    // Display results
    cout << "------------------------------------------------------" << endl;
    cout << "Dataset: " << datasetName << endl;
    cout << "------------------------------------------------------" << endl;
    cout << endl;

    // Constructive Heuristics
    // Nearest Neighbour
    vector<int> nnTour = nearestNeighbourHeuristic(points);
    cout << "Nearest Neighbour Tour Cost: " << calculateTourDistance(points, nnTour) << endl;
    if (PRINT_TOUR)
    {
        cout << "Nearest Neighbour Tour: ";
        printTour(nnTour);
    }
    // Nearest Insertion
    vector<int> niTour = nearestInsertionHeuristic(points);
    cout << "Nearest Insertion Tour Cost: " << calculateTourDistance(points, niTour) << endl;
    if (PRINT_TOUR)
    {
        cout << "Nearest Insertion Tour: ";
        printTour(niTour);
    }
    // Greedy
    vector<int> greedyTour = greedyHeuristic(points);
    cout << "Greedy Tour Cost: " << calculateTourDistance(points, greedyTour) << endl;
    if (PRINT_TOUR)
    {
        cout << "Greedy Tour: ";
        printTour(greedyTour);
    }
    // MST
    vector<int> mstTour = mstHeuristic(points);
    cout << "MST Tour Cost: " << calculateTourDistance(points, mstTour) << endl;
    if (PRINT_TOUR)
    {
        cout << "MST Tour: ";
        printTour(mstTour);
    }
    cout << endl;

    // Perturbative Heuristics
    // 2-Opt
    vector<int> twoOptTour = twoOpt(points, nnTour);
    temp = calculateTourDistance(points, twoOptTour);
    cout << "Two-Opt Tour Cost (from NN): " << temp << endl;
    tourCosts[0][0] += temp;
    if (PRINT_TOUR)
    {
        cout << "Two-Opt Tour: ";
        printTour(twoOptTour);
    }
    vector<int> twoOptTour2 = twoOpt(points, niTour);
    temp = calculateTourDistance(points, twoOptTour2);
    cout << "Two-Opt Tour Cost (from NI): " << temp << endl;
    tourCosts[0][1] += temp;
    if (PRINT_TOUR)
    {
        cout << "Two-Opt Tour: ";
        printTour(twoOptTour2);
    }
    vector<int> twoOptTour3 = twoOpt(points, greedyTour);
    temp = calculateTourDistance(points, twoOptTour3);
    cout << "Two-Opt Tour Cost (from Greedy): " << temp << endl;
    tourCosts[0][2] += temp;
    if (PRINT_TOUR)
    {
        cout << "Two-Opt Tour: ";
        printTour(twoOptTour3);
    }
    vector<int> twoOptTour4 = twoOpt(points, mstTour);
    temp = calculateTourDistance(points, twoOptTour4);
    cout << "Two-Opt Tour Cost (from MST): " << temp << endl;
    tourCosts[0][3] += temp;
    if (PRINT_TOUR)
    {
        cout << "Two-Opt Tour: ";
        printTour(twoOptTour4);
    }
    cout << endl;
    // Node Shift
    vector<int> nodeShiftTour = nodeShift(points, nnTour);
    temp = calculateTourDistance(points, nodeShiftTour);
    cout << "Node Shift Tour Cost (from NN): " << temp << endl;
    tourCosts[1][0] += temp;
    if (PRINT_TOUR)
    {
        cout << "Node Shift Tour: ";
        printTour(nodeShiftTour);
    }
    vector<int> nodeShiftTour2 = nodeShift(points, niTour);
    temp = calculateTourDistance(points, nodeShiftTour2);
    cout << "Node Shift Tour Cost (from NI): " << temp << endl;
    tourCosts[1][1] += temp;
    if (PRINT_TOUR)
    {
        cout << "Node Shift Tour: ";
        printTour(nodeShiftTour2);
    }
    vector<int> nodeShiftTour3 = nodeShift(points, greedyTour);
    temp = calculateTourDistance(points, nodeShiftTour3);
    cout << "Node Shift Tour Cost (from Greedy): " << temp << endl;
    tourCosts[1][2] += temp;
    if (PRINT_TOUR)
    {
        cout << "Node Shift Tour: ";
        printTour(nodeShiftTour3);
    }
    vector<int> nodeShiftTour4 = nodeShift(points, mstTour);
    temp = calculateTourDistance(points, nodeShiftTour4);
    cout << "Node Shift Tour Cost (from MST): " << temp << endl;
    tourCosts[1][3] += temp;
    if (PRINT_TOUR)
    {
        cout << "Node Shift Tour: ";
        printTour(nodeShiftTour4);
    }
    cout << endl;
    // Node Swap
    vector<int> nodeSwapTour = nodeSwap(points, nnTour);
    temp = calculateTourDistance(points, nodeSwapTour);
    cout << "Node Swap Tour Cost (from NN): " << temp << endl;
    tourCosts[2][0] += temp;
    if (PRINT_TOUR)
    {
        cout << "Node Swap Tour: ";
        printTour(nodeSwapTour);
    }
    vector<int> nodeSwapTour2 = nodeSwap(points, niTour);
    temp = calculateTourDistance(points, nodeSwapTour2);
    cout << "Node Swap Tour Cost (from NI): " << temp << endl;
    tourCosts[2][1] += temp;
    if (PRINT_TOUR)
    {
        cout << "Node Swap Tour: ";
        printTour(nodeSwapTour2);
    }
    vector<int> nodeSwapTour3 = nodeSwap(points, greedyTour);
    temp = calculateTourDistance(points, nodeSwapTour3);
    cout << "Node Swap Tour Cost (from Greedy): " << temp << endl;
    tourCosts[2][2] += temp;
    if (PRINT_TOUR)
    {
        cout << "Node Swap Tour: ";
        printTour(nodeSwapTour3);
    }
    vector<int> nodeSwapTour4 = nodeSwap(points, mstTour);
    temp = calculateTourDistance(points, nodeSwapTour4);
    cout << "Node Swap Tour Cost (from MST): " << temp << endl;
    tourCosts[2][3] += temp;
    if (PRINT_TOUR)
    {
        cout << "Node Swap Tour: ";
        printTour(nodeSwapTour4);
    }
    cout << endl;

    cout << endl;
}

int main()
{
    freopen("output.txt", "w", stdout);
    string folderPath = "./TSP_assignment_task_benchmark_data/"; // Folder containing 21 .tsp files
    // Iterate over each .tsp file in the directory
    int c = 0;
    for (const auto &entry : fs::directory_iterator(folderPath))
    {
        if (entry.path().extension() == ".tsp")
        {
            c++;
            string filename = entry.path().string();
            vector<Point> points = parseTSPFile(filename);
            runHeuristics(points, entry.path().filename().string());
        }
    }
    double count = c * 1.0;
    cout << endl;
    cout << "------------------------------------------------------" << endl;
    cout << "Total number of .tsp files processed: " << count << endl;
    cout << "------------------------------------------------------" << endl;
    cout << "Average Tour Costs: " << endl;
    cout << "Two Opt: " << endl;
    cout << "Average Two-Opt Tour Cost (from NN): " << tourCosts[0][0] / count << endl;
    cout << "Average Two-Opt Tour Cost (from NI): " << tourCosts[0][1] / count << endl;
    cout << "Average Two-Opt Tour Cost (from Greedy): " << tourCosts[0][2] / count << endl;
    cout << "Average Two-Opt Tour Cost (from MST): " << tourCosts[0][3] / count << endl;
    cout << "Node Shift: " << endl;
    cout << "Average Node Shift Tour Cost (from NN): " << tourCosts[1][0] / count << endl;
    cout << "Average Node Shift Tour Cost (from NI): " << tourCosts[1][1] / count << endl;
    cout << "Average Node Shift Tour Cost (from Greedy): " << tourCosts[1][2] / count << endl;
    cout << "Average Node Shift Tour Cost (from MST): " << tourCosts[1][3] / count << endl;
    cout << "Node Swap: " << endl;
    cout << "Average Node Swap Tour Cost (from NN): " << tourCosts[2][0] / count << endl;
    cout << "Average Node Swap Tour Cost (from NI): " << tourCosts[2][1] / count << endl;
    cout << "Average Node Swap Tour Cost (from Greedy): " << tourCosts[2][2] / count << endl;
    cout << "Average Node Swap Tour Cost (from MST): " << tourCosts[2][3] / count << endl;
    cout << "------------------------------------------------------" << endl;
    // string filename = "./TSP_assignment_task_benchmark_data/lin105.tsp";
    // vector<Point> points = parseTSPFile(filename);
    // runHeuristics(points, filename);
    return 0;
}
