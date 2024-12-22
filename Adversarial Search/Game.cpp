#include <iostream>
#include "heuristic.cpp"
using namespace std;

class Game
{
    int player1_heuristic;
    int player2_heuristic;
    int player1_w1, player1_w2, player1_w3, player1_w4;
    int player2_w1, player2_w2, player2_w3, player2_w4;
    int player1_depth_limit;
    int player2_depth_limit;
    int step;

public:
    Game()
    {
        this->player1_heuristic = 1;
        this->player2_heuristic = 1;
        this->player1_w1 = 1;
        this->player1_w2 = 1;
        this->player1_w3 = 1;
        this->player1_w4 = 1;
        this->player2_w1 = 1;
        this->player2_w2 = 1;
        this->player2_w3 = 1;
        this->player2_w4 = 1;
        this->player1_depth_limit = rand() % (7) + 1;
        this->player2_depth_limit = rand() % (7) + 1;
        step = 0;
    }

    ~Game()
    {
    }

    void setPlayer1Heuristic(int heuristic)
    {
        this->player1_heuristic = heuristic;
    }

    void setPlayer2Heuristic(int heuristic)
    {
        this->player2_heuristic = heuristic;
    }

    void setPlayer1Weights(vector<int> w)
    {
        this->player1_w1 = w[0];
        this->player1_w2 = w[1];
        this->player1_w3 = w[2];
        this->player1_w4 = w[3];
    }

    void setPlayer2Weights(vector<int> w)
    {
        this->player2_w1 = w[0];
        this->player2_w2 = w[1];
        this->player2_w3 = w[2];
        this->player2_w4 = w[3];
    }

    void setPlayer1Depth(int depth)
    {
        this->player1_depth_limit = depth;
    }

    void setPlayer2Depth(int depth)
    {
        this->player2_depth_limit = depth;
    }

    int getStep()
    {
        return step;
    }

    int evaluateBoard(MancalaBoard *board)
    {
        if (board->isPlayer1Turn())
        {
            if (player1_heuristic == 1)
            {
                return heuristic1(board);
            }
            else if (player1_heuristic == 2)
            {
                return heuristic2(board, player1_w1, player1_w2);
            }
            else if (player1_heuristic == 3)
            {
                return heuristic3(board, player1_w1, player1_w2, player1_w3);
            }
            else if (player1_heuristic == 4)
            {
                return heuristic4(board, player1_w1, player1_w2, player1_w3, player1_w4);
            }
        }
        else
        {
            if (player2_heuristic == 1)
            {
                return heuristic1(board);
            }
            else if (player2_heuristic == 2)
            {
                return heuristic2(board, player2_w1, player2_w2);
            }
            else if (player2_heuristic == 3)
            {
                return heuristic3(board, player2_w1, player2_w2, player2_w3);
            }
            else if (player2_heuristic == 4)
            {
                return heuristic4(board, player2_w1, player2_w2, player2_w3, player2_w4);
            }
        }
        return -1;
    }

    int getDepthLimit(MancalaBoard *board)
    {
        if (board->isPlayer1Turn())
        {
            return player1_depth_limit;
        }
        else
        {
            return player2_depth_limit;
        }
    }

    int minimax(MancalaBoard *board, int depth, int a, int b)
    {
        if (depth == 0 || board->isGameOver())
        {
            return evaluateBoard(board);
        }
        int v;
        if (board->isPlayer1Turn())
        {
            v = INT_MIN;
            vector<int> moves = board->getMovePositions();
            for (int i = 0; i < moves.size(); i++)
            {
                MancalaBoard *new_board = board->playMove(moves[i]);
                v = max(v, minimax(new_board, depth - 1, a, b));
                if (b <= v)
                {
                    return v;
                }
                a = max(a, v);
            }
        }
        else
        {
            v = INT_MAX;
            vector<int> moves = board->getMovePositions();
            for (int i = 0; i < moves.size(); i++)
            {
                MancalaBoard *new_board = board->playMove(moves[i]);
                v = min(v, minimax(new_board, depth - 1, a, b));
                if (v <= a)
                {
                    return v;
                }
                b = min(b, v);
            }
        }
        return v;
    }

    int getBestMove(MancalaBoard *board)
    {
        int best_move_position = 0;
        int best_value = board->isPlayer1Turn() ? INT_MIN : INT_MAX;
        vector<int> moves = board->getMovePositions();
        for (int i = 0; i < moves.size(); i++)
        {
            MancalaBoard *new_board = board->playMove(moves[i]);
            int value = minimax(new_board, getDepthLimit(new_board), INT_MIN, INT_MAX);
            if (board->isPlayer1Turn() && value > best_value)
            {
                best_value = value;
                best_move_position = moves[i];
            }
            else if (!board->isPlayer1Turn() && value < best_value)
            {
                best_value = value;
                best_move_position = moves[i];
            }
        }
        return best_move_position;
    }

    int runGameWithSteps(MancalaBoard *board)
    {
        while (!board->isGameOver())
        {
            step++;
            int move_position = getBestMove(board);
            cout << "\nMove for player" << (board->isPlayer1Turn() ? "1" : "2") << ": " << move_position + 1 << endl;
            board = board->playMove(move_position);
            board->printBoard();
        }
        cout << "\nEnd game for player" << (board->isPlayer1Turn() ? "1" : "2") << ": " << endl;
        board->printBoard();
        cout << "\nGame Over\n";
        return board->getWinner();
    }

    int runGame(MancalaBoard *board)
    {
        while (!board->isGameOver())
        {
            step++;
            int move_position = getBestMove(board);
            board = board->playMove(move_position);
        }
        return board->getWinner();
    }

    int playGame(MancalaBoard *board)
    {
        while (!board->isGameOver())
        {
            step++;
            int move_position;
            if (board->isPlayer1Turn())
            {
                cout << "\nEnter your move for player1: ";
                cin >> move_position;
                move_position--;
                while (move_position < 0 || move_position > 5 || board->getPlayer1Bin()[move_position] == 0)
                {
                    cout << "Invalid move\nEnter your move for player1 again: ";
                    cin >> move_position;
                    move_position--;
                }
            }
            else
            {
                move_position = getBestMove(board);
            }

            cout << "\nPlayer" << (board->isPlayer1Turn() ? "1" : "2") << " move: " << move_position + 1 << endl;
            board = board->playMove(move_position);
            board->printBoard();
        }
        cout << "\nPlayer" << (board->isPlayer1Turn() ? "1" : "2") << " move: " << endl;
        board->printBoard();
        cout << "\nGame Over\n";
        return board->getWinner();
    }
};
