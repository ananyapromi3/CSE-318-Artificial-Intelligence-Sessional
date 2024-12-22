#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Board
{
    int grid_dim;
    vector<vector<int>> grid;
    Board *parent_board;
    int move;

public:
    Board(int dim, vector<vector<int>> grid)
    {
        this->grid_dim = dim;
        this->grid = grid;
        this->parent_board = this;
        this->move = 0;
    }

    ~Board()
    {
        delete this->parent_board;
    }

    Board(Board &board)
    {
        this->grid_dim = board.grid_dim;
        this->grid = board.grid;
        this->parent_board = board.parent_board;
        this->move = board.move;
    }

    vector<vector<int>> getGrid()
    {
        return this->grid;
    }

    Board *getParentBoard()
    {
        return this->parent_board;
    }

    int getMove()
    {
        return this->move;
    }

    int getRow(int val)
    {
        for (int i = 0; i < grid_dim; i++)
        {
            for (int j = 0; j < grid_dim; j++)
            {
                if (grid[i][j] == val)
                {
                    return i;
                }
            }
        }
        return -1;
    }

    int getCol(int val)
    {
        for (int i = 0; i < grid_dim; i++)
        {
            for (int j = 0; j < grid_dim; j++)
            {
                if (grid[i][j] == val)
                {
                    return j;
                }
            }
        }
        return -1;
    }

    void swapPositions(int i1, int j1, int i2, int j2)
    {
        int temp = grid[i1][j1];
        grid[i1][j1] = grid[i2][j2];
        grid[i2][j2] = temp;
    }

    Board *slideDown()
    {
        int r = getRow(0);
        if (r == grid_dim - 1)
        {
            return NULL;
        }
        int c = getCol(0);
        vector<vector<int>> temp_grid;
        temp_grid = this->grid;
        int temp = temp_grid[r][c];
        temp_grid[r][c] = temp_grid[r + 1][c];
        temp_grid[r + 1][c] = temp;
        Board *child_board = new Board(grid_dim, temp_grid);
        child_board->parent_board = this;
        child_board->move = this->move + 1;
        return child_board;
    }

    Board *slideUp()
    {
        int r = getRow(0);
        if (r == 0)
        {
            return NULL;
        }
        int c = getCol(0);
        vector<vector<int>> temp_grid;
        temp_grid = this->grid;
        int temp = temp_grid[r][c];
        temp_grid[r][c] = temp_grid[r - 1][c];
        temp_grid[r - 1][c] = temp;
        Board *child_board = new Board(grid_dim, temp_grid);
        child_board->parent_board = this;
        child_board->move = this->move + 1;
        return child_board;
    }

    Board *slideRight()
    {
        int c = getCol(0);
        if (c == grid_dim - 1)
        {
            return NULL;
        }
        int r = getRow(0);
        vector<vector<int>> temp_grid;
        temp_grid = this->grid;
        int temp = temp_grid[r][c];
        temp_grid[r][c] = temp_grid[r][c + 1];
        temp_grid[r][c + 1] = temp;
        Board *child_board = new Board(grid_dim, temp_grid);
        child_board->parent_board = this;
        child_board->move = this->move + 1;
        return child_board;
    }

    Board *slideLeft()
    {
        int c = getCol(0);
        if (c == 0)
        {
            return NULL;
        }
        int r = getRow(0);
        vector<vector<int>> temp_grid;
        temp_grid = this->grid;
        int temp = temp_grid[r][c];
        temp_grid[r][c] = temp_grid[r][c - 1];
        temp_grid[r][c - 1] = temp;
        Board *child_board = new Board(grid_dim, temp_grid);
        child_board->parent_board = this;
        child_board->move = this->move + 1;
        return child_board;
    }

    int getHammingDistance(Board *target_board)
    {
        int h = 0;
        for (int i = 0; i < grid_dim; i++)
        {
            for (int j = 0; j < grid_dim; j++)
            {
                if (this->grid[i][j] != 0 && this->grid[i][j] != target_board->grid[i][j])
                {
                    h++;
                }
            }
        }
        return h;
    }

    int getManhattanDistance(Board *target_board)
    {
        int m = 0;
        for (int i = 1; i < grid_dim * grid_dim; i++)
        {
            m += abs(target_board->getCol(i) - this->getCol(i)) + abs(target_board->getRow(i) - this->getRow(i));
        }
        return m;
    }

    int getInversionCount()
    {
        int c = 0;
        for (int i = 0; i < this->grid_dim; i++)
        {
            for (int j = 0; j < this->grid_dim; j++)
            {
                if (this->grid[i][j] != 0)
                {
                    for (int l = j + 1; l < this->grid_dim; l++)
                    {
                        if (this->grid[i][l] > this->grid[i][j])
                        {
                            c++;
                        }
                    }
                    for (int k = i + 1; k < this->grid_dim; k++)
                    {
                        for (int l = 0; l < this->grid_dim; l++)
                        {
                            if (this->grid[k][l] > this->grid[i][j])
                            {
                                c++;
                            }
                        }
                    }
                }
            }
        }
        return c;
    }

    bool isSolvable()
    {
        if (this->grid_dim % 2 != 0)
        {
            if (this->getInversionCount() % 2 == 0)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            if (this->getInversionCount() % 2 == 0 && this->getRow(0) % 2 == 0)
            {
                return true;
            }
            else if (this->getInversionCount() % 2 != 0 && this->getRow(0) % 2 != 0)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }

    void printBoard()
    {
        for (int i = 0; i < grid_dim; i++)
        {
            for (int j = 0; j < grid_dim; j++)
            {
                if (grid[i][j] == 0)
                {
                    cout << '*' << " ";
                }
                else
                {
                    cout << grid[i][j] << " ";
                }
            }
            cout << "\n";
        }
        cout << "\n";
    }
};