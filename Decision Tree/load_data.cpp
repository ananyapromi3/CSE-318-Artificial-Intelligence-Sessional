#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <random>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

vector<string> uniqueValues(int attribute);

class Data
{
public:
    string buying, maint, doors, persons, lug_boot, safety, label;
    Data()
    {
        buying = maint = doors = persons = lug_boot = safety = label = "";
    }
};

vector<Data> loadDataset(const string &filePath)
{
    ifstream file(filePath);
    vector<Data> dataset;
    string line;

    while (getline(file, line))
    {
        stringstream ss(line);
        string value;
        Data row = Data();
        getline(ss, row.buying, ',');
        getline(ss, row.maint, ',');
        getline(ss, row.doors, ',');
        getline(ss, row.persons, ',');
        getline(ss, row.lug_boot, ',');
        getline(ss, row.safety, ',');
        getline(ss, row.label, ',');
        dataset.push_back(row);
    }
    file.close();
    return dataset;
}

void splitDataset(const vector<Data> &dataset, vector<Data> &train, vector<Data> &test, double trainRatio = 0.8)
{
    auto shuffled = dataset;
    random_device rd;
    mt19937 g(rd());
    shuffle(shuffled.begin(), shuffled.end(), g);
    int trainSize = static_cast<int>(trainRatio * shuffled.size());
    train.assign(shuffled.begin(), shuffled.begin() + trainSize);
    test.assign(shuffled.begin() + trainSize, shuffled.end());
}

// vector<string> uniqueValues(int attribute)
// {
//     vector<set<string> > allVallues;
//     set<string> values0, values1, values2, values3, values4, values5;
//     values0.insert("vhigh");
//     values0.insert("high");
//     values0.insert("med");
//     values0.insert("low");
//     allVallues.push_back(values0);

//     values1.insert("vhigh");
//     values1.insert("high");
//     values1.insert("med");
//     values1.insert("low");
//     allVallues.push_back(values1);

//     values2.insert("2");
//     values2.insert("3");
//     values2.insert("4");
//     values2.insert("5more");
//     allVallues.push_back(values2);

//     values3.insert("2");
//     values3.insert("4");
//     values3.insert("more");
//     allVallues.push_back(values3);

//     values4.insert("small");
//     values4.insert("med");
//     values4.insert("big");
//     allVallues.push_back(values4);

//     values5.insert("low");
//     values5.insert("med");
//     values5.insert("high");
//     allVallues.push_back(values5);

//     return vector<string>(allVallues[attribute].begin(), allVallues[attribute].end());
// }

const vector<set<string>> allValues = vector<set<string>>{
    {"vhigh", "high", "med", "low"}, // Attribute 0: buying
    {"vhigh", "high", "med", "low"}, // Attribute 1: maint
    {"2", "3", "4", "5more"},        // Attribute 2: doors
    {"2", "4", "more"},              // Attribute 3: persons
    {"small", "med", "big"},         // Attribute 4: lug_boot
    {"low", "med", "high"}           // Attribute 5: safety
};

vector<string> uniqueValues(int attribute)
{
    if (attribute < 0 || attribute >= allValues.size())
    {
        return vector<string>();
    }
    return vector<string>(allValues[attribute].begin(), allValues[attribute].end());
}