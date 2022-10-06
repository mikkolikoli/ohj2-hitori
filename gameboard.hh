#ifndef GAMEBOARD_HH
#define GAMEBOARD_HH
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

using namespace std;


class Gameboard
{
public:
    Gameboard();

    void init();
    void init(const vector<uint>& manualInput);

    void print();
    bool removeNumber(vector<uint> coordinates);
    bool hasWon();
    bool hasLost();

private:
    vector<vector<uint>> formatGameboard(const vector<uint>& unformattedGameboard);
    vector<vector<uint>> gameboard;
    bool checkInput(vector<uint> coordinates);
    bool checkNeighbours();
    unsigned int stoi_with_check(const string& str);
    const uint BOARD_SIDE = 5;
    const unsigned char EMPTY = ' ';
};

#endif // GAMEBOARD_HH
