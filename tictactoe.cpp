//Tic Tac Toe AI
//Carson Miller

#include <iostream>
#include <cmath>
#include <string>
#include <conio.h>
#include <stdlib.h>
#include <ctime>

using namespace std;

const int RMAX = 3;
const int CMAX = 3;
int turn = 0;
const char empty = '-', me = 'X', you = 'O';

void printBoard(char board[RMAX][CMAX]);
int mustBlockWin(char board[][CMAX], char player);
void boardIn(char board[][CMAX], char mark);
void boardManual(char board[][CMAX]);
bool winDetect(char board[][CMAX], char player);
void compMove(char board[][CMAX], int cell);
int numWin(char board[][CMAX], int row, int column, char player);
int moveSelect(char board[][CMAX]);

int main()
{
    system("CLS");

    char cont = 'y';
    while(cont == 'y' || cont == 'Y')
    {
        char board[RMAX][CMAX];
        char yn;
        boardIn(board, empty);

        /*cout << "Manual board Entry? (y/n): ";
        cin >> yn;
        if(yn == 'y' || yn == 'Y')
            boardManual(board);*/

        char moveFirst;

        cout << "Who will go first? (m for me, c for computer):";
        cin >> moveFirst;
        if(moveFirst == 'c')
            cout << "The computer will go first.\n";
        cout << endl;
        turn = 0;

        /*if(moveFirst == 'r')
        {
            double decide = (static_cast<double>(rand()))/(RAND_MAX+1);
            cout << decide << endl;
            if(decide > .5)
            {
                moveFirst = 'm';
                cout << "You will go first.\n\n";
            }
            else
            {
                moveFirst = 'c';
                cout << "The computer will go first.\n\n";
            }
        }*/

        int rtemp = 0, ctemp = 0;

        while(turn<9)
        {
            if(turn != 0 || moveFirst == 'm' || moveFirst == 'M')
            {
                cout << "It is your turn\n\n";
                printBoard(board);
                cout << "\nEnter the row and column for your move: ";

                while(true)
                {
                    cin >> rtemp >> ctemp;
                    rtemp--;
                    ctemp--;

                    if(board[rtemp][ctemp] == empty)
                        {
                            board[rtemp][ctemp] = me;
                            break;
                        }
                    else cout << "\nSomeone has already played there\n\n";
                    cout << "It is your turn\nEnter a different row and column for your move: ";
                }

                turn++;
                system("CLS");
            }

            if(turn >= 9)
            {
                cout << "\nTHE GAME ENDED IN A DRAW.\n\n";
                printBoard(board);
                cout << "Play again? (y/n)";
                cin >> cont;
                cout << "\n\n\n";
                turn = 9;
                continue;
            }

            if(winDetect(board, me)) //checks if the user just won with its last move
                {
                    cout << "Play again? (y/n)";
                    cin >> cont;
                    cout << "\n\n\n";
                    turn = 9;
                    continue;
                }

            if(moveSelect(board) == 1) //calls moveSelect and if the computer wins with its move, calls winDetect and ends the game
                {
                    cout << "Play again? (y/n)";
                    cin >> cont;
                    cout << "\n\n\n";
                    turn = 9;
                    continue;
                }

            turn++;

            if(turn >= 9)
            {
                cout << "\nTHE GAME ENDED IN A DRAW.\n\n";
                printBoard(board);
                cout << "Play again? (y/n)";
                cin >> cont;
                cout << "\n\n\n";
                turn = 9;
                continue;
            }
        }
    }

    return 0;
}

//Main function for deciding where the computer should play
//returns 1 if a win check comes back positive
//returns zero if the game is not won on the current turn
int moveSelect(char board[][CMAX])
{
    if(turn==0)
    {
        compMove(board, 4);
        return 0;
    }

    else if(turn>=3) //only run through this is the 4th or greater turn
    {
        if(mustBlockWin(board, you) != -1)  //Checks if I can win with a move this turn and makes it if I can
        {
            compMove(board, mustBlockWin(board, you));
            if(winDetect(board, you)) return 1;
        }

        else if(mustBlockWin(board, me) != -1)  //Checks if I have to block my opponent from winning anywhere and makes it if I can
        {
            compMove(board, mustBlockWin(board, me));
            return 0;
        }

        for(int r=0; r<RMAX; r++)  //this double for loop checks each cell to see if playing there would give the computer 2 chances to win next turn
        {
            for(int c=0; c<CMAX; c++)
            {
                if(board[r][c] == empty && numWin(board, r, c, you) >= 2)
                {
                    compMove(board, ((r*3)+c));
                    return 0;
                }
            }
        }

        int tempWinCount = 0;
        for(int r=0; r<RMAX; r++)  //this double for loop checks each cell to see if playing there would give the user 2 chances to win next turn
        {
            for(int c=0; c<CMAX; c++)
            {
                if(board[r][c] == empty && numWin(board, r, c, me) >= 2)
                {
                    tempWinCount++;
                }
            }
        }

        if(tempWinCount >= 2)
        {
            compMove(board, 1);
            return 0;
        }

    }

    char cors = 's';
    if(turn==2) //computer played first, it's now the computer's second turn
    {
        for(int r=0; r<RMAX; r+=2)
        {
            for(int c=0; c<CMAX; c+=2)
            {
                if(board[r][c] == me)
                    char cors = 'c';
            }
        }

        switch(cors)
        {
        case 's': //player played on a side
            compMove(board, 2);
            return 0;
            break;
        case 'c': //player played in a corner
            if(board[2][2] != me)
            {
                compMove(board, 8);
                return 0;
                break;
            }
            else
            {
                compMove(board, 6);
                return 0;
                break;
            }
        default:
            cout << "Something went wrong with tactic1.\nTerminating program.  Press any key to continue.";
            getch();
            exit(1);
        }
    }

    char csm = 's';
    if (turn==1) //the user went first, it's now the computer's first move  (round 2)
    {

        if(board[1][1] == me)
        {
            csm = 'm';
        }

        switch(csm)
        {
        case 's':
            compMove(board, 4);
            return 0;
            break;
        case 'm':
            compMove(board, 0);
            return 0;
            break;
        default:
            cout << "Something went wrong with csm.\nTerminating program.  Press any key to continue.";
            getch();
            exit(1);
        }
    }

    else // checks to see if there is anywhere that will give the computer one win opprotunity on the next turn
    {
        for(int r=0; r<RMAX; r++)
        {
            for(int c=0; c<CMAX; c++)
            {
                if(board[r][c] == empty && numWin(board, r, c, you) >= 1)
                {
                    compMove(board, ((r*3)+c));
                    return 0;
                }
            }
        }
    }

    for(int r=0; r<RMAX; r++) //last resort.  causes the computer to play in the first open cell it finds
    {
        for(int c=0; c<CMAX; c++)
        {
            if(board[r][c] == empty)
                compMove(board, ((r*3) +c));
                return 0;
        }
    }
    cout << "Ran through moveSelect (debug)" << endl;
}



void compMove(char board[][CMAX], int cell)
{
    int c = cell%3;
    int r = (cell-c)/3;
    if(board[r][c] == empty)
        board[r][c] = you;
    else
    {
        cout << "Cannot overwrite a cell.  Terminating program.\nPress any key to continue.";
        getch();
        exit(0);
    }
}



bool winDetect(char board[][CMAX], char player)
{
    string str;
    if(player == me) str = "\nYOU WIN!\n";
    else if(player == you) str = "\nTHE COMPUTER WINS.\n";

    for(int n=0; n<CMAX; n++)
    {
        if(board[n][0] == board[n][1] && board[n][2] == board[n][1] && board[n][0] == player)
        {
            cout << str << endl;
            printBoard(board);
            return true;
        }

        else if(board[0][n] == board[1][n] && board[2][n] == board[1][n] && board[0][n] == player)
        {
            cout << str << endl;
            printBoard(board);
            return true;
        }
    }

    if(board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] == player)
    {
        cout << str << endl;
        printBoard(board);
        return true;
    }

    else if(board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[2][0] == player)
    {
        cout << str << endl;
        printBoard(board);
        return true;
    }

    return false;
}



void boardManual(char board[][CMAX])
{
    cout << "Input the first row of characters.  Use capital characters (X, O, -): ";
    cin >> board[0][0] >> board[0][1] >> board[0][2];
    cout << "Input the second row of characters.  Use capital characters (X, O, -): ";
    cin >> board[1][0] >> board[1][1] >> board[1][2];
    cout << "Input the third row of characters.  Use capital characters (X, O, -): ";
    cin >> board[2][0] >> board[2][1] >> board[2][2];

    printBoard(board);
}



void boardIn(char board[][CMAX], char mark)
{
    for(int r=0; r<RMAX; r++)
    {
        for(int c=0; c<RMAX; c++)
        {
            board[r][c] = mark;
        }
    }
}


//checks a cell for the number of win opprotunities the cpu would have next turn if it played there

int numWin(char board[][CMAX], int row, int column, char player)
{
int count = 0;

if(board[row][column] != empty)
    return 0;

char tempBoard[RMAX][CMAX];
    for(int r=0; r<RMAX; r++)
    {
        for(int c=0; c<CMAX; c++)
        {
            tempBoard[r][c] = board[r][c];
        }
    }
    tempBoard[row][column] = player;

    for(int c=0; c<CMAX; c++)
    {
        for(int r=0; r<RMAX; r++)
        {
            //cout<< r <<" "<<c<<" "<<endl<<((r+2)%3)<<" "<<c<<endl;
            //cout<< c <<" "<<r<<" "<<endl<<c<<" "<<((r+2)%3)<<endl<<endl;


            //getch();

            if(tempBoard[r][c] == player && tempBoard[((r+2)%3)][c] == player && tempBoard[(r+4)%3][c] == empty)
            {
                    count++;
            }
            if(tempBoard[c][r] == player && tempBoard[c][((r+2)%3)] == player && tempBoard[c][(r+4)%3] == empty)
            {
                    count++;
            }
        }
    }

    for(int n=0; n<RMAX; n++)
    {
        if(tempBoard[n][n] == player && tempBoard[((n+2)%3)][((n+2)%3)] == player && tempBoard[(n+4)%3][(n+4)%3] == empty)
        {
                count++;
        }
    }

    if(tempBoard[0][2] == player && tempBoard[1][1] == player && tempBoard[2][0] == empty)
    {
            count++;
    }
    if(tempBoard[0][2] == player && tempBoard[2][0] == player && tempBoard[1][1] == empty)
    {
            count++;

    }
    if(tempBoard[1][1] == player && tempBoard[2][0] == player && tempBoard[0][2] == empty)
    {
            count++;
    }

    return count;
}


//checks if a space is empty and could be played in for one of the players to win

int mustBlockWin(char board[][CMAX], char player)
{
    for(int c=0; c<CMAX; c++)
    {
        for(int r=0; r<RMAX; r++)
        {
            if(board[r][c] == player && board[((r+2)%3)][c] == player && board[(r+4)%3][c] == empty)
            {
            return ((((r+4)%3)*3) + c);
            }
            else if(board[c][r] == player && board[c][((r+2)%3)] == player && board[c][(r+4)%3] == empty)
            {
            return ((c*3) + ((r+4)%3));
            }
        }
    }

    for(int n=0; n<RMAX; n++)
    {
        if(board[n][n] == player && board[((n+2)%3)][((n+2)%3)] == player && board[(n+4)%3][(n+4)%3] == empty)
        {
        return (((n+4)%3)*3 + ((n+4)%3));
        }
    }

    if(board[0][2] == player && board[1][1] == player && board[2][0] == empty)
    {
       return 6;
    }
    if(board[0][2] == player && board[2][0] == player && board[1][1] == empty)
    {
        return 4;
    }
    if(board[1][1] == player && board[2][0] == player && board[0][2] == empty)
    {
        return 2;
    }

    return -1;
}



void printBoard(char board[RMAX][CMAX])
{
    cout << "The current board is:\n";
    for(int r=0; r<RMAX; r++)
    {
        for(int c=0; c<CMAX; c++)
        {
            cout << board[r][c] << "\t";
        }
        cout << endl;
    }
}