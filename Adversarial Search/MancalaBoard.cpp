#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
using namespace std;

class MancalaBoard
{
    vector<int> player1_bin;
    vector<int> player2_bin;
    int player1_storage;
    int player2_storage;
    bool player1_turn;
    int player1_extra_move;
    int player2_extra_move;
    int player1_stone_capture;
    int player2_stone_capture;

public:
    MancalaBoard()
    {
        player1_bin = vector<int>(6, 4);
        player2_bin = vector<int>(6, 4);
        player1_storage = 0;
        player2_storage = 0;
        player1_turn = true;
        player1_extra_move = 0;
        player2_extra_move = 0;
        player1_stone_capture = 0;
        player2_stone_capture = 0;
    }

    MancalaBoard(const MancalaBoard &MancalaBoard)
    {
        player1_bin = MancalaBoard.player1_bin;
        player2_bin = MancalaBoard.player2_bin;
        player1_storage = MancalaBoard.player1_storage;
        player2_storage = MancalaBoard.player2_storage;
        player1_turn = MancalaBoard.player1_turn;
        player1_extra_move = MancalaBoard.player1_extra_move;
        player2_extra_move = MancalaBoard.player2_extra_move;
        player1_stone_capture = MancalaBoard.player1_stone_capture;
        player2_stone_capture = MancalaBoard.player2_stone_capture;
    }

    ~MancalaBoard()
    {
    }

    void resetBoard()
    {
        player1_bin = vector<int>(6, 4);
        player2_bin = vector<int>(6, 4);
        player1_storage = 0;
        player2_storage = 0;
        player1_turn = true;
        player1_extra_move = 0;
        player2_extra_move = 0;
        player1_stone_capture = 0;
        player2_stone_capture = 0;
    }

    int getPlayer1Storage()
    {
        return player1_storage;
    }

    int getPlayer2Storage()
    {
        return player2_storage;
    }

    vector<int> getPlayer1Bin()
    {
        return player1_bin;
    }

    vector<int> getPlayer2Bin()
    {
        return player2_bin;
    }

    bool isPlayer1Turn()
    {
        return player1_turn;
    }

    int getPlayer1ExtraMove()
    {
        return player1_extra_move;
    }

    int getPlayer2ExtraMove()
    {
        return player2_extra_move;
    }

    int getPlayer1StoneCapture()
    {
        return player1_stone_capture;
    }

    int getPlayer2StoneCapture()
    {
        return player2_stone_capture;
    }

    vector<int> getMovePositions()
    {
        vector<int> move_positions;
        if (player1_turn)
        {
            for (int i = 0; i < 6; i++)
            {
                if (player1_bin[i] > 0)
                {
                    move_positions.push_back(i);
                }
            }
        }
        else
        {
            for (int i = 0; i < 6; i++)
            {
                if (player2_bin[i] > 0)
                {
                    move_positions.push_back(i);
                }
            }
        }
        random_device rd;
        mt19937 g(rd());
        shuffle(move_positions.begin(), move_positions.end(), g);
        return move_positions;
    }

    MancalaBoard *playMove(int move_position)
    {
        MancalaBoard *new_board = new MancalaBoard(*this);
        vector<int> all_bins;
        //  0  1  2  3  4  5    -> player1_bin
        // 12 11 10  9  8  7    -> player2_bin
        // 6                    -> player1_storage
        // 13                   -> player2_storage
        for (int i = 0; i < new_board->player1_bin.size(); i++)
        {
            all_bins.push_back(new_board->player1_bin[i]);
        }
        all_bins.push_back(new_board->player1_storage);
        for (int i = 0; i < new_board->player2_bin.size(); i++)
        {
            all_bins.push_back(new_board->player2_bin[i]);
        }
        all_bins.push_back(new_board->player2_storage);
        if (new_board->player1_turn)
        {
            int i = move_position;
            int stones = all_bins[i];
            all_bins[i] = 0;
            while (stones > 0)
            {
                i = (i + 1) % 14;
                if (i == 13)
                {
                    continue;
                }
                all_bins[i]++;
                stones--;
            }
            if (i < 6 && all_bins[i] == 1 && all_bins[12 - i] > 0)
            {
                player1_stone_capture += all_bins[i] + all_bins[12 - i];
                all_bins[6] += all_bins[i] + all_bins[12 - i];
                all_bins[i] = 0;
                all_bins[12 - i] = 0;
            }
            if (i == 6)
            {
                player1_extra_move++;
                new_board->player1_turn = true;
            }
            else
            {
                new_board->player1_turn = false;
            }
        }
        else
        {
            int i = move_position + 7;
            int stones = all_bins[i];
            all_bins[i] = 0;
            while (stones > 0)
            {
                i = (i + 1) % 14;
                if (i == 6)
                {
                    continue;
                }
                all_bins[i]++;
                stones--;
            }
            if (i > 6 && i < 13 && all_bins[i] == 1 && all_bins[12 - i] > 0)
            {
                player2_stone_capture += all_bins[i] + all_bins[12 - i];
                all_bins[13] += all_bins[i] + all_bins[12 - i];
                all_bins[i] = 0;
                all_bins[12 - i] = 0;
            }
            if (i == 13)
            {
                player2_extra_move++;
                new_board->player1_turn = false;
            }
            else
            {
                new_board->player1_turn = true;
            }
        }
        for (int i = 0; i < 6; i++)
        {
            new_board->player1_bin[i] = all_bins[i];
        }
        new_board->player1_storage = all_bins[6];
        for (int i = 7; i < 13; i++)
        {
            new_board->player2_bin[i - 7] = all_bins[i];
        }
        new_board->player2_storage = all_bins[13];
        return new_board;
    }

    bool isGameOver()
    {
        bool player1_bin_empty = true;
        bool player2_bin_empty = true;
        for (int i = 0; i < player1_bin.size(); i++)
        {
            if (player1_bin[i] > 0)
            {
                player1_bin_empty = false;
                break;
            }
        }
        for (int i = 0; i < player2_bin.size(); i++)
        {
            if (player2_bin[i] > 0)
            {
                player2_bin_empty = false;
                break;
            }
        }
        if (player1_bin_empty)
        {
            for (int i = 0; i < player2_bin.size(); i++)
            {
                player2_storage += player2_bin[i];
                player2_bin[i] = 0;
            }
        }
        if (player2_bin_empty)
        {
            for (int i = 0; i < player1_bin.size(); i++)
            {
                player1_storage += player1_bin[i];
                player1_bin[i] = 0;
            }
        }
        return player1_bin_empty || player2_bin_empty;
    }

    int getWinner()
    {
        // 1    -> player1 wins
        // -1   -> player2 wins
        // 0    -> draw
        if (player1_storage > player2_storage)
        {
            return 1;
        }
        else if (player1_storage < player2_storage)
        {
            return -1;
        }
        else
        {
            return 0;
        }
    }

    void printBoard()
    {
        cout << "\n\t\t\tPlayer2\n\t";
        for (int i = 12; i >= 7; i--)
        {
            cout << "-\t";
        }
        cout << "\n\t";
        for (int i = 5; i >= 0; i--)
        {
            cout << player2_bin[i] << "\t";
        }
        cout << "\n\t";
        for (int i = 12; i >= 7; i--)
        {
            cout << "-\t";
        }
        cout << "\n"
             << player2_storage << "\t\t\t\t\t\t\t" << player1_storage << "\n\t";
        for (int i = 0; i < 6; i++)
        {
            cout << "-\t";
        }
        cout << "\n\t";
        for (int i = 0; i < 6; i++)
        {
            cout << player1_bin[i] << "\t";
        }
        cout << "\n\t";
        for (int i = 0; i < 6; i++)
        {
            cout << "-\t";
        }
        cout << "\n\t\t\tPlayer1\n";
        cout << "\n----------------------------------------------------------\n";
    }
};