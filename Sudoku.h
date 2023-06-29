#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <stdio.h>
#include <algorithm>
#pragma warning (disable: 4996)

using namespace std;

// 检查数字num是否可以放置在(row, col)位置
bool isValid(vector<vector<int> >& board, int row, int col, int num) ;
// 递归生成数独终局
bool generateSudoku(vector<vector<int> >& board, int row, int col) ;

// 挖掉一些空生成数独游戏
void digHoles(vector<vector<int> >& board, int numHoles) ;

// 递归解数独
void solveSudoku(vector<vector<int> >& board, int row, int col, int& count) ;

bool findUnassignedLocation(vector<vector<int> > board, int& row, int& col) ;
bool solveProblem(vector<vector<int> > &board) ;

//生成唯一解数独游戏
void digHolesUnique(vector<vector<int> >& board, int numHoles) ;

// 打印数独终局
void printSudoku(const vector<vector<int> >& board);

// 检查输入参数
void parameterCheck(char* argv[]);
