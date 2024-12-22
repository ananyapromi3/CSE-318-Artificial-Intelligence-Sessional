#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <map>
#include <set>
#include <algorithm>
#include <random>
#include "helper.cpp"

using namespace std;

class Node
{
public:
    int attribute;
    map<string, Node *> children;
    Node *parent;
    string label;
    bool isLeaf;

    Node()
    {
        attribute = 0;
        parent = nullptr;
        isLeaf = false;
    }
};

void buildDecisionTree(Node *node, const vector<Data> &data, vector<int> &attributes, int flag);
void buildRandomDecisionTree(Node *node, const vector<Data> &data, vector<int> &attributes, int flag);
string classify(Node *tree, const Data &row);
double calculateAccuracy(Node *tree, const vector<Data> &test);
void deleteTree(Node *root);
// void printTree(Node *node, string prefix);

void buildDecisionTree(Node *node, const vector<Data> &data, vector<int> &attributes_, int flag)
{
    vector<int> attributes = attributes_;
    if (data.empty())
    {
        return;
    }
    if (node == nullptr)
    {
        return;
    }
    // map<string, int> labelCounts;
    // for (auto row : data)
    // {
    //     labelCounts[row.label]++;
    // }
    // string mostCommonLabel = data[0].label;
    // int maxCount = 0;
    // for (auto pair : labelCounts)
    // {
    //     if (pair.second > maxCount)
    //     {
    //         maxCount = pair.second;
    //         mostCommonLabel = pair.first;
    //     }
    // }
    // node->label = mostCommonLabel;

    // Check if all labels are the same
    bool allSame = true;
    for (int i = 1; i < data.size(); i++)
    {
        if (data[i].label != data[0].label)
        {
            allSame = false;
            break;
        }
    }
    if (allSame)
    {
        node->isLeaf = true;
        node->label = data[0].label;
        return;
    }
    if (attributes.empty())
    {
        node->isLeaf = true;
        map<string, int> labelCounts;
        for (auto row : data)
        {
            labelCounts[row.label]++;
        }
        string mostCommonLabel = data[0].label;
        int maxCount = 0;
        for (auto pair : labelCounts)
        {
            if (pair.second > maxCount)
            {
                maxCount = pair.second;
                mostCommonLabel = pair.first;
            }
        }
        node->label = mostCommonLabel;
        return;
    }
    int bestAttribute = 0;
    double bestScore = 0.0;
    for (const auto &attribute : attributes)
    {
        double score = 0.0;
        if (flag == 0)
        {
            score = informationGain(data, attribute);
            // cout << "IG Score: " << score << " Gini Score: " << giniGain(data, attribute) << endl;
        }
        else
        {
            score = giniGain(data, attribute);
        }
        if (score > bestScore)
        {
            bestScore = score;
            bestAttribute = attribute;
        }
    }
    node->attribute = bestAttribute;
    node->isLeaf = false;
    attributes.erase(find(attributes.begin(), attributes.end(), bestAttribute));
    vector<string> values = uniqueValues(bestAttribute);
    for (auto value : values)
    {
        vector<Data> subset = filterData(data, bestAttribute, value);
        if (subset.empty())
        {
            Node *leaf = new Node();
            leaf->isLeaf = true;
            map<string, int> labelCounts;
            for (auto row : data)
            {
                labelCounts[row.label]++;
            }
            string mostCommonLabel = labelCounts.begin()->first;
            int maxCount = 0;
            for (auto pair : labelCounts)
            {
                if (pair.second > maxCount)
                {
                    maxCount = pair.second;
                    mostCommonLabel = pair.first;
                }
                leaf->label = mostCommonLabel;
            }
            // leaf->label = node->label;
            node->children[value] = leaf;
        }
        else
        {
            node->children[value] = new Node();
            node->children[value]->parent = node;
            buildDecisionTree(node->children[value], subset, attributes, flag);
        }
    }
}
void buildRandomDecisionTree(Node *node, const vector<Data> &data, vector<int> &attributes_, int flag)
{
    vector<int> attributes = attributes_;
    if (data.empty())
    {
        return;
    }
    if (node == nullptr)
    {
        return;
    }
    // map<string, int> labelCounts;
    // for (auto row : data)
    // {
    //     labelCounts[row.label]++;
    // }
    // string mostCommonLabel = data[0].label;
    // int maxCount = 0;
    // for (auto pair : labelCounts)
    // {
    //     if (pair.second > maxCount)
    //     {
    //         maxCount = pair.second;
    //         mostCommonLabel = pair.first;
    //     }
    // }
    // node->label = mostCommonLabel;

    // Check if all labels are the same
    bool allSame = true;
    for (int i = 1; i < data.size(); i++)
    {
        if (data[i].label != data[0].label)
        {
            allSame = false;
            break;
        }
    }
    if (allSame)
    {
        node->isLeaf = true;
        node->label = data[0].label;
        return;
    }
    if (attributes.empty())
    {
        node->isLeaf = true;
        map<string, int> labelCounts;
        for (auto row : data)
        {
            labelCounts[row.label]++;
        }
        string mostCommonLabel = data[0].label;
        int maxCount = 0;
        for (auto pair : labelCounts)
        {
            if (pair.second > maxCount)
            {
                maxCount = pair.second;
                mostCommonLabel = pair.first;
            }
        }
        node->label = mostCommonLabel;
        return;
    }
    int bestAttribute = 0;
    // double bestScore = 0;
    vector<pair<double, int>> scores;
    for (const auto &attribute : attributes)
    {
        double score = 0.0;
        if (flag == 0)
        {
            score = informationGain(data, attribute);
            // cout << "IG Score: " << score << " Gini Score: " << giniGain(data, attribute) << endl;
        }
        else
        {
            score = giniGain(data, attribute);
        }
        scores.push_back(make_pair(score, attribute));
        // if (score > bestScore)
        // {
        //     bestScore = score;
        //     bestAttribute = attribute;
        // }
    }
    sort(scores.begin(), scores.end());
    // cout << "Best Score: " << scores[scores.size() - 1].first << endl;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, min(2, (int)scores.size() - 1));
    int randomNumber = dist(gen);
    bestAttribute = scores[randomNumber].second;
    node->attribute = bestAttribute;
    node->isLeaf = false;
    attributes.erase(find(attributes.begin(), attributes.end(), bestAttribute));
    // cout << "Finding..." << endl;
    // auto it = find(attributes.begin(), attributes.end(), bestAttribute);
    // cout << *it << endl;
    // if (it != attributes.end())
    // {
    //     attributes.erase(it);
    // cout << "Erased..." << endl;
    // }
    vector<string> values = uniqueValues(bestAttribute);
    for (auto value : values)
    {
        vector<Data> subset = filterData(data, bestAttribute, value);
        if (subset.empty())
        {
            Node *leaf = new Node();
            leaf->isLeaf = true;
            map<string, int> labelCounts;
            for (auto row : data)
            {
                labelCounts[row.label]++;
            }
            string mostCommonLabel = labelCounts.begin()->first;
            int maxCount = 0;
            for (auto pair : labelCounts)
            {
                if (pair.second > maxCount)
                {
                    maxCount = pair.second;
                    mostCommonLabel = pair.first;
                }
                leaf->label = mostCommonLabel;
            }
            // leaf->label = node->label;
            node->children[value] = leaf;
        }
        else
        {
            node->children[value] = new Node();
            node->children[value]->parent = node;
            buildDecisionTree(node->children[value], subset, attributes, flag);
        }
    }
}

string classify(Node *tree, const Data &row)
{
    // cout << "Classifying..." << endl;
    if (!tree)
    {
        return "";
    }
    if (tree->isLeaf)
    {
        // cout << "Leaf: " << tree->label << endl;
        return tree->label;
    }
    string value;
    if (tree->attribute == BUYING)
    {
        value = row.buying;
    }
    else if (tree->attribute == MAINT)
    {
        value = row.maint;
    }
    else if (tree->attribute == DOORS)
    {
        value = row.doors;
    }
    else if (tree->attribute == PERSONS)
    {
        value = row.persons;
    }
    else if (tree->attribute == LUG_BOOT)
    {
        value = row.lug_boot;
    }
    else if (tree->attribute == SAFETY)
    {
        value = row.safety;
    }
    // cout << "Value: " << value << endl;
    return classify(tree->children[value], row);
}

double calculateAccuracy(Node *tree, const vector<Data> &test)
{
    // cout << "Calculating accuracy..." << endl;
    int correct = 0;
    for (const auto &row : test)
    {
        string label = classify(tree, row);
        if (label == row.label)
        {
            correct++;
        }
        // else
        // {
        //     cout << "Incorrect: " << row.label << " " << label << endl;
        // }
    }
    // cout << "Correct: " << correct << " out of " << test.size() << endl;
    double accuracy = (correct * 1.0) / test.size();
    // cout << "Accuracy: " << accuracy << endl;
    return accuracy;
}

void deleteTree(Node *root)
{
    if (!root)
    {
        return;
    }
    for (auto &child : root->children)
    {
        deleteTree(child.second);
    }
    delete root;
}
