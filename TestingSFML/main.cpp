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

    for (int i = 0; i < sprites.size(); i++)
    {
        vector = sprites.at(i).getPosition();

        if (sprites.at(i).getPosition() == check.getPosition())
        {
            sprites.erase(sprites.begin() + i);

            return true;
        }
    }

    return false;
}

bool CheckIfRevealed(Sprite& sprite, Board& board, Texture& revealed)
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
                    if (board.Tiles.at(i).at(j).tileSprite.getTexture() == &revealed)
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

    //End of reading data



    //The numbers in the video mode function arguments are by pixels, not any other units

    RenderWindow window (VideoMode(width, height), "The window for now");

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

    smileySprite.setPosition(width - 384, height - 88);

    Sprite xFaceSprite;

    xFaceSprite.setTexture(xFace);

    xFaceSprite.setPosition(width - 384, height - 88);

    Sprite debugS;

    debugS.setTexture(debugT);

    debugS.setPosition(width - 256, height - 88);

    Sprite testoneS;

    testoneS.setTexture(testone);

    testoneS.setPosition(width - 192, height - 88);

    Sprite testTwo;

    testTwo.setTexture(testtwo);

    testTwo.setPosition(width - 128, height - 88);

    Sprite testThree;

    testThree.setTexture(testthree);

    testThree.setPosition(width - 64, height - 88);

    Sprite numOneSprite;

    numOneSprite.setTexture(numOne);

    Sprite numTwoSprite;

    numTwoSprite.setTexture(numTwo);

    Sprite numThreeSprite;

    numThreeSprite.setTexture(numThree);

    Sprite numFourSprite;

    numFourSprite.setTexture(numFour);

    Sprite numFiveSprite;

    numFiveSprite.setTexture(numFive);

    Sprite numSixSprite;

    numSixSprite.setTexture(numSix);

    Sprite numSevenSprite;

    numSevenSprite.setTexture(numSeven);

    Sprite numEightSprite;

    numEightSprite.setTexture(numEight);


    //Lots of texture and sprites here

    float x_pos = 0;

    float y_pos = 0;

    int widthCalc = (width / 32) - 1;

    int heightCalc = ((height - 88) / 32) - 1;

    for (int i = 0; i < heightCalc + 1; i++)
    {
        for (int j = 0; j < widthCalc + 1; j++)
        {
            board.Tiles.at(i).at(j).tileSprite.setTexture(tile);

            board.Tiles.at(i).at(j).tileSprite.setPosition(x_pos, y_pos);

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

    //Working through the board's Tiles vector and setting the positions of each to make sense. Also doing it here to avoid issues with the texture pointers and whatnot

    vector<int> tempIndexes;

    bool check = false;

    bool printMine = false;

    bool remove = false;

    bool checkIfRevealed = false;

    Sprite temp;

    vector<Sprite> flagSprites;

    vector<Sprite> mineSprites;

    SetRandomMines(board, height, width, mineCount);

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


            window.draw(debugS);

            window.draw(testoneS);

            window.draw(testTwo);

            window.draw(testThree);

            switch (event.type)
            {
                case Event::Closed:
                    cout << "We closed " << endl;
                    window.close();
                    break;
                case Event::KeyPressed:
                    break;
                case Event::MouseButtonPressed:
                    if (event.mouseButton.button == Mouse::Left)
                    {
                        tempIndexes = SearchForTile(board, event.mouseButton.x, event.mouseButton.y);

                        if (board.Tiles.at(tempIndexes.at(0)).at(tempIndexes.at(1)).hasFlag)
                        {
                            //int index = SearchForFlag(board, tempIndexes, flagSprites); Don't need this anymore

                            //setTextures(board, revealedTile, tempIndexes);

                            //See why the hasFlag isn't being true make sure it is set to be true somehow in the right click event
                        }

                        else
                        {
                            setTextures(board, revealedTile, tempIndexes);

                            if (board.Tiles.at(tempIndexes.at(0)).at(tempIndexes.at(1)).hasMine)
                            {
                                temp = setTextures(board, tempIndexes, mine);

                                mineSprites.push_back(temp);

                                printMine = true;
                            }
                        }
                    }

                    else if (event.mouseButton.button == Mouse::Right)
                    {
                        check = true;

                        tempIndexes = SearchForTile(board, event.mouseButton.x, event.mouseButton.y);

                        temp = setTextures(board, tempIndexes, flagT);

                        remove = CheckForCopies(temp, flagSprites);

                        checkIfRevealed = CheckIfRevealed(temp, board, revealedTile);

                        if (remove || checkIfRevealed)
                        {
                            board.Tiles.at(tempIndexes.at(0)).at(tempIndexes.at(1)).hasFlag = false;

                            //Do nothing which is perfect
                        }

                        else
                        {
                            flagSprites.push_back(temp);
                            board.Tiles.at(tempIndexes.at(0)).at(tempIndexes.at(1)).hasFlag = true;
                        }
                    }
                    break;
                default:
                    break;
            }

            if (check)
            {
                for (const auto& x : flagSprites)
                {
                    window.draw(x);
                }
            }

            else if (printMine)
            {
                for (const auto& x: mineSprites)
                {
                    window.draw(x);
                }

                window.draw(xFaceSprite);
            }

            else
            {
                window.draw(smileySprite);
            }

            window.display();
        }

    }

    return 0;

}


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