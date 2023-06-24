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

// 挖掉一些空生成数独游戏
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

// 递归解数独
void solveSudoku(vector<vector<int>>& board, int row, int col, int& count) {
    if (col == 9) {
        col = 0;
        row++;
        if (row == 9) {
            count++; // 统计解的个数
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
        return true; // 数独已解决
    }

    for (int num = 1; num <= 9; num++) {
        if (isValid(board, row, col, num)) {
            board[row][col] = num;
            if (solveProblem(board)) {
                return true;
            }
            board[row][col] = 0; // 回溯
        }
    }
    return false; // 无解
}

//生成唯一解数独游戏
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

        // 检查唯一解
        int count = 0;
        vector<vector<int>> tempBoard = board;
        generateSudoku(tempBoard, 0, 0);
        solveSudoku(tempBoard, 0, 0, count);
        if (count != 1) {
            board[row][col] = temp;
        }
    }
}

// 打印数独终局
void printSudoku(const vector<vector<int>>& board) {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            if(board[row][col] == 0)
                cout << "$" << " "; //空格用$表示
            else
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
            }else {
                cout << "生成数独终局失败。" << endl;
            }
        }
        fclose(stdout);
    }
    else if (strcmp(argv[1], "-s") == 0) {
        if (argv[2] == NULL) {
            cout << "请输入参数。" << endl;
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
                outputFile << "数独无解。" << endl;
            }
        }
        inputFile.close();
        outputFile.close();
    }
    else if (strcmp(argv[1], "-n") == 0) {
        if (argv[2] == NULL) {
            cout << "请输入参数。" << endl;
            return;
        }
        int num = atoi(argv[2]);
        if (num < 1 || num > 10000) {
            cout << "参数n超出范围(参考范围：1~10000)。" << endl;
            return;
        }
        if (argv[3] == NULL) {
            freopen_s(&stream, problemFile, "w", stdout);
            for (int i = 0; i < num; i++) {
                if (generateSudoku(board, 0, 0)) {
                    cout << "[" << i + 1 << "]" << endl;
                    int seed = rand() % 64 + 1;
                    digHoles(board, seed); //随机挖去1-64个空格
                    printSudoku(board);
                    board = zero;
                }else {
                    cout << "生成数独游戏失败。" << endl;
                }
            }
            fclose(stdout);
        }
        else if (strcmp(argv[3], "-m") == 0) {
            if (argv[4] == NULL) {
                cout << "请输入参数。" << endl;
                return;
            }
            int difficulty = atoi(argv[4]);
            if (difficulty < 1 || difficulty > 3) {
                cout << "参数m范围错误(参考范围：1~3)。" << endl;
                return;
            }
            //数独难度比较主观，必须综合多个方面
            //这里简单处理，认为空数>45为easy，30~45为medium，15~29是hard
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
                    digHoles(board, seed); //随机挖去seed个空格
                    printSudoku(board);
                    board = zero;
                }else {
                    cout << "生成数独游戏失败。" << endl;
                }
            }
            fclose(stdout);
        }else if (strcmp(argv[3], "-r") == 0) {
            if (argv[4] == NULL) {
                cout << "请输入参数。" << endl;
                return;
            }
            const char* split = "~";
            // 拆分字符串
            char* p = strtok(argv[4], split);
            int num1 = 0, num2 = 0;
            sscanf_s(p, "%d", &num1);
            p = strtok(NULL, split);
            sscanf_s(p, "%d", &num2);
            if (num1 < 20 || num2 > 55 || num2 < num1) {
                cout << "参数r范围错误(参考范围：20~55)。" << endl;
                return;
            }
            freopen_s(&stream, problemFile, "w", stdout);
            for (int i = 0; i < num; i++) {
                int seed = rand() % (num2 - num1 + 1) + num1;
                if (generateSudoku(board, 0, 0)) {
                    cout << "[" << i + 1 << "]" << endl;
                    digHoles(board, seed); //随机挖去num1~num2个空格
                    printSudoku(board);
                    board = zero;
                }else {
                    cout << "生成数独游戏失败。" << endl;
                }
            }
            fclose(stdout);
        }else if (strcmp(argv[3], "-u") == 0) {
            freopen_s(&stream, problemFile, "w", stdout);
            for (int i = 0; i < num; i++) {
                int seed = rand() % 35 + 1;
                if (generateSudoku(board, 0, 0)) {
                    cout << "[" << i + 1 << "]" << endl;
                    //挖的空越少，唯一解概率越大
                    digHolesUnique(board, seed); //随机挖去1~35个空格, 若没有唯一解则回填
                    printSudoku(board);
                    board = zero;
                }else {
                    cout << "生成数独游戏失败。" << endl;
                }
            }
            fclose(stdout);
        }
    }
    else {
        cout << "参数错误(参考参数：-c、-s、-n开头)。" << endl;
    }
}

int main(int argc, char* argv[]) {
    srand(time(NULL));
    parameterCheck(argv);
    return 0;
}