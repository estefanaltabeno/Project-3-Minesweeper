#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <random>

using namespace std;
using namespace sf;

//Helper Random class, thanks Professor Fox!

class Random
{
    static mt19937 random;

public:

    static int Number(int min, int max);
};

mt19937 Random::random;

int Random::Number(int min, int max)
{
    uniform_int_distribution<int> dist(min, max);

    return dist(random);
}


class Tile
{

public:

    bool hasMine;

    bool hasFlag;

    vector<Tile*> adjacentTiles; //Thank you Professor Fox!

    Sprite tileSprite;

    Tile();

};

Tile::Tile()
{
    hasMine = false;

    hasFlag = false;
}

class Board
{
public:

    vector<vector<Tile>> Tiles;

    Board(int width, int height);

};

Board::Board(int width, int height)
{
    vector<Tile> tempTiles;

    for (int i = 0; i < ((height - 88) / 32); i++)
    {
        for (int j = 0; j < (width / 32); j++)
        {
            Tile temp = Tile();

            tempTiles.push_back(temp);
        }

        Tiles.push_back(tempTiles);
    }
}