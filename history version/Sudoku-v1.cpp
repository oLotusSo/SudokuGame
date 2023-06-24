#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

const char* finalFile = "./finalFile.txt";
const char* problemFile = "./problemFile.txt";
const char* solveFile = "./solveFile.txt";

// 检查数字num是否可以放置在(row, col)位置
bool isValid(vector<vector<int>>& board, int row, int col, int num) {
    // 检查行是否有重复数字
    for (int i = 0; i < 9; i++) {
        if (board[row][i] == num) {
            return false;
        }
    }

    // 检查列是否有重复数字
    for (int i = 0; i < 9; i++) {
        if (board[i][col] == num) {
            return false;
        }
    }

    // 检查3x3小方格内是否有重复数字
    int startRow = (row / 3) * 3;
    int startCol = (col / 3) * 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[startRow + i][startCol + j] == num) {
                return false;
            }
        }
    }

    return true;
}

// 递归生成数独终局
bool generateSudoku(vector<vector<int>>& board, int row, int col) {
    if (col == 9) {
        col = 0;
        row++;
        if (row == 9) {
            return true;  // 数独终局生成完成
        }
    }

    if (board[row][col] != 0) {
        return generateSudoku(board, row, col + 1);
    }

    vector<int> numbers = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    random_shuffle(numbers.begin(), numbers.end());

    for (int num : numbers) {
        if (isValid(board, row, col, num)) {
            board[row][col] = num;
            if (generateSudoku(board, row, col + 1)) {
                return true;
            }
            board[row][col] = 0;
        }
    }

    return false;
}

// 打印数独终局
void printSudoku(const vector<vector<int>>& board) {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            cout << board[row][col] << " ";
        }
        cout << endl;
    }
}

// 检查输入参数
void parameterCheck(char* argv[]) {
    vector<vector<int>> board(9, vector<int>(9, 0)), zero(9, vector<int>(9, 0));
    FILE* stream;
    if (argv[1] == NULL) {
        cout << "请输入参数。" << endl;
    }else if (strcmp(argv[1], "-c") == 0) {
        if (argv[2] == NULL) {
            cout << "请输入参数。" << endl;
            return;
        }
        int num = atoi(argv[2]);
        if (num < 1 || num >1000000) {
            cout << "参数c超出范围(参考范围：1~1000000)。" << endl;
            return;
        }
        freopen_s(&stream, finalFile, "w", stdout);
        for (int i = 0; i < num; i++) {
            if (generateSudoku(board, 0, 0)) {
                cout << "[" << i + 1 << "]" << endl;
                printSudoku(board);
                board = zero;
            }
            else {
                cout << "生成数独终局失败。" << endl;
            }
        }
        fclose(stdout);
    }
    else if (strcmp(argv[1], "-s") == 0) {
        cout << "2" << endl;
    }
    else if (strcmp(argv[1], "-n") == 0) {
        cout << "3" << endl;
    }
    else {
        cout << "参数错误。" << endl;
    }
}

int main(int argc, char* argv[]) {
    srand(time(NULL));
    parameterCheck(argv);
    return 0;
}