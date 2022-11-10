#include <iostream>
#include <iomanip>
#include <random>

using namespace std;

const int
    N = 9,
    D = 10;


bool canSlideL(int board[][4]) {

    // for each row r {
    for (int row=0;row<4;row++) {

        // for col = 3,2,1 {
        for (int col=3;col>0;col--) {

            // if board[row][col] == 0 nothing to move left so onto next loop
            if (board[row][col] == 0)
                continue;
            // if board[row][col] == board[row][col-1] return true
            if(board[row][col] == board[row][col-1])
                return true;
            // if board[row][col-1] == 0 return true
            if(board[row][col-1] == 0)
                return true;
            // end col loop
        }

        // end row loop
    }

    // return false, can't slide left
    return false;
}

bool canSlideR(int board[][4]) {

    // for each row r {
    for(int row = 0; row < 4; row++)
    {
        // for col = 0,1,2 {
        for(int col = 0; col < 3; col++)
        {
            // if board[row][col] == 0 continue, nothing to move right
            if(board[row][col] == 0)
                continue;
            // if board[row][col] == board[row][col+1] return true
            if(board[row][col] == board[row][col+1])
                return true;
            // if board[row][col+1] == 0 return true
            if(board[row][col+1] == 0)
                return true;
            // end col loop
        }
        // end row loop
    }
    //Return false, cant slide right
    return false;
}

bool canSlideU(int board[][4]) {

    //scans columns
    for(int col = 0; col < 4; col++)
    {
        //Checks from bottom to top
        for(int row = 3; row > 0; row--)
        {
            // If board[row][col] = 0 onto next loop, nothing to move up
            if(board[row][col] == 0)
                continue;
            // if board[row][col] == board[row-1][col] return true
            if(board[row][col] == board[row - 1][col])
                return true;
            // if board[row+1][col] == 0 return true
            if(board[row-1][col] == 0)
                return true;
            // end row loop
        }
        // end col loop
    }
    //Return false, cant slide right
    return false;
}

bool canSlideD(int board[][4]) {

    //scans columns
    for(int col = 0; col < 4; col++)
    {
        // Scans row top to bottom
        for(int row = 0; row < 3; row++)
        {
            // if board[row][col] == 0 continue, nothing to move down
            if(board[row][col] == 0)
                continue;
            // if value below current location equals current value return true
            if(board[row][col] == board[row+1][col])
                return true;
            // if board[row+1][col] == 0 return true
            if(board[row+1][col] == 0)
                return true;
            // end row loop
        }
        // end col loop
    }
    //Return false, cant slide right
    return false;
}

void slideL(int board[][4],int &score) {
    //Moves each item in each column to the left most position possible
    for(int i = 0; i<3; i++) {
        for(int row=0;row<4;row++) {
            //Moves each item to left until it cant move left anymore
            for (int col=3;col>0;col--) {
                //If true no value to move left
                 if(board[row][col] == 0)
                    continue;
                // if board[row][col - 1] == 0 move board[row][col] to that position
                if(board[row][col - 1] == 0) {
                    board[row][col - 1] = board[row][col];
                    board[row][col] = 0;
                }
            }
        }
    }


    //Merges adjacent similar values left to right
    for (int row =0;row<4;row++) {

        //Scans left to right merging or moving to left
        for (int col = 0; col < 3; col++) {
            // If square is 0 begin check of next value
            if (board[row][col] == 0)
                continue;
                //Check if current square equals value of square to right
            if (board[row][col] == board[row][col + 1]) {
                score += board[row][col] = board[row][col] + board[row][col + 1];
                board[row][col + 1] = 0;
            }
            // end col loop
        }
        // end row loop
    }
    //Moves each item in each column to the left most position possible
    for(int row=0;row<4;row++) {
        //Moves each item to left until it cant move left anymore
        for (int col=3;col>0;col--) {
            //If true no value to move left
            if(board[row][col] == 0)
                continue;
            // if board[row][col - 1] == 0 move board[row][col] to that position
            if(board[row][col - 1] == 0) {
                board[row][col - 1] = board[row][col];
                board[row][col] = 0;
            }
        }
    }
}

void slideR(int board[][4],int &score) {
    for(int i = 0; i<3; i++) {
        //Moves each item in each column to the right most position possible
        for(int row=0;row<4;row++) {
            //Moves each item to right until it cant move right anymore
            for (int col=0;col<3;col++) {
                //If true no value to move right
                if(board[row][col] == 0)
                    continue;
                // if board[row][col + 1] == 0 move board[row][col] to that position
                if(board[row][col + 1] == 0){
                    board[row][col + 1] = board[row][col];
                    board[row][col] = 0;
                }
            }
        }
    }

    //Merges adjacent similar values right to left
    for (int row =0;row<4;row++) {

        //Scans right to left merging or moving to right
        for (int col = 3; col > 0; col--) {

            // If square is 0 begin check of next value
            if (board[row][col] == 0)
                continue;

                //Check if current square equals value of square to left
                if (board[row][col] == board[row][col - 1]) {
                score += board[row][col] = board[row][col] + board[row][col - 1];
                board[row][col - 1] = 0;
            }
            // end col loop
        }
        // end row loop
    }
    //Moves each item in each column to the right most position possible
    for(int row=0;row<4;row++) {
        //Moves each item to right until it cant move right anymore
        for (int col=0;col<3;col++) {
            //If true no value to move right
            if(board[row][col] == 0)
                continue;
            // if board[row][col + 1] == 0 move board[row][col] to that position
            if(board[row][col + 1] == 0){
                board[row][col + 1] = board[row][col];
                board[row][col] = 0;
            }
        }
    }
}

void slideU(int board[][4],int &score) {
    //Moves each value up to the top
    for(int i = 0; i<3; i++) {
        for(int col=0;col<4;col++) {
            //Moves each item up until it cant move up anymore
            for (int row=3;row>0;row--) {
                //If true no value to move up
                if(board[row][col] == 0)
                    continue;
                // if board[row-1][col] == 0 move board[row][col] to that position
                if(board[row-1][col] == 0) {
                    board[row-1][col] = board[row][col];
                    board[row][col] = 0;
                }
            }
        }
    }

    //Merges adjacent similar values up from bottom
    for (int col=0;col<4;col++) {

        //Scans upwards merging or moving down
        for (int row = 0; row < 3; row++) {
            // If square is 0 begin check of next value
            if (board[row][col] == 0)
                continue;

                //Check if current square equals value of square below
            if (board[row][col] == board[row + 1][col]) {
                score += board[row][col] = board[row][col] + board[row+1][col];
                board[row+1][col] = 0;
            }
            // end col loop
        }
        // end row loop
    }
    //Moves each value up to the top
    for(int col=0;col<4;col++) {
        //Moves each item up until it cant move up anymore
        for (int row=3;row>0;row--) {
            //If true no value to move up
            if(board[row][col] == 0)
                continue;
            // if board[row-1][col] == 0 move board[row][col] to that position
            if(board[row-1][col] == 0) {
                board[row-1][col] = board[row][col];
                board[row][col] = 0;
            }
        }
    }
}

void slideD(int board[][4],int &score) {
    //Moves each value down to the bottom
    for(int i = 0; i<3; i++) {
        for(int col=0;col<4;col++) {
            //Moves each item up until it cant move down anymore
            for (int row=0;row<3;row++) {
                //If true no value to move down
                if(board[row][col] == 0)
                    continue;
                // if board[row+1][col] == 0 move board[row][col] to that position
                if(board[row+1][col] == 0) {
                    board[row+1][col] = board[row][col];
                    board[row][col] = 0;
                }
            }
        }
    }


    //Merges adjacent similar values down from top
    for (int col=0;col<4;col++) {

        //Scans bottom to top merging or moving to bottom
        for (int row = 3; row > 0; row--) {

            // If square is 0 begin check of next value
            if (board[row][col] == 0)
                continue;

                //Check if current square equals value of square above
            if (board[row][col] == board[row - 1][col]) {
                score += board[row][col] = board[row][col] + board[row-1][col];
                board[row-1][col] = 0;
            }
            // end col loop
        }
        // end row loop
    }
    //Moves each value down to the bottom
    for(int col=0;col<4;col++) {
        //Moves each item up until it cant move down anymore
        for (int row=0;row<3;row++) {
            //If true no value to move down
            if(board[row][col] == 0)
                continue;
            // if board[row+1][col] == 0 move board[row][col] to that position
            if(board[row+1][col] == 0) {
                board[row+1][col] = board[row][col];
                board[row][col] = 0;
            }
        }
    }
}

void fillCell(int board[][4]) {
    int
        row,col,
        n=0,
        randVal;
    random_device
        rd;
    mt19937
        mt(rd());

    // count empty squares (n)
    for (row=0;row<4;row++)
        for (col=0;col<4;col++)
            if (board[row][col] == 0)
                n++;

    // choose random number between 1 and n
    uniform_int_distribution
        dis1(1,n);

    randVal = dis1(mt);

    row = col = 0;
    // scan board, while randVal > 0
    while (true) {

        // if cell is empty, subtract 1 from randVal
        if (board[row][col] == 0)
            randVal--;

        // if randVal == 0, break
        if (randVal == 0)
            break;

        // move to next cell
        col++;
        if (col == 4) {
            row++;
            col = 0;
        }
    }

    // choose random number from 1 to D
    uniform_int_distribution
        dis2(1,D);

    randVal = dis2(mt);

    // if randVal > N, fill cell with 4, else fill cell with 2
    if(randVal > N)
    {
        board[row][col] = 4;
    } else {
        board[row][col] = 2;
    }
}

void displayBoard(int board[][4],int score) {

    cout << "\033[2J\033[H";    // clear screen

    cout << "Score: " << score << endl; // show score

    // loop over all rows
    for (int r=0;r<4;r++) {
        // top border plus top space
        cout << "+--------+--------+--------+--------+\n"
                "|        |        |        |        |" << endl;
        // output each column
        for (int c=0;c<4;c++)
            if (board[r][c] != 0)
                cout << "| " << setw(6) << board[r][c] << ' ';
            else
                cout << "|        ";
        // bottom space
        cout << "|\n|        |        |        |        |" << endl;
    }

    // bottom border
    cout << "+--------+--------+--------+--------+" << endl;
}

int main() {
    int
        board[4][4] = {0},
        score = 0;
    string
        moves;
    char
        ch;

    // initialize the game board
    fillCell(board);
    fillCell(board);
    // do {
    do {

        displayBoard(board,score);

        // check for slide directions
        moves = "";
        if (canSlideU(board))
            moves += 'u';
        if (canSlideD(board))
            moves += 'd';
        if (canSlideL(board))
            moves += 'l';
        if (canSlideR(board))
            moves += 'r';

        // if no slides available, break
        if (moves == "")
            break;

        // get a move
        cout << "Enter move [q" << moves << "]: ";
        cin >> ch;

        // apply move
        if (ch == 'u' && canSlideU(board))
            slideU(board,score);
        if (ch == 'l' && canSlideL(board))
            slideL(board,score);
        if (ch == 'r' && canSlideR(board))
            slideR(board,score);
        if (ch == 'd' && canSlideD(board))
            slideD(board,score);
        fillCell(board);

        // } end loop
    } while (ch != 'q' && ch != 'Q');

    // show final score
    cout << "Final score: " << score << endl;

    return 0;
}
