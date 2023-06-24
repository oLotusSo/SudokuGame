#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

const char* finalFile = "./finalFile.txt";
const char* problemFile = "./problemFile.txt";
const char* solveFile = "./solveFile.txt";

// �������num�Ƿ���Է�����(row, col)λ��
bool isValid(vector<vector<int>>& board, int row, int col, int num) {
    // ������Ƿ����ظ�����
    for (int i = 0; i < 9; i++) {
        if (board[row][i] == num) {
            return false;
        }
    }

    // ������Ƿ����ظ�����
    for (int i = 0; i < 9; i++) {
        if (board[i][col] == num) {
            return false;
        }
    }

    // ���3x3С�������Ƿ����ظ�����
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

// �ݹ����������վ�
bool generateSudoku(vector<vector<int>>& board, int row, int col) {
    if (col == 9) {
        col = 0;
        row++;
        if (row == 9) {
            return true;  // �����վ��������
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

// ��ӡ�����վ�
void printSudoku(const vector<vector<int>>& board) {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            cout << board[row][col] << " ";
        }
        cout << endl;
    }
}

// ����������
void parameterCheck(char* argv[]) {
    vector<vector<int>> board(9, vector<int>(9, 0)), zero(9, vector<int>(9, 0));
    FILE* stream;
    if (argv[1] == NULL) {
        cout << "�����������" << endl;
    }else if (strcmp(argv[1], "-c") == 0) {
        if (argv[2] == NULL) {
            cout << "�����������" << endl;
            return;
        }
        int num = atoi(argv[2]);
        if (num < 1 || num >1000000) {
            cout << "����c������Χ(�ο���Χ��1~1000000)��" << endl;
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
                cout << "���������վ�ʧ�ܡ�" << endl;
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
        cout << "��������" << endl;
    }
}

int main(int argc, char* argv[]) {
    srand(time(NULL));
    parameterCheck(argv);
    return 0;
}