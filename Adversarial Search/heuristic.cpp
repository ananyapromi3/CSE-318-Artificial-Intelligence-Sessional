#include <iostream>
using namespace std;
#include "MancalaBoard.cpp"

int heuristic1(MancalaBoard *board)
{
    return board->getPlayer1Storage() - board->getPlayer2Storage();
}

int heuristic2(MancalaBoard *board, int w1, int w2)
{
    vector<int> temp;
    int player1_stones = 0;
    int player2_stones = 0;
    temp = board->getPlayer1Bin();
    for (int i = 0; i < temp.size(); i++)
    {
        player1_stones += temp[i];
    }
    temp = board->getPlayer2Bin();
    for (int i = 0; i < temp.size(); i++)
    {
        player2_stones += temp[i];
    }
    return w1 * heuristic1(board) + w2 * (player1_stones - player2_stones);
}

int heuristic3(MancalaBoard *board, int w1, int w2, int w3)
{
    return heuristic2(board, w1, w2) + w3 * board->getPlayer1ExtraMove();
}

int heuristic4(MancalaBoard *board, int w1, int w2, int w3, int w4)
{
    return heuristic3(board, w1, w2, w3) + w4 * board->getPlayer1StoneCapture();
}