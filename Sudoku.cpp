#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
#pragma warning (disable: 4996)
using namespace std;

const char* finalFile = "./finalFile.txt";
const char* problemFile = "./problemFile.txt";
const char* solveFile = "./solveFile.txt";
const char* output = "./output.txt";

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

// �ڵ�һЩ������������Ϸ
void digHoles(vector<vector<int>>& board, int numHoles) {
    for (int i = 0; i < numHoles; i++) {
        int row = rand() % 9;
        int col = rand() % 9;
        while (board[row][col] == 0) {
            row = rand() % 9;
            col = rand() % 9;
        }
        board[row][col] = 0;
    }
}

// �ݹ������
void solveSudoku(vector<vector<int>>& board, int row, int col, int& count) {
    if (col == 9) {
        col = 0;
        row++;
        if (row == 9) {
            count++; // ͳ�ƽ�ĸ���
            return;
        }
    }
    if (board[row][col] != 0) {
        solveSudoku(board, row, col + 1, count);
        return;
    }
    for (int num = 1; num <= 9; num++) {
        if (isValid(board, row, col, num)) {
            board[row][col] = num;
            solveSudoku(board, row, col + 1, count);
            board[row][col] = 0;
        }
    }
}

bool findUnassignedLocation(vector<vector<int>> board, int& row, int& col) {
    for (row = 0; row < 9; row++) {
        for (col = 0; col < 9; col++) {
            if (board[row][col] == 0) {
                return true;
            }
        }
    }
    return false;
}
bool solveProblem(vector<vector<int>> &board) {
    int row, col;
    if (!findUnassignedLocation(board, row, col)) {
        return true; // �����ѽ��
    }

    for (int num = 1; num <= 9; num++) {
        if (isValid(board, row, col, num)) {
            board[row][col] = num;
            if (solveProblem(board)) {
                return true;
            }
            board[row][col] = 0; // ����
        }
    }
    return false; // �޽�
}

//����Ψһ��������Ϸ
void digHolesUnique(vector<vector<int>>& board, int numHoles) {
    for (int i = 0; i < numHoles; i++) {
        int row = rand() % 9;
        int col = rand() % 9;
        while (board[row][col] == 0) {
            row = rand() % 9;
            col = rand() % 9;
        }
        int temp = board[row][col];
        board[row][col] = 0;

        // ���Ψһ��
        int count = 0;
        vector<vector<int>> tempBoard = board;
        generateSudoku(tempBoard, 0, 0);
        solveSudoku(tempBoard, 0, 0, count);
        if (count != 1) {
            board[row][col] = temp;
        }
    }
}

// ��ӡ�����վ�
void printSudoku(const vector<vector<int>>& board) {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            if(board[row][col] == 0)
                cout << "$" << " "; //�ո���$��ʾ
            else
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
            }else {
                cout << "���������վ�ʧ�ܡ�" << endl;
            }
        }
        fclose(stdout);
    }
    else if (strcmp(argv[1], "-s") == 0) {
        if (argv[2] == NULL) {
            cout << "�����������" << endl;
            return;
        }
        char* input = argv[2];
        ifstream inputFile(input);
        if (!inputFile) {
            cerr << "Failed to open input file." << endl;
            return;
        }
        ofstream outputFile(output);
        if (!outputFile) {
            cerr << "Failed to open output file." << endl;
            return;
        }
        string str, temp;
        int no = 0;
        while (inputFile >> str) {
            str = str.substr(1, str.length() - 2);
            no = stoi(str);
            for (int i = 0; i < 9; i++) {
                for (int j = 0; j < 9; j++) {
                    inputFile >> temp;
                    if (temp == "$")board[i][j] = 0;
                    else board[i][j] = stoi(temp);
                }
            }
            if (solveProblem(board)) {
                outputFile << "[" << no << "]" << endl;
                for (int i = 0; i < 9; i++) {
                    for (int j = 0; j < 9; j++) {
                        outputFile << board[i][j] << " ";
                    }
                    outputFile << endl;
                }
            }
            else {
                outputFile << "�����޽⡣" << endl;
            }
        }
        inputFile.close();
        outputFile.close();
    }
    else if (strcmp(argv[1], "-n") == 0) {
        if (argv[2] == NULL) {
            cout << "�����������" << endl;
            return;
        }
        int num = atoi(argv[2]);
        if (num < 1 || num > 10000) {
            cout << "����n������Χ(�ο���Χ��1~10000)��" << endl;
            return;
        }
        if (argv[3] == NULL) {
            freopen_s(&stream, problemFile, "w", stdout);
            for (int i = 0; i < num; i++) {
                if (generateSudoku(board, 0, 0)) {
                    cout << "[" << i + 1 << "]" << endl;
                    int seed = rand() % 64 + 1;
                    digHoles(board, seed); //�����ȥ1-64���ո�
                    printSudoku(board);
                    board = zero;
                }else {
                    cout << "����������Ϸʧ�ܡ�" << endl;
                }
            }
            fclose(stdout);
        }
        else if (strcmp(argv[3], "-m") == 0) {
            if (argv[4] == NULL) {
                cout << "�����������" << endl;
                return;
            }
            int difficulty = atoi(argv[4]);
            if (difficulty < 1 || difficulty > 3) {
                cout << "����m��Χ����(�ο���Χ��1~3)��" << endl;
                return;
            }
            //�����ѶȱȽ����ۣ������ۺ϶������
            //����򵥴�����Ϊ����>45Ϊeasy��30~45Ϊmedium��15~29��hard
            freopen_s(&stream, problemFile, "w", stdout);
            for (int i = 0; i < num; i++) {
                int seed = 0;
                switch (difficulty) {
                    case 1:
                        seed = rand() % 19 + 46;
                        break;
                    case 2:
                        seed = rand() % 16 + 30;
                        break;
                    case 3:
                        seed = rand() % 15 + 15;
                        break;
                }
                if (generateSudoku(board, 0, 0)) {
                    cout << "[" << i + 1 << "]" << endl;
                    digHoles(board, seed); //�����ȥseed���ո�
                    printSudoku(board);
                    board = zero;
                }else {
                    cout << "����������Ϸʧ�ܡ�" << endl;
                }
            }
            fclose(stdout);
        }else if (strcmp(argv[3], "-r") == 0) {
            if (argv[4] == NULL) {
                cout << "�����������" << endl;
                return;
            }
            const char* split = "~";
            // ����ַ���
            char* p = strtok(argv[4], split);
            int num1 = 0, num2 = 0;
            sscanf_s(p, "%d", &num1);
            p = strtok(NULL, split);
            sscanf_s(p, "%d", &num2);
            if (num1 < 20 || num2 > 55 || num2 < num1) {
                cout << "����r��Χ����(�ο���Χ��20~55)��" << endl;
                return;
            }
            freopen_s(&stream, problemFile, "w", stdout);
            for (int i = 0; i < num; i++) {
                int seed = rand() % (num2 - num1 + 1) + num1;
                if (generateSudoku(board, 0, 0)) {
                    cout << "[" << i + 1 << "]" << endl;
                    digHoles(board, seed); //�����ȥnum1~num2���ո�
                    printSudoku(board);
                    board = zero;
                }else {
                    cout << "����������Ϸʧ�ܡ�" << endl;
                }
            }
            fclose(stdout);
        }else if (strcmp(argv[3], "-u") == 0) {
            freopen_s(&stream, problemFile, "w", stdout);
            for (int i = 0; i < num; i++) {
                int seed = rand() % 35 + 1;
                if (generateSudoku(board, 0, 0)) {
                    cout << "[" << i + 1 << "]" << endl;
                    //�ڵĿ�Խ�٣�Ψһ�����Խ��
                    digHolesUnique(board, seed); //�����ȥ1~35���ո�, ��û��Ψһ�������
                    printSudoku(board);
                    board = zero;
                }else {
                    cout << "����������Ϸʧ�ܡ�" << endl;
                }
            }
            fclose(stdout);
        }
    }
    else {
        cout << "��������(�ο�������-c��-s��-n��ͷ)��" << endl;
    }
}

int main(int argc, char* argv[]) {
    srand(time(NULL));
    parameterCheck(argv);
    return 0;
}