#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <time.h>

#define numRows 4
#define numColumns 4

using namespace std;
void displayBoard(int board[numColumns][numRows]);
bool canSlideL(int board[numColumns][numRows]);
bool canSlideR(int board[numColumns][numRows]);
bool canSlideU(int board[numColumns][numRows]);
bool canSlideD(int board[numColumns][numRows]);
void slideLeft(int board[numColumns][numRows]);
void slideRight(int board[numColumns][numRows]);
void slideUp(int board[numColumns][numRows]);
void slideDown(int board[numColumns][numRows]);
void generateRandom2or4(int board[numColumns][numRows]);

int main()
{
    bool
        canMoveL,
        canMoveR,
        canMoveU,
        canMoveD;
    char
        input = 0;
    int
        board[numColumns][numRows] = {0};
    //generate 2 or 4 twice
    generateRandom2or4(board);
    generateRandom2or4(board);
    //do loop for main game loop
    do
    {
        displayBoard(board);
        //check for slide directions
        //if no slides break loop
        //get a move u d l r
        //apply move
    } while(1);
    //End loop
    //show final score. Final score = sum of any merging
    return 0;
}
void generateRandom2or4 (int board[numColumns][numRows])
{
    int
        columnNum = 0,
        rowNum = 0,
        multFactor = 0;
    //Sets a random seed for column and row number generation
    srand(time(NULL));
    do
    {
        columnNum = rand()%4;
        rowNum = rand()%4;
        //Checks if selected column and row value are 0
        if (board[columnNum][rowNum] == 0)
        {
            //Generates a random number (0, 1) adds one and multiplies by two to get two or four randomly
            multFactor = (rand()%2 + 1) * 2;
            board[columnNum][rowNum] = multFactor;
            break;
        }
    } while (1);
}

void displayBoard(int board[numColumns][numRows])
{
    for (int j = 0; j < numRows; j++)
    {
        //Prints top line of box
        for (int i = 0; i < numColumns; i++)
        {
            cout << "_______";
        }
        cout << endl;
        //Prints middle of box
        for(int i = 0; i < numColumns; i++)
        {
            cout << '|' << setw(3) << board[i][j] << setw(3) << '|';
        }
        cout << endl;
        //Prints bottom of box
        for(int i = 0; i < numColumns; i++)
        {
            cout << "|_____|";
        }
        cout << endl;
    }
}