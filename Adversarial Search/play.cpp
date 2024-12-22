#include <iostream>
#include <fstream>
#include "Game.cpp"
using namespace std;

int main()
{
    MancalaBoard *board = new MancalaBoard();
    cout << "Play against computer\n";
    cout << "You are player 1\n";
    int h2 = rand() % 4 + 1;
    vector<int> w2(4, 1);
    if (h2 > 1)
    {
        for (int i = 0; i < h2; i++)
        {
            w2[i] = rand() % 10 + 1;
        }
    }
    Game *game = new Game();
    board->resetBoard();
    game->setPlayer2Heuristic(h2);
    game->setPlayer2Weights(w2);
    cout << "Initial Mancala Board:\n";
    board->printBoard();
    int result = game->playGame(board);
    if (result == 1)
    {
        cout << "You won !!!" << endl;
    }
    else if (result == -1)
    {
        cout << "You lost :(" << endl;
    }
    else
    {
        cout << "Game draw :|" << endl;
    }
    cout << "Total Move: " << game->getStep() << endl;
    return 0;
}