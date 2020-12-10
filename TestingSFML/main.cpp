#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <fstream>
#include <string>
#include <iostream>
#include "HelperClasses.h"

using namespace std;

//I know maybe it would help but I don't want to use sf:: everytime for things like std::

using namespace sf;

vector<int> SearchForTile(Board& board, float x, float y)
{
    int i_index = 0;

    int j_index = 0;

    Vector2f vectorPos;

    float x_comp = 0;

    float y_comp = 0;

    vector<int> indexes;

    for (int i = 0; i < board.Tiles.size(); i++)
    {
        for (int j = 0; j < board.Tiles.at(i).size(); j++)
        {
            vectorPos = board.Tiles.at(i).at(j).tileSprite.getPosition();

            x_comp = vectorPos.x;

            y_comp = vectorPos.y;

            if (x >= x_comp && x < x_comp + 32)
            {
                if (y >= y_comp && y < y_comp + 32)
                {
                    indexes.push_back(i);

                    indexes.push_back(j);

                    return indexes;
                }
            }
        }
    }
    return indexes;
}

void setTextures(Board& board, Texture& text, vector<int>& indexes)
{
    board.Tiles.at(indexes.at(0)).at(indexes.at(1)).tileSprite.setTexture(text);
}

Sprite setTextures(Board& board, vector<int>& indexes, Texture& flagT)
{
    Sprite temp;

    temp.setTexture(flagT);

    Vector2f vector;

    float x = 0;

    float y = 0;

    vector = board.Tiles.at(indexes.at(0)).at(indexes.at(1)).tileSprite.getPosition();

    x = vector.x;

    y = vector.y;

    temp.setPosition(x, y);

    return temp;
}

bool CheckForCopies(Sprite check, vector<Sprite>& sprites)
{
    Vector2f vector;

    Vector2f checkVector = check.getPosition();

    float x = checkVector.x;

    float y = checkVector.y;

    for (int i = 0; i < sprites.size(); i++)
    {
        vector = sprites.at(i).getPosition();

        if (x >= vector.x && x < vector.x + 32)
        {
            if (y >= vector.y && y < vector.y + 32)
            {
                sprites.erase(sprites.begin() + i);

                return true;
            }
        }
    }

    return false;
}

bool CheckIfRevealed(Sprite& sprite, Board& board)
{
    Vector2f vectorSprite = sprite.getPosition();

    Vector2f vectorAgainst;

    float x = vectorSprite.x;

    float y = vectorSprite.y;

    for (int i = 0; i < board.Tiles.size(); i++)
    {
        for (int j = 0; j < board.Tiles.at(i).size(); j++)
        {
            vectorAgainst = board.Tiles.at(i).at(j).tileSprite.getPosition();

            if (x >= vectorAgainst.x && x < vectorAgainst.x + 32)
            {
                if (y >= vectorAgainst.y && y < vectorAgainst.y + 32)
                {
                    if (board.Tiles.at(i).at(j).isRevealed)
                    {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

void SetRandomMines(Board& board, int height, int width, int mineCount)
{
    int random_x = 0;

    int random_y = 0;

    vector<int> indexes;

    for (int i = 0; i < mineCount; i++)
    {
        random_x = Random::Number(0, width);

        random_y = Random::Number(0, height - 88);

        indexes = SearchForTile(board, random_x, random_y);

        board.Tiles.at(indexes.at(0)).at(indexes.at(1)).hasMine = true;
    }
}


void SetProxNumbers(Board& board, int width, int height)
{
    width++;

    height++;

    int count = 0;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            count = 0;

            for (auto & adjacentTile : board.Tiles.at(i).at(j).adjacentTiles)
            {
                if (adjacentTile == nullptr)
                {

                }
                else
                {
                    if (adjacentTile->hasMine)
                    {
                        count++;
                    }
                }
            }

            board.Tiles.at(i).at(j).proxMines = count;
        }
    }

}



vector<Sprite> SetDigitRect(int height, int width, Sprite& zero, Sprite& one, Sprite& two, Sprite& three, Sprite& four, Sprite& five, Sprite& six, Sprite& seven, Sprite& eight, Sprite& nine, Sprite& negativeSign, int mineCount)
{
    bool isNeg = false;

    vector<Sprite> countDigits;

    float x_pos = 21;

    float y_pos = height - 88;

    if (mineCount < 0)
    {
        countDigits.push_back(negativeSign);

        mineCount *= -1;

        isNeg = true;
    }

    if (mineCount < 100)
    {
        countDigits.push_back(zero);
    }

    if (mineCount < 10)
    {
        countDigits.push_back(zero);
    }

    string temp = to_string(mineCount);

    string tempNum = "";

    for (int i = 0; i < temp.size(); i++)
    {
        tempNum = "";

        tempNum.push_back(temp.at(i));

        int digit = stoi(tempNum);

        if (digit == 1)
        {
            countDigits.push_back(one);
        }

        else if (digit == 2)
        {
            countDigits.push_back(two);
        }

        else if (digit == 3)
        {
            countDigits.push_back(three);
        }

        else if (digit == 4)
        {
            countDigits.push_back(four);
        }

        else if (digit == 5)
        {
            countDigits.push_back(five);
        }

        else if (digit == 6)
        {
            countDigits.push_back(six);
        }

        else if (digit == 7)
        {
            countDigits.push_back(seven);
        }

        else if (digit == 8)
        {
            countDigits.push_back(eight);
        }

        else if (digit == 9)
        {
            countDigits.push_back(nine);
        }

        else if (digit == 0)
        {
            countDigits.push_back(zero);
        }
    }

    for (int i = 0; i < countDigits.size(); i++)
    {
        if (isNeg)
        {
            countDigits.at(i).setPosition(0, y_pos);

            isNeg = false;
        }

        else
        {
            countDigits.at(i).setPosition(x_pos, y_pos);

            x_pos += 21;
        }
    }

    return countDigits;
}

void SetPositionsandNeighbors(Board& board, int widthCalc, int heightCalc, Texture& tile)
{
    float x_pos = 0;

    float y_pos = 0;

    for (int i = 0; i < heightCalc + 1; i++)
    {
        for (int j = 0; j < widthCalc + 1; j++)
        {
            board.Tiles.at(i).at(j).tileSprite.setTexture(tile);

            board.Tiles.at(i).at(j).tileSprite.setPosition(x_pos, y_pos);

            board.Tiles.at(i).at(j).x_pos = x_pos;

            board.Tiles.at(i).at(j).y_pos = y_pos;

            //cout << i << " i and j " << j << endl;

            //cout << "Positions " << x_pos << " x and y " << y_pos << endl;

            Tile* behind;

            Tile* front;

            Tile* top;

            Tile* below;

            Tile* topLeft;

            Tile* topRight;

            Tile* bottomLeft;

            Tile* bottomRight;

            //Top right corner
            if (j == 0 && i == 0)
            {
                behind = nullptr;

                top = nullptr;

                front = &board.Tiles.at(i).at(j + 1);

                below = &board.Tiles.at(i + 1).at(j);

                bottomLeft = nullptr;

                bottomRight = &board.Tiles.at(i + 1).at(j + 1);

                topLeft = nullptr;

                topRight = nullptr;
            }

                //Top left corner
            else if ((j == widthCalc && i == 0))
            {
                topRight = nullptr;

                top = nullptr;

                topLeft = nullptr;

                front = nullptr;

                bottomRight = nullptr;

                below = &board.Tiles.at(i + 1).at(j);

                bottomLeft = &board.Tiles.at(i + 1).at(j - 1);

                behind = &board.Tiles.at(i).at(j - 1);
            }

                //Bottom left corner
            else if (j == 0 && i == heightCalc)
            {
                below = nullptr;

                behind = nullptr;

                bottomLeft = nullptr;

                topLeft = nullptr;

                bottomLeft = nullptr;

                top = &board.Tiles.at(i - 1).at(j);

                front = &board.Tiles.at(i).at(j + 1);

                topRight = &board.Tiles.at(i - 1).at(j + 1);
            }


                //Bottom right corner
            else if (j == widthCalc && i == heightCalc)
            {
                front = nullptr;

                bottomRight = nullptr;

                below = nullptr;

                topRight = nullptr;

                bottomLeft = nullptr;

                behind = &board.Tiles.at(i).at(j - 1);

                topLeft - &board.Tiles.at(i - 1).at(j - 1);

                top = &board.Tiles.at(i - 1).at(j);
            }

                //Leftmost Tiles
            else if (j == 0)
            {
                behind = nullptr;

                front = &board.Tiles.at(i).at(j + 1);

                below = &board.Tiles.at(i + 1).at(j);

                top = &board.Tiles.at(i - 1).at(j);

                topLeft = nullptr;

                topRight = &board.Tiles.at(i - 1).at(j + 1);

                bottomLeft = nullptr;

                bottomRight = &board.Tiles.at(i + 1).at(j + 1);

            }

                //Rightmost Tiles
            else if (j == widthCalc)
            {
                front = nullptr;

                bottomRight = nullptr;

                topRight = nullptr;

                behind = &board.Tiles.at(i).at(j - 1);

                topLeft = &board.Tiles.at(i - 1).at(j - 1);

                below = &board.Tiles.at(i + 1).at(j);

                bottomLeft = &board.Tiles.at(i + 1).at(j - 1);

                top = &board.Tiles.at(i - 1).at(j);
            }

                //Topmost Tiles
            else if ((j > 0) && (j < widthCalc) && (i == 0))
            {
                top = nullptr;

                behind = &board.Tiles.at(i).at(j - 1);

                front = &board.Tiles.at(i).at(j + 1);

                below = &board.Tiles.at(i + 1).at(j);

                topRight = nullptr;

                topLeft = nullptr;

                bottomLeft = &board.Tiles.at(i + 1).at(j - 1);

                bottomRight = &board.Tiles.at(i + 1).at(j + 1);
            }

                //Bottommost Tiles
            else if (j > 0 && j < widthCalc && i == heightCalc)
            {
                below = nullptr;

                bottomRight = nullptr;

                bottomRight = nullptr;

                behind = &board.Tiles.at(i).at(j - 1);

                front = &board.Tiles.at(i).at(j + 1);

                top = &board.Tiles.at(i - 1).at(j);

                topRight = &board.Tiles.at(i - 1).at(j + 1);

                topLeft = &board.Tiles.at(i - 1).at(j - 1);
            }

            else
            {
                behind = &board.Tiles.at(i).at(j - 1);

                front = &board.Tiles.at(i).at(j + 1);

                top = &board.Tiles.at(i - 1).at(j);

                below = &board.Tiles.at(i + 1).at(j);

                topLeft = &board.Tiles.at(i - 1).at(j - 1);

                topRight = &board.Tiles.at(i - 1).at(j + 1);

                bottomRight = &board.Tiles.at(i + 1).at(j + 1);

                bottomLeft = &board.Tiles.at(i + 1).at(j - 1);
            }

            board.Tiles.at(i).at(j).adjacentTiles.push_back(behind);

            board.Tiles.at(i).at(j).adjacentTiles.push_back(front);

            board.Tiles.at(i).at(j).adjacentTiles.push_back(top);

            board.Tiles.at(i).at(j).adjacentTiles.push_back(below);

            board.Tiles.at(i).at(j).adjacentTiles.push_back(bottomLeft);

            board.Tiles.at(i).at(j).adjacentTiles.push_back(bottomRight);

            board.Tiles.at(i).at(j).adjacentTiles.push_back(topLeft);

            board.Tiles.at(i).at(j).adjacentTiles.push_back(topRight);

            x_pos += 32;
        }

        x_pos = 0;

        y_pos += 32;
    }
}

void ResetAll(Board& board, int width, int height, int& mineCount, int& finalMineCount, bool& check, bool& printMine, bool& remove, bool& checkIfRevealed, bool& yaWon, vector<Sprite>& flagSprites, vector<Sprite>& mineSprites, vector<Sprite>& proxNumSprites, vector<Sprite>& flagOverMines, int widthCalc, int heightCalc, Texture& tile, int& winCount, vector<Sprite>& debugModeMines)
{
    mineCount = finalMineCount;

    board = Board(width, height);

    SetPositionsandNeighbors(board, widthCalc, heightCalc, tile);

    SetRandomMines(board, height, width, mineCount);

    SetProxNumbers(board, widthCalc, heightCalc);

    check = false;

    printMine = false;

    remove = false;

    checkIfRevealed = false;

    yaWon = false;

    winCount = 0;

    flagSprites.clear();

    mineSprites.clear();

    proxNumSprites.clear();

    flagOverMines.clear();

    debugModeMines.clear();
}

void ReadInBoard(Board& board, int& width, int& height, int& mineCount, int& finalMineCount, bool& check, bool& printMine, bool& remove, bool& checkIfRevealed, bool& yaWon, vector<Sprite>& flagSprites, vector<Sprite>& mineSprites, vector<Sprite>& proxNumSprites, vector<Sprite> flagOverMines, int& widthCalc, int& heightCalc, Texture& tile, int& winCount, vector<Sprite>& debugModeMines, string name)
{
    ResetAll(board, width, height, mineCount, finalMineCount, check, printMine, remove, checkIfRevealed, yaWon, flagSprites, mineSprites, proxNumSprites, flagOverMines, widthCalc, heightCalc, tile, winCount, debugModeMines);

    ifstream file(name);

    vector<vector<int>> indexesOfMines;

    vector<int> currentIndexes;

    string tempString;

    int count = 0;

    int mines = 0;

    while(getline(file, tempString, '\n'))
    {
        for (int i = 0; i < tempString.size(); i++)
        {
            if (tempString.at(i) == '1')
            {
                mines++;

                currentIndexes.push_back(count);

                currentIndexes.push_back(i);
            }
        }

        indexesOfMines.push_back(currentIndexes);

        count++;
    }

    widthCalc = tempString.size();

    heightCalc = count;

    width = widthCalc * 32;

    height = ((heightCalc * 32 ) + 88);

    board = Board(width, height);

    for (int i = 0; i < indexesOfMines.size(); i++)
    {
        board.Tiles.at(indexesOfMines.at(i).at(0)).at(indexesOfMines.at(i).at(1)).hasMine = true;
    }

    mineCount = mines;

    SetPositionsandNeighbors(board, widthCalc - 1, heightCalc - 1, tile);

    SetProxNumbers(board, widthCalc - 1, heightCalc - 1);

}

int main()
{
    //Reading in Data

    string widthS;

    string heightS;

    string mineCountS;

    int tileCount = 0;

    ifstream file ("config.cfg");

    getline(file, widthS, '\n');

    getline(file, heightS,'\n');

    getline(file, mineCountS, '\n');

    int width = stoi(widthS);

    int height = stoi(heightS);

    int mineCount = stoi(mineCountS);

    tileCount = width * height;

    width *= 32;

    height = (height * 32) + 88;

    int finalMineCount = mineCount;

    //End of reading data



    //The numbers in the video mode function arguments are by pixels, not any other units

    RenderWindow window (VideoMode(width, height), "Minesweeper");

    Board board = Board(width, height);

    //Loaded in a window and a board given the config file input

    Texture numOne;

    numOne.loadFromFile("number_1.png");

    Texture numTwo;

    numTwo.loadFromFile("number_2.png");

    Texture numThree;

    numThree.loadFromFile("number_3.png");

    Texture numFour;

    numFour.loadFromFile("number_4.png");

    Texture numFive;

    numFive.loadFromFile("number_5.png");

    Texture numSix;

    numSix.loadFromFile("number_6.png");

    Texture numSeven;

    numSeven.loadFromFile("number_7.png");

    Texture numEight;

    numEight.loadFromFile("number_8.png");



    Texture digits;

    digits.loadFromFile("digits.png");

    Sprite digitSprite;

    digitSprite.setTexture(digits);

    Sprite digitZero = digitSprite;

    Sprite digitOne = digitSprite;

    Sprite digitTwo = digitSprite;

    Sprite digitThree = digitSprite;

    Sprite digitFour = digitSprite;

    Sprite digitFive = digitSprite;

    Sprite digitSix = digitSprite;

    Sprite digitSeven = digitSprite;

    Sprite digitEight = digitSprite;

    Sprite digitNine = digitSprite;

    Sprite negativeSign = digitSprite;




    Texture tile;

    tile.loadFromFile("tile_hidden.png");

    Texture revealedTile;

    revealedTile.loadFromFile("tile_revealed.png");

    Texture mine;

    mine.loadFromFile("mine.png");

    Texture flagT;

    flagT.loadFromFile("flag.png");

    Texture smileyFace;

    smileyFace.loadFromFile("face_happy.png");

    Texture xFace;

    xFace.loadFromFile("face_lose.png");

    Texture shadesFace;

    shadesFace.loadFromFile("face_win.png");

    Texture debugT;

    debugT.loadFromFile("debug.png");

    Texture testone;

    testone.loadFromFile("test_1.png");

    Texture testtwo;

    testtwo.loadFromFile("test_2.png");

    Texture testthree;

    testthree.loadFromFile("test_3.png");


    //End of Textures

    Sprite smileySprite;

    smileySprite.setTexture(smileyFace);


    Sprite xFaceSprite;

    xFaceSprite.setTexture(xFace);


    Sprite shadeFace;

    shadeFace.setTexture(shadesFace);

    Sprite debugS;

    debugS.setTexture(debugT);


    Sprite testoneS;

    testoneS.setTexture(testone);


    Sprite testTwo;

    testTwo.setTexture(testtwo);


    Sprite testThree;

    testThree.setTexture(testthree);


    //Lots of texture and sprites here

    int widthCalc = (width / 32) - 1;

    int heightCalc = ((height - 88) / 32) - 1;

    SetPositionsandNeighbors(board, widthCalc, heightCalc, tile);

    //Working through the board's Tiles vector and setting the positions of each to make sense. Also doing it here to avoid issues with the texture pointers and whatnot


    bool check = false;

    bool printMine = false;

    bool remove = false;

    bool checkIfRevealed = false;

    bool yaWon = false;

    bool debugMode = false;

    Sprite temp;

    Tile tempTile;

    vector<int> tempIndexes;

    vector<Sprite> flagSprites;

    vector<Sprite> mineSprites;

    vector<Sprite> proxNumSprites;

    vector<Sprite> flagOverMines;

    vector<Sprite> debugModeMines;

    vector<int> indexess;

    vector<Tile> tilesWith0Prox;

    vector<Sprite> mineCountSprites;

    SetRandomMines(board, height, width, mineCount);

    //WORKING ON THIS SETTING THE NUMBERS AND THEIR PROXIMITY TO THE MINES THAT I SET WITH THE FUNCTION PRIOR

    SetProxNumbers(board, widthCalc, heightCalc);

    int winCount = 0;

    while(window.isOpen())
    {
        Event event;

        while (window.pollEvent(event))
        {
            window.clear(Color(255, 255, 255));

            for (int i = 0; i < board.Tiles.size(); i++)
            {
                for (int j = 0; j < board.Tiles.at(i).size(); j++)
                {
                    window.draw(board.Tiles.at(i).at(j).tileSprite);
                }
            }

            //I know my code is messy and trust me, I know. I'm not doing this project last minute, I've been working at this
            //for the past week but since I'm now on a time crunch, I'm getting messy. I'm sorry! I would normally put everything in functions and
            //make it neat but I don't have the time!

            digitSprite.setPosition(21, height - 88);

            digitZero.setTextureRect(IntRect(0, 0, 21, 32));

            digitOne.setTextureRect(IntRect(22, 0, 21, 32));

            digitTwo.setTextureRect(IntRect(43, 0, 21, 32));

            digitThree.setTextureRect(IntRect(64, 0, 21, 32));

            digitFour.setTextureRect(IntRect(85, 0, 21, 32));

            digitFive.setTextureRect(IntRect(106, 0, 21, 32));

            digitSix.setTextureRect(IntRect(127, 0, 21, 32));

            digitSeven.setTextureRect(IntRect(148, 0, 21, 32));

            digitEight.setTextureRect(IntRect(169, 0, 21, 32));

            digitNine.setTextureRect(IntRect(190, 0, 21, 32));

            negativeSign.setTextureRect(IntRect(211, 0, 21, 32));

            smileySprite.setPosition(width - 384, height - 88);

            xFaceSprite.setPosition(width - 384, height - 88);

            shadeFace.setPosition(width - 384, height - 88);

            debugS.setPosition(width - 256, height - 88);

            testoneS.setPosition(width - 192, height - 88);

            testTwo.setPosition(width - 128, height - 88);

            testThree.setPosition(width - 64, height - 88);

            window.draw(debugS);

            window.draw(testoneS);

            window.draw(testTwo);

            window.draw(testThree);

            switch (event.type)
            {
                case Event::Closed:
                    window.close();
                    break;
                case Event::MouseButtonPressed:
                    if (event.mouseButton.button == Mouse::Left)
                    {
                        //Smiley Face Sprite

                        if (event.mouseButton.x >= width - 384 && event.mouseButton.x < width - 320)
                        {
                            if (event.mouseButton.y >= height - 88 && event.mouseButton.y < height)
                            {
                                ResetAll(board, width, height, mineCount, finalMineCount, check, printMine, remove, checkIfRevealed, yaWon, flagSprites, mineSprites, proxNumSprites, flagOverMines, widthCalc, heightCalc, tile, winCount, debugModeMines);

                                continue;
                            }
                        }

                        //Test 1 Button
                        if (event.mouseButton.x >= width - 192 && event.mouseButton.x < width - 128)
                        {
                            if(event.mouseButton.y >= height - 88 && event.mouseButton.y < height)
                            {
                                ReadInBoard(board, width, height, mineCount, finalMineCount, check, printMine, remove, checkIfRevealed, yaWon, flagSprites, mineSprites, proxNumSprites, flagOverMines, widthCalc, heightCalc, tile, winCount, debugModeMines, "testboard1.brd");

                                continue;
                            }
                        }

                        if (printMine || yaWon)
                        {
                            if (event.mouseButton.x >= width - 384 && event.mouseButton.x < width - 320)
                            {
                                if (event.mouseButton.y >= height - 88 && event.mouseButton.y < height)
                                {
                                    ResetAll(board, width, height, mineCount, finalMineCount, check, printMine, remove, checkIfRevealed, yaWon, flagSprites, mineSprites, proxNumSprites, flagOverMines, widthCalc, heightCalc, tile, winCount, debugModeMines);

                                    continue;
                                }
                            }
                        }

                        if (winCount == (tileCount - mineCount))
                        {
                            yaWon = true;

                            continue;
                        }

                        //Debug Button
                        if (event.mouseButton.x >= width - 256 && event.mouseButton.x < width - 192)
                        {
                            if (event.mouseButton.y >= height - 88 && event.mouseButton.y < height)
                            {
                                if (debugMode)
                                {
                                    debugMode = false;
                                }

                                else
                                {
                                    debugMode = true;
                                }

                                continue;
                            }
                        }

                        //width - 384, height - 88

                        tempIndexes = SearchForTile(board, event.mouseButton.x, event.mouseButton.y);

                        if (printMine || yaWon)
                        {
                            //Do nothing, game's over.
                        }

                        if (board.Tiles.at(tempIndexes.at(0)).at(tempIndexes.at(1)).hasFlag)
                        {
                            //Do nothing

                            //int index = SearchForFlag(board, tempIndexes, flagSprites); Don't need this anymore

                            //setTextures(board, revealedTile, tempIndexes);

                            //See why the hasFlag isn't being true make sure it is set to be true somehow in the right click event
                        }

                        else
                        {
                            setTextures(board, revealedTile, tempIndexes);

                            board.Tiles.at(tempIndexes.at(0)).at(tempIndexes.at(1)).isRevealed = true;

                            if (board.Tiles.at(tempIndexes.at(0)).at(tempIndexes.at(1)).hasMine)
                            {
                                temp = setTextures(board, tempIndexes, mine);

                                mineSprites.push_back(temp);

                                printMine = true;
                            }

                            else
                            {
                                winCount++;

                                tilesWith0Prox.clear();

                                int countMine = board.Tiles.at(tempIndexes.at(0)).at(tempIndexes.at(1)).proxMines;

                                tilesWith0Prox.push_back(board.Tiles.at(tempIndexes.at(0)).at(tempIndexes.at(1)));

                                //using if/else instead of switch since while loop is acting funny in switch statement

                                //cout << board.Tiles.at(0).at(5).tileSprite.getPosition().x << "  " << board.Tiles.at(0).at(5).tileSprite.getPosition().y << endl;

                                if (countMine == 0)
                                {
                                    int sizeCount = 1;

                                    for (int i = 0; i < sizeCount; i++)
                                    {
                                        for (int j = 0; j < tilesWith0Prox.at(i).adjacentTiles.size(); j++)
                                        {
                                            if (tilesWith0Prox.at(i).adjacentTiles.at(j) == nullptr)
                                            {
                                                continue;
                                            }

                                            else if (tilesWith0Prox.at(i).adjacentTiles.at(j)->isRevealed)
                                            {
                                                continue;
                                            }

                                            else if (tilesWith0Prox.at(i).adjacentTiles.at(j)->hasFlag)
                                            {
                                                continue;
                                            }

                                            else
                                            {
                                                indexess = SearchForTile(board, tilesWith0Prox.at(i).adjacentTiles.at(j)->tileSprite.getPosition().x, tilesWith0Prox.at(i).adjacentTiles.at(j)->tileSprite.getPosition().y);

                                                winCount++;

                                                setTextures(board, revealedTile, indexess);

                                                board.Tiles.at(indexess.at(0)).at(indexess.at(1)).isRevealed = true;

                                                int proxMines = tilesWith0Prox.at(i).adjacentTiles.at(j)->proxMines;

                                                if (proxMines == 0)
                                                {
                                                    tilesWith0Prox.push_back(board.Tiles.at(indexess.at(0)).at(indexess.at(1)));

                                                    sizeCount++;
                                                }

                                                else if (proxMines == 1)
                                                {
                                                    temp = setTextures(board, indexess, numOne);

                                                }

                                                else if (proxMines == 2)
                                                {
                                                    temp = setTextures(board, indexess, numTwo);

                                                }

                                                else if (proxMines == 3)
                                                {
                                                    temp = setTextures(board, indexess, numThree);

                                                }

                                                else if (proxMines == 4)
                                                {
                                                    temp = setTextures(board, indexess, numFour);

                                                }

                                                else if (proxMines == 5)
                                                {
                                                    temp = setTextures(board, indexess, numFive);

                                                }

                                                else if (proxMines == 6)
                                                {
                                                    temp = setTextures(board, indexess, numSix);

                                                }

                                                else if (proxMines == 7)
                                                {
                                                    temp = setTextures(board, indexess, numSeven);

                                                }

                                                else if (proxMines == 8)
                                                {
                                                    temp = setTextures(board, indexess, numEight);

                                                }

                                            }
                                            proxNumSprites.push_back(temp);
                                        }

                                        //tilesWith0Prox.erase(tilesWith0Prox.begin());
                                    }
                                }

                                else if (countMine == 1)
                                {
                                    temp = setTextures(board, tempIndexes, numOne);
                                }

                                else if (countMine == 2)
                                {
                                    temp = setTextures(board, tempIndexes, numTwo);
                                }

                                else if (countMine == 3)
                                {
                                    temp = setTextures(board, tempIndexes, numThree);
                                }

                                else if (countMine == 4)
                                {
                                    temp = setTextures(board, tempIndexes, numFour);
                                }

                                else if (countMine == 5)
                                {
                                    temp = setTextures(board, tempIndexes, numFive);
                                }

                                else if (countMine == 6)
                                {
                                    temp = setTextures(board, tempIndexes, numSix);
                                }

                                else if (countMine == 7)
                                {
                                    temp = setTextures(board, tempIndexes, numSeven);
                                }

                                else if (countMine == 8)
                                {
                                    temp = setTextures(board, tempIndexes, numEight);
                                }

                                proxNumSprites.push_back(temp);
                            }
                        }
                    }

                    else if (event.mouseButton.button == Mouse::Right)
                    {
                        if (printMine || yaWon)
                        {
                            //Do nothing again, game's over.

                            continue;
                        }

                        check = true;

                        tempIndexes = SearchForTile(board, event.mouseButton.x, event.mouseButton.y);

                        temp = setTextures(board, tempIndexes, flagT);

                        remove = CheckForCopies(temp, flagSprites);

                        checkIfRevealed = CheckIfRevealed(temp, board);

                        if (remove)
                        {
                            mineCount++;

                            board.Tiles.at(tempIndexes.at(0)).at(tempIndexes.at(1)).hasFlag = false;

                            bool dontNeed = CheckForCopies(temp, flagSprites);

                            //Do nothing which is perfect
                        }

                        else if (checkIfRevealed)
                        {
                            board.Tiles.at(tempIndexes.at(0)).at(tempIndexes.at(1)).hasFlag = false;

                            bool dontNeed = CheckForCopies(temp, flagSprites);
                        }

                        else
                        {
                            mineCount--;

                            flagSprites.push_back(temp);

                            board.Tiles.at(tempIndexes.at(0)).at(tempIndexes.at(1)).hasFlag = true;
                        }
                    }
                    break;
                default:
                    break;
            }


            for (const auto& x : flagSprites)
            {
                window.draw(x);
            }


            window.draw(smileySprite);

            if (printMine)
            {
                for (int i = 0; i < board.Tiles.size(); i++)
                {
                    for (int j = 0; j < board.Tiles.at(i).size(); j++)
                    {
                        if (board.Tiles.at(i).at(j).hasMine)
                        {
                            board.Tiles.at(i).at(j).isRevealed = true;

                            board.Tiles.at(i).at(j).tileSprite.setTexture(revealedTile);

                            vector<int> tempIndex;

                            tempIndex.push_back(i);

                            tempIndex.push_back(j);

                            temp = setTextures(board, tempIndex, mine);

                            mineSprites.push_back(temp);
                        }
                    }
                }

                for (const auto& x: mineSprites)
                {
                    window.draw(x);
                }

                window.draw(xFaceSprite);
            }

            if (yaWon)
            {
                for (int i = 0; i < board.Tiles.size(); i++)
                {
                    for (int j = 0; j < board.Tiles.at(i).size(); j++)
                    {
                        if (board.Tiles.at(i).at(j).hasMine)
                        {
                            board.Tiles.at(i).at(j).isRevealed = false;

                            //board.Tiles.at(i).at(j).tileSprite.setTexture(revealedTile);

                            vector<int> tempIndex;

                            tempIndex.push_back(i);

                            tempIndex.push_back(j);

                            temp = setTextures(board, tempIndex, flagT);

                            flagOverMines.push_back(temp);
                        }
                    }
                }

                for (const auto& x: flagOverMines)
                {
                    window.draw(x);
                }

                window.draw(shadeFace);
            }

            if (debugMode)
            {
                for (int i = 0; i < board.Tiles.size(); i++)
                {
                    for (int j = 0; j < board.Tiles.at(i).size(); j++)
                    {
                        if (board.Tiles.at(i).at(j).hasMine)
                        {
                            board.Tiles.at(i).at(j).isRevealed = false;

                            //board.Tiles.at(i).at(j).tileSprite.setTexture(revealedTile);

                            vector<int> tempIndex;

                            tempIndex.push_back(i);

                            tempIndex.push_back(j);

                            temp = setTextures(board, tempIndex, mine);

                            debugModeMines.push_back(temp);
                        }
                    }
                }

                for (auto& x : debugModeMines)
                {
                    window.draw(x);
                }

                window.draw(smileySprite);

            }

            mineCountSprites = SetDigitRect(height, width, digitZero, digitOne, digitTwo, digitThree, digitFour, digitFive, digitSix, digitSeven, digitEight, digitNine, negativeSign, mineCount);

            for (auto& x : mineCountSprites)
            {
                window.draw(x);
            }

            for (const auto& x : proxNumSprites)
            {
                window.draw(x);
            }

            window.display();
        }

    }

    return 0;
}

/*
int SearchForFlag(Board& board, vector<int>& indexes, vector<Sprite>& flags)
{
    Vector2f vectorTile = board.Tiles.at(indexes.at(0)).at(indexes.at(1)).tileSprite.getPosition();

    Vector2f compareVector;

    for (int i = 0; i < flags.size(); i++)
    {
        compareVector = flags.at(i).getPosition();

        if (vectorTile.x == compareVector.x)
        {
            if (vectorTile.y == compareVector.y)
            {
                return i;
            }
        }
    }

    return 0;
}
*/

//Don't need this anymore

/*
bool RevealingLoop(Board& board, Tile tile, vector<Sprite>& proxNumSprites, Texture& revealedTile, Texture& numOne, Texture& numTwo, Texture& numThree, Texture& numFour, Texture& numFive, Texture& numSix, Texture& numSeven, Texture& numEight)
{
    vector<int> indexes;

    vector<Tile> tiles;

    tiles.push_back(tile);

    Sprite temp;

    bool changeTile = false;

    for (int i = 0; i < tiles.size(); i++)
    {
        Tile tileTemp = tiles.at(i);

        for (int j = 0; j < tileTemp.adjacentTiles.size(); j++)
        {
            if (tileTemp.adjacentTiles.at(j) == nullptr)
            {

            }

            else
            {
                indexes = SearchForTile(board, tileTemp.adjacentTiles.at(j)->tileSprite.getPosition().x, tileTemp.adjacentTiles.at(j)->tileSprite.getPosition().y);

                setTextures(board, revealedTile, indexes);

                switch(tileTemp.adjacentTiles.at(j)->proxMines)
                {
                    case 0:
                        changeTile = true;
                        break;
                    case 1:
                        temp = setTextures(board, indexes, numOne);
                        break;
                    case 2:
                        temp = setTextures(board, indexes, numTwo);
                        break;
                    case 3:
                        temp = setTextures(board, indexes, numThree);
                        break;
                    case 4:
                        temp = setTextures(board, indexes, numFour);
                        break;
                    case 5:
                        temp = setTextures(board, indexes, numFive);
                        break;
                    case 6:
                        temp = setTextures(board, indexes, numSix);
                        break;
                    case 7:
                        temp = setTextures(board, indexes, numSeven);
                        break;
                    case 8:
                        temp = setTextures(board, indexes, numEight);
                        break;
                }

                proxNumSprites.push_back(temp);
            }
        }
    }


    if (changeTile)
    {

        RevealingLoop(board, )
    }

    else
    {
        return false;
    }
}
*/

/*

                                if (countMine == 0)
                                {
                                    for (int i = 0; i < tilesWith0Prox.size(); i++)
                                    {
                                        cout << "Starting the loop " << endl;

                                        exitCall = false;

                                        Tile x = tilesWith0Prox.at(i);

                                        for (int j = 0; j < x.adjacentTiles.size(); j++)
                                        {
                                            if (x.adjacentTiles.at(j) == nullptr)
                                            {
                                                continue;
                                            }

                                            else
                                            {
                                                indexess = SearchForTile(board, x.adjacentTiles.at(j)->tileSprite.getPosition().x, x.adjacentTiles.at(j)->tileSprite.getPosition().y);

                                                setTextures(board, revealedTile, indexess);

                                                switch(x.adjacentTiles.at(j)->proxMines)
                                                {
                                                    case 0:
                                                        tempTile = board.Tiles.at(indexess.at(0)).at(indexess.at(1));

                                                        tilesWith0Prox.push_back(tempTile);

                                                        exitCall = true;
                                                        break;
                                                    case 1:
                                                        temp = setTextures(board, indexess, numOne);
                                                        break;
                                                    case 2:
                                                        temp = setTextures(board, indexess, numTwo);
                                                        break;
                                                    case 3:
                                                        temp = setTextures(board, indexess, numThree);
                                                        break;
                                                    case 4:
                                                        temp = setTextures(board, indexess, numFour);
                                                        break;
                                                    case 5:
                                                        temp = setTextures(board, indexess, numFive);
                                                        break;
                                                    case 6:
                                                        temp = setTextures(board, indexess, numSix);
                                                        break;
                                                    case 7:
                                                        temp = setTextures(board, indexess, numSeven);
                                                        break;
                                                    case 8:
                                                        temp = setTextures(board, indexess, numEight);
                                                        break;
                                                }
                                            }

                                                proxNumSprites.push_back(temp);
                                        }

                                        if (exitCall)
                                        {
                                            continue;
                                        }

                                        else
                                        {
                                            break;
                                        }
                                    }
                                }

                                else if (countMine == 1)
                                {
                                    temp = setTextures(board, tempIndexes, numOne);
                                }

                                else if (countMine == 2)
                                {
                                    temp = setTextures(board, tempIndexes, numTwo);
                                }

                                else if (countMine == 3)
                                {
                                    temp = setTextures(board, tempIndexes, numThree);
                                }

                                else if (countMine == 4)
                                {
                                    temp = setTextures(board, tempIndexes, numFour);
                                }

                                else if (countMine == 5)
                                {
                                    temp = setTextures(board, tempIndexes, numFive);
                                }

                                else if (countMine == 6)
                                {
                                    temp = setTextures(board, tempIndexes, numSix);
                                }

                                else if (countMine == 7)
                                {
                                    temp = setTextures(board, tempIndexes, numSeven);
                                }

                                else if (countMine == 8)
                                {
                                    temp = setTextures(board, tempIndexes, numEight);
                                }

                                proxNumSprites.push_back(temp);

                                 */


/*
for (auto& x : board.Tiles.at(tempIndexes.at(0)).at(tempIndexes.at(1)).adjacentTiles)
{
    if (x == nullptr)
    {

    }

    else
    {
        if (x->proxMines == 0)
        {
            Tile
            anyLeftZero = true;
        }

        indexess = SearchForTile(board, x->tileSprite.getPosition().x, x->tileSprite.getPosition().y);

        setTextures(board, revealedTile, indexess);
    }
}

if (anyLeftZero)
{
    continue;
}

else
{
    break;
}
 */

//Moved this trial out of the way for now
/*
   while(true)
   {
       while(true)
       {
           tileSprite.setPosition(x_pos, y_pos);

           window.draw(tileSprite);

           count++;

           if (count == width/32)
           {
               break;
           }
       }

       outerCount++;

       if (outerCount == (height - 88) / 32)
       {
           break;
       }
   }
   */


/*
switch (countMine)
{
    case 0:

        bool anyLeftZero = false;

        while (true)
        {
            for (auto& x : board.Tiles.at(tempIndexes.at(0)).at(tempIndexes.at(1)).adjacentTiles)
            {
                if (x == nullptr)
                {

                }

                else
                {
                    if (x->proxMines == 0)
                    {
                        anyLeftZero = true;
                    }

                    indexess = SearchForTile(board, x->tileSprite.getPosition().x, x->tileSprite.getPosition().y);

                    setTextures(board, revealedTile, indexess);
                }
            }

            if (anyLeftZero)
            {
                continue;
            }

            else
            {
                break;
            }
        }



        break;

    case 1:
        temp = setTextures(board, tempIndexes, numOne);
        break;
    case 2:
        temp = setTextures(board, tempIndexes, numTwo);
        break;
    case 3:
        temp = setTextures(board, tempIndexes, numThree);
        break;
    case 4:
        temp = setTextures(board, tempIndexes, numFour);
        break;
    case 5:
        temp = setTextures(board, tempIndexes, numFive);
        break;
    case 6:
        temp = setTextures(board, tempIndexes, numSix);
        break;
    case 7:
        temp = setTextures(board, tempIndexes, numSeven);
        break;
    case 8:
        temp = setTextures(board, tempIndexes, numEight);
        break;
    default:
        break;
}

*/

/*
int main()
{
    cout << "We started up in here" << endl;

    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    cout << "We eneded out here." << endl;

    return 0;
}
*/

/*


int lastDigit = 0;

while (mineCount != 0)
{
lastDigit = mineCount % 10;

mineCount /= 10;

//using if/else statements since I don't trust switch statements anymore, they act funny at times.

if (lastDigit == 1)
{
countDigits.push_back(one);
}

else if (lastDigit == 2)
{
countDigits.push_back(two);
}

else if (lastDigit == 3)
{
countDigits.push_back(three);
}

else if (lastDigit == 4)
{
countDigits.push_back(four);
}

else if (lastDigit == 5)
{
countDigits.push_back(five);
}

else if (lastDigit == 6)
{
countDigits.push_back(six);
}

else if (lastDigit == 7)
{
countDigits.push_back(seven);
}

else if (lastDigit == 8)
{
countDigits.push_back(eight);
}

else if (lastDigit == 9)
{
countDigits.push_back(nine);
}

else if (lastDigit == 0)
{
countDigits.push_back(zero);
}

}
*/