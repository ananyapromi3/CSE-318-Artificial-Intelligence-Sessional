#include <iostream>
#include <vector>
#include "puzzle.cpp"

using namespace std;

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int k;
    cin >> k;
    vector<vector<int>> input_grid(k, vector<int>(k, 0)), target_grid(k, vector<int>(k, 0));
    string temp;
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            cin >> temp;
            if (temp == "*")
            {
                input_grid[i][j] = 0; 
            }
            else
            {
                input_grid[i][j] = stoi(temp); 
            }
        }
    }
    int c = 1;
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            target_grid[i][j] = c++;
        }
    }
    target_grid[k - 1][k - 1] = 0;

    Board *initial_board = new Board(k, input_grid);
    Board *target_board = new Board(k, target_grid);

    Puzzle *puzzle1 = new Puzzle(initial_board, target_board);
    puzzle1->setPriorityFunc(1);
    puzzle1->solvePuzzle();

    Puzzle *puzzle2 = new Puzzle(initial_board, target_board);
    puzzle2->setPriorityFunc(2);
    puzzle2->solvePuzzle();

    return 0;
}