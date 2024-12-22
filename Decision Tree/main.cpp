#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <set>
#include <iomanip>
#include "decisionTree.cpp"
#define RUNS 20
#define INFORMATION_GAIN 0
#define GINI_IMPURITY 1

using namespace std;

string filePath = "car evaluation dataset/car.data";

void printAccuracyTable(double totalAccuracyIG, double totalAccuracyIG_, double totalAccuracyGini, double totalAccuracyGini_)
{
    double avgAccuracyIG = totalAccuracyIG / RUNS * 100;
    double avgAccuracyIGRandom = totalAccuracyIG_ / RUNS * 100;
    double avgAccuracyGini = totalAccuracyGini / RUNS * 100;
    double avgAccuracyGiniRandom = totalAccuracyGini_ / RUNS * 100;
    cout << string(110, '-') << endl;
    cout << left << "Attribute selection strategy  " << setw(30) << " "
         << "Information Gain" << "\t\t"
         << "Gini Impurity"
         << endl;
    cout << string(110, '-') << endl;
    cout << left << setw(60) << "Always select the best attribute"
         << fixed << setprecision(2) << avgAccuracyIG << "%" << "\t\t\t"
         << avgAccuracyGini << "%"
         << endl;
    cout << left << setw(60) << "Select one randomly from the top three attributes"
         << avgAccuracyIGRandom << "%" << "\t\t\t"
         << avgAccuracyGiniRandom << "%"
         << endl;
    cout << string(110, '-') << endl;
}

int main()
{
    auto dataset = loadDataset(filePath);
    // cout << "Dataset size: " << dataset.size() << endl;
    vector<Data> train, test;
    double totalAccuracyIG = 0.0, totalAccuracyGini = 0.0;
    double totalAccuracyIG_ = 0.0, totalAccuracyGini_ = 0.0;
    for (int i = 0; i < RUNS; ++i)
    {
        vector<int> attributes;
        for (int i = 0; i < 6; i++)
        {
            attributes.push_back(i);
        }
        splitDataset(dataset, train, test);
        // cout << train.size() << " " << test.size() << endl;

        Node *informationGainRoot = new Node();
        buildDecisionTree(informationGainRoot, train, attributes, INFORMATION_GAIN);
        double accInfoGain = calculateAccuracy(informationGainRoot, test);
        // cout << "Accuracy using Information Gain: " << accInfoGain << endl;
        totalAccuracyIG += accInfoGain;

        Node *informationGainRoot_ = new Node();
        buildRandomDecisionTree(informationGainRoot_, train, attributes, INFORMATION_GAIN);
        double accInfoGain_ = calculateAccuracy(informationGainRoot_, test);
        totalAccuracyIG_ += accInfoGain_;

        Node *giniRoot = new Node();
        buildDecisionTree(giniRoot, train, attributes, GINI_IMPURITY);
        double accGini = calculateAccuracy(giniRoot, test);
        // cout << "Accuracy using Gini Impurity: " << accGini << endl;
        totalAccuracyGini += accGini;

        Node *giniRoot_ = new Node();
        buildRandomDecisionTree(giniRoot_, train, attributes, GINI_IMPURITY);
        double accGini_ = calculateAccuracy(giniRoot_, test);
        totalAccuracyGini_ += accGini_;
    }
    // totalAccuracyIG += accInfoGain;
    // for (int i = 0; i < RUNS; ++i)
    // {
    //     vector<int> attributes;
    //     for (int i = 0; i < 6; i++)
    //     {
    //         attributes.push_back(i);
    //     }
    //     splitDataset(dataset, train, test);

    //     Node *informationGainRoot_ = new Node();
    //     buildDecisionTree(informationGainRoot_, train, attributes, INFORMATION_GAIN);
    //     accInfoGain_ = calculateAccuracy(informationGainRoot_, test);
    //     totalAccuracyIG_ += accInfoGain_;
    // }
    // totalAccuracyIG += accInfoGain;
    // for (int i = 0; i < RUNS; ++i)
    // {
    //     vector<int> attributes;
    //     for (int i = 0; i < 6; i++)
    //     {
    //         attributes.push_back(i);
    //     }
    //     splitDataset(dataset, train, test);

    //     Node *giniRoot = new Node();
    //     buildDecisionTree(giniRoot, train, attributes, GINI_IMPURITY);
    //     accGini = calculateAccuracy(giniRoot, test);
    //     // cout << "Accuracy using Gini Impurity: " << accGini << endl;
    //     totalAccuracyGini += accGini;
    // }
    // totalAccuracyGini += accGini;
    // for (int i = 0; i < RUNS; ++i)
    // {
    //     vector<int> attributes;
    //     for (int i = 0; i < 6; i++)
    //     {
    //         attributes.push_back(i);
    //     }
    //     splitDataset(dataset, train, test);

    //     Node *giniRoot_ = new Node();
    //     buildDecisionTree(giniRoot_, train, attributes, GINI_IMPURITY);
    //     accGini_ = calculateAccuracy(giniRoot_, test);
    //     // cout << "Accuracy using Gini Impurity: " << accGini << endl;
    //     totalAccuracyGini_ += accGini_;
    // }
    // cout << "Accuracy using Gini Impurity: " << accGini << endl;
    // totalAccuracyGini += accGini;
    // cout << "Accuracy using Information Gain: " << totalAccuracyIG / RUNS << endl;
    // cout << "Average accuracy using Information Gain (random): " << totalAccuracyIG_ / RUNS << endl;

    // cout << "Average accuracy using Information Gain: " << totalAccuracyIG / RUNS * 100 << "%" << endl;
    // cout << "Average accuracy using Information Gain (random): " << totalAccuracyIG_ / RUNS * 100 << "%" << endl;
    // cout << "Average accuracy using Gini Impurity: " << totalAccuracyGini / RUNS * 100 << "%" << endl;
    // cout << "Average accuracy using Gini Impurity (random): " << totalAccuracyGini_ / RUNS * 100 << "%" << endl;

    printAccuracyTable(totalAccuracyIG, totalAccuracyIG_, totalAccuracyGini, totalAccuracyGini_);
    return 0;
}
