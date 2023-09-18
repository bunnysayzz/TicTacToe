#include <iostream>
using namespace std;

#define COMPUTER 1
#define HUMAN 2
#define SIDE 3
#define COMPUTERMOVE 'O'
#define HUMANMOVE 'X'

void showBoard(char board[][SIDE])
{
    cout << "\t\t\t " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << endl;
    cout << "\t\t\t-----------" << endl;
    cout << "\t\t\t " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << endl;
    cout << "\t\t\t-----------" << endl;
    cout << "\t\t\t " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << endl << endl;
}

void showInstructions()
{
    cout << "\nChoose a cell numbered from 1 to 9 as below and play\n\n";
    cout << "\t\t\t 1 | 2 | 3 \n";
    cout << "\t\t\t-----------\n";
    cout << "\t\t\t 4 | 5 | 6 \n";
    cout << "\t\t\t-----------\n";
    cout << "\t\t\t 7 | 8 | 9 \n\n";
}

void initialise(char board[][SIDE])
{
    // Initially the board to '*' as said
    for (int i = 0; i < SIDE; i++)
    {
        for (int j = 0; j < SIDE; j++)
            board[i][j] = '*';
    }
}

void declareWinner(int whoseTurn)
{
    if (whoseTurn == COMPUTER)
        cout << "COMPUTER has won\n";
    else
        cout << "HUMAN has won\n";
}

bool rowCrossed(char board[][SIDE])
{
    for (int i = 0; i < SIDE; i++)
    {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != '*')
            return true;
    }
    return false;
}

bool columnCrossed(char board[][SIDE])
{
    for (int i = 0; i < SIDE; i++)
    {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != '*')
            return true;
    }
    return false;
}

bool diagonalCrossed(char board[][SIDE])
{
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != '*')
        return true;
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != '*')
        return true;
    return false;
}

bool gameOver(char board[][SIDE])
{
    return (rowCrossed(board) || columnCrossed(board) || diagonalCrossed(board));
}

int minimax(char board[][SIDE], int depth, bool isAI)
{
    int score = 0;
    int bestScore = 0;
    if (gameOver(board) == true)
    {
        if (isAI == true)
            return -10;
        if (isAI == false)
            return 10;
    }
    else
    {
        if (depth < 9)
        {
            if (isAI == true)
            {
                bestScore = -999;
                for (int i = 0; i < SIDE; i++)
                {
                    for (int j = 0; j < SIDE; j++)
                    {
                        if (board[i][j] == '*')
                        {
                            board[i][j] = COMPUTERMOVE;
                            int currentScore = minimax(board, depth + 1, false);
                            board[i][j] = '*';
                            if (currentScore > bestScore)
                                bestScore = currentScore;
                        }
                    }
                }
                return bestScore;
            }
            else
            {
                bestScore = 999;
                for (int i = 0; i < SIDE; i++)
                {
                    for (int j = 0; j < SIDE; j++)
                    {
                        if (board[i][j] == '*')
                        {
                            board[i][j] = HUMANMOVE;
                            int currentScore = minimax(board, depth + 1, true);
                            board[i][j] = '*';
                            if (currentScore < bestScore)
                                bestScore = currentScore;
                        }
                    }
                }
                return bestScore;
            }
        }
        else
        {
            return 0;
        }
    }
    return bestScore; // Add this line to fix the warning
}

int bestMove(char board[][SIDE], int moveIndex)
{
    int x = -1, y = -1;
    int score = 0, bestScore = -999;
    for (int i = 0; i < SIDE; i++)
    {
        for (int j = 0; j < SIDE; j++)
        {
            if (board[i][j] == '*')
            {
                board[i][j] = COMPUTERMOVE;
                score = minimax(board, moveIndex + 1, false);
                board[i][j] = '*';
                if (score > bestScore)
                {
                    bestScore = score;
                    x = i;
                    y = j;
                }
            }
        }
    }
    return (x * 3) + y + 1;
}

int main()
{
    char board[SIDE][SIDE];
    int moveIndex = 0;
    
    initialise(board);
    showInstructions();
    
    while (gameOver(board) == false && moveIndex < SIDE*SIDE)
    {
        if (moveIndex % 2 == 0)
        {
            int cell;
            cout << "Enter cell number for HUMAN (X): ";
            cin >> cell;
            cell--;
            board[cell / 3][cell % 3] = HUMANMOVE;
        }
        else
        {
            cout << "Computer's turn (O): ";
            int bestMoveIndex = bestMove(board, moveIndex);
            board[(bestMoveIndex - 1) / 3][(bestMoveIndex - 1) % 3] = COMPUTERMOVE;
            cout << bestMoveIndex << endl;
        }
        moveIndex++;
        showBoard(board);
    }
    
    if (gameOver(board) == false && moveIndex == SIDE * SIDE)
        cout << "It's a draw!" << endl;
    else
        declareWinner(moveIndex % 2 + 1);
    
    return 0;
}
