#include <iostream>
#include <fstream>
#include "Game.cpp"
using namespace std;

int main()
{
    freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    MancalaBoard *board = new MancalaBoard();
    int h1, h2;
    int n;
    cin >> n;
    vector<int> w1(4, 1), w2(4, 1);
    cin >> h1;
    if (h1 > 1)
    {
        for (int i = 0; i < h1; i++)
        {
            cin >> w1[i];
        }
    }
    cin >> h2;
    if (h2 > 1)
    {
        for (int i = 0; i < h2; i++)
        {
            cin >> w2[i];
        }
    }
    int draw = 0;
    int p1 = 0;
    int p2 = 0;
    for (int i = 0; i < n; i++)
    {
        Game *game = new Game();
        board->resetBoard();
        game->setPlayer1Heuristic(h1);
        game->setPlayer1Weights(w1);
        game->setPlayer2Heuristic(h2);
        game->setPlayer2Weights(w2);
        // cout << "Initial Mancala Board:\n";
        // board->printBoard();
        // int result = game->runGameWithSteps(board);
        int result = game->runGame(board);
        if (result == 1)
        {
            cout << "Player 1 wins" << endl;
            p1++;
        }
        else if (result == -1)
        {
            cout << "Player 2 wins" << endl;
            p2++;
        }
        else
        {
            cout << "Draw" << endl;
            draw++;
        }
        cout << "Total Move: " << game->getStep() << endl;
    }
    cout << "Player 1 wins: " << p1 << endl;
    cout << "Player 2 wins: " << p2 << endl;
    cout << "Draw: " << draw << endl;
    return 0;
}