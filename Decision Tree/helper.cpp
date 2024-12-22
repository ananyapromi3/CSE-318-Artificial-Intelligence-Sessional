#include <cmath>
#include <map>
#include <set>
#include "load_data.cpp"
#include "attributes.h"

using namespace std;

double entropy(const vector<Data> &data);
double giniImpurity(const vector<Data> &data);
double informationGain(const vector<Data> &data, int attribute);
double giniGain(const vector<Data> &data, int attribute);
vector<Data> filterData(const vector<Data> &data, int attribute, const string &value);

double entropy(const vector<Data> &data)
{
    map<string, int> labelCounts;
    for (const auto &row : data)
    {
        labelCounts[row.label]++;
    }
    double result = 0.0;
    for (const auto &pair : labelCounts)
    {
        double p = static_cast<double>(pair.second) / data.size();
        result -= p * log2(p);
    }
    return result;
}

double giniImpurity(const vector<Data> &data)
{
    map<string, int> labelCounts;
    for (const auto &row : data)
    {
        labelCounts[row.label]++;
    }
    double result = 1.0;
    for (const auto &pair : labelCounts)
    {
        double p = pair.second * 1.0 / data.size();
        result -= p * p;
    }
    return result;
}

double informationGain(const vector<Data> &data, int attribute)
{
    double originalEntropy = entropy(data);
    vector<string> values = uniqueValues(attribute);
    double weightedEntropy = 0.0;

    for (const auto &value : values)
    {
        vector<Data> subset = filterData(data, attribute, value);
        if (subset.empty())
        {
            continue;
        }
        weightedEntropy += ((subset.size() * 1.0) / data.size()) * entropy(subset);
    }
    return originalEntropy - weightedEntropy;
}

double giniGain(const vector<Data> &data, int attribute)
{
    double originalGini = 1.0;
    vector<string> values = uniqueValues(attribute);
    double weightedGini = 0.0;
    for (const auto &value : values)
    {
        vector<Data> subset = filterData(data, attribute, value);
        if (subset.empty())
        {
            continue;
        }
        weightedGini += ((subset.size() * 1.0) / data.size()) * giniImpurity(subset);
    }
    return originalGini - weightedGini;
}

vector<Data> filterData(const vector<Data> &data, int attribute, const string &value)
{
    vector<Data> filtered;
    // filtered.reserve(data.size());
    for (const auto &row : data)
    {
        if ((attribute == BUYING && row.buying == value) ||
            (attribute == MAINT && row.maint == value) ||
            (attribute == DOORS && row.doors == value) ||
            (attribute == PERSONS && row.persons == value) ||
            (attribute == LUG_BOOT && row.lug_boot == value) ||
            (attribute == SAFETY && row.safety == value))
        {
            filtered.push_back(row);
        }
    }

    return filtered;
}
