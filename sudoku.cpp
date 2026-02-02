#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> sudoku = {
    {5, 3, 0, 0, 7, 0, 0, 0, 0},
    {6, 0, 0, 1, 9, 5, 0, 0, 0},
    {0, 9, 8, 0, 0, 0, 0, 6, 0},
    {8, 0, 0, 0, 6, 0, 0, 0, 3},
    {4, 0, 0, 8, 0, 3, 0, 0, 1},
    {7, 0, 0, 0, 2, 0, 0, 0, 6},
    {0, 6, 0, 0, 0, 0, 2, 8, 0},
    {0, 0, 0, 4, 1, 9, 0, 0, 5},
    {0, 0, 0, 0, 8, 0, 0, 7, 9}};

void printSudoku()
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            cout << sudoku[i][j] << " ";
        }
        cout << endl;
    }
}

int countRemaining()
{
    int count = 0;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (sudoku[i][j] == 0)
                count++;
        }
    }
    return count;
}

pair<int, int> findNext()
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (sudoku[i][j] == 0)
                return {i, j};
        }
    }
    return {-1, -1};
}

bool isRowValid(int row, int val)
{
    for (int i = 0; i < 9; i++)
    {
        if (sudoku[row][i] == val)
            return false;
    }
    return true;
}

bool isColumnValid(int column, int val)
{
    for (int i = 0; i < 9; i++)
    {
        if (sudoku[i][column] == val)
            return false;
    }
    return true;
}

bool isBoxValid(int row, int column, int val)
{
    int r = 3 * (row / 3);
    int c = 3 * (column / 3);
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (sudoku[r + i][c + j] == val)
                return false;
        }
    }
    return true;
}

bool isValueValid(int x, int y, int val)
{
    return isRowValid(x, val) && isColumnValid(y, val) && isBoxValid(x, y, val);
}

bool recurseSolve()
{
    int count = countRemaining();
    if (count == 0)
        return true;

    pair<int, int> coords = findNext();
    int x = coords.first;
    int y = coords.second;

    for (int val = 1; val <= 9; val++)
    {
        if (isValueValid(x, y, val))
        {
            sudoku[x][y] = val;
            bool result = recurseSolve();
            if (result)
            {
                return true;
            }
            sudoku[x][y] = 0;
        }
    }
    return false;
}

int main()
{
    recurseSolve();
    printSudoku();
    return 0;
}