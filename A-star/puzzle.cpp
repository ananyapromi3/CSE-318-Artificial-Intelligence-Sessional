#include <iostream>
#include "board.cpp"
#include <queue>
#include <vector>
#include <functional>
#include <set>

using namespace std;

class Puzzle
{
    Board *initial_board;
    Board *target_board;
    int priority_func; // 1 = Hamming distance, 2 = Manhattan distance
    int cost;

public:
    Puzzle(Board *initial_board, Board *target_board)
    {
        this->initial_board = initial_board;
        this->target_board = target_board;
        this->priority_func = 2;
    }

    ~Puzzle()
    {
        delete initial_board;
        delete target_board;
    }

    void setPriorityFunc(int func)
    {
        this->priority_func = func;
    }

    int heuristic(Board *board)
    {
        if (priority_func == 1)
        {
            return board->getHammingDistance(target_board);
        }
        else if (priority_func == 2)
        {
            return board->getManhattanDistance(target_board);
        }
        else
        {
            return -1;
        }
    }

    void solvePuzzle()
    {
        if (initial_board->isSolvable())
        {
            priority_queue<pair<int, Board *>, vector<pair<int, Board *>>, greater<pair<int, Board *>>> q;
            set<vector<vector<int>>> explored;
            q.push(make_pair(heuristic(initial_board) + initial_board->getMove(), initial_board));
            explored.insert(initial_board->getGrid());
            int explored_node = 1;
            int expanded_node = 0;
            while (!q.empty())
            {
                Board *parent = q.top().second;
                q.pop();
                expanded_node++;
                if (heuristic(parent) == 0)
                {
                    this->cost = parent->getMove();
                    cout << "Optimal cost to reach the goal state: " << this->cost << "\n\n";
                    this->printPuzzleBoards(parent);
                    cout << "Number of explored nodes: " << explored_node << "\n";
                    cout << "Number of expanded nodes: " << expanded_node << "\n\n";
                    return;
                }
                Board *child;
                child = parent->slideLeft();
                if (child)
                {
                    if (explored.find(child->getGrid()) == explored.end())
                    {
                        q.push(make_pair(heuristic(child) + child->getMove(), child));
                        explored.insert(child->getGrid());
                        explored_node++;
                    }
                }
                child = parent->slideRight();
                if (child)
                {
                    if (explored.find(child->getGrid()) == explored.end())
                    {
                        q.push(make_pair(heuristic(child) + child->getMove(), child));
                        explored.insert(child->getGrid());
                        explored_node++;
                    }
                }
                child = parent->slideUp();
                if (child)
                {
                    if (explored.find(child->getGrid()) == explored.end())
                    {
                        q.push(make_pair(heuristic(child) + child->getMove(), child));
                        explored.insert(child->getGrid());
                        explored_node++;
                    }
                }
                child = parent->slideDown();
                if (child)
                {
                    if (explored.find(child->getGrid()) == explored.end())
                    {
                        q.push(make_pair(heuristic(child) + child->getMove(), child));
                        explored.insert(child->getGrid());
                        explored_node++;
                    }
                }
            }
        }
        else
        {
            cout << "Unsolvable puzzle\n";
        }
    }

    void printPuzzleBoards(Board *board)
    {
        if (board->getParentBoard() == board)
        {
            board->printBoard();
            return;
        }
        printPuzzleBoards(board->getParentBoard());
        board->printBoard();
    }
};