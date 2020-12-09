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

    int proxMines;

    bool hasMine;

    bool hasFlag;

    bool isRevealed;

    float x_pos;

    float y_pos;

    int tileNum;

    vector<Tile*> adjacentTiles; //Thank you Professor Fox!

    Sprite tileSprite;

    Tile();

    Tile& operator=(const Tile &d);

};

Tile& Tile::operator=(const Tile &d)
{
    this->adjacentTiles = d.adjacentTiles;

    this->isRevealed = d.isRevealed;

    this->x_pos = d.x_pos;

    this->y_pos = y_pos;

    this->tileSprite = d.tileSprite;

    this->proxMines = d.proxMines;

    this->hasMine = d.hasMine;

    this->hasFlag = d.hasFlag;

    return *this;
}


Tile::Tile()
{
    proxMines = 0;

    x_pos = 0;

    y_pos = 0;

    hasMine = false;

    hasFlag = false;

    isRevealed = false;

    tileNum = 0;
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

    int count = 0;

    for (int i = 0; i < ((height - 88) / 32); i++)
    {
        for (int j = 0; j < (width / 32); j++)
        {
            Tile temp = Tile();

            temp.tileNum = count;

            count++;

            tempTiles.push_back(temp);
        }

        count = 0;

        Tiles.push_back(tempTiles);
    }
}