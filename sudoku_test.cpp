#include "gtest/gtest.h"
#include "Sudoku.h"
#include <fstream>
#include <cstdio>
#include <string>
using namespace std;


/*
bool isValid(vector<vector<int>>& board, int row, int col, int num)：检查数字num是否可以放置在数独棋盘board的(row, col)位置，如果可以放置则返回true，否则返回false。

bool generateSudoku(vector<vector<int>>& board, int row, int col)：递归生成数独终局。从(row, col)位置开始，填充数独棋盘board，确保填充的数字满足数独规则。

void digHoles(vector<vector<int>>& board, int numHoles)：挖掉一些空生成数独游戏。从完整的数独终局board中挖去numHoles个空格，生成一个数独游戏问题。

void solveSudoku(vector<vector<int>>& board, int row, int col, int& count)：递归解数独。从(row, col)位置开始，填充数独棋盘board，并计算解的个数。将解的数量存储在count变量中。

bool findUnassignedLocation(vector<vector<int>> board, int& row, int& col)：在数独棋盘board中查找未分配的位置（即值为0的空格）。如果找到未分配的位置，则将其行和列分别存储在row和col变量中，并返回true。如果没有未分配的位置，则返回false。

bool solveProblem(vector<vector<int>> &board)：解决给定的数独问题。使用回溯算法，在数独棋盘board上填充数字，以找到一个满足数独规则的解。如果找到解，则返回true，否则返回false。

void digHolesUnique(vector<vector<int>>& board, int numHoles)：生成具有唯一解的数独游戏。从完整的数独终局board中挖去numHoles个空格，确保生成的数独问题具有唯一解。

void printSudoku(const vector<vector<int>>& board)：打印数独终局。将数独棋盘board以易于阅读的格式打印到控制台。

void parameterCheck(char* argv[])：检查命令行参数。验证传递给程序的命令行参数是否有效。如果参数无效，则显示错误消息并退出程序。*/
bool review(int* p)  //判断是否有没有的数字
{
    int i=1;
    while(i<10)
    {
        if(!*(++p))
        {
            return false;
        }
        ++i;
    }
    return true;
}
void zero_tag(int* p)   //每次判断后对tag数组清零
{
    int i=1;
    while(i<10)
    {
        *(++p)=0;
        ++i;
    }
}
bool isSolved(vector<vector<int> > board )
{
    int tag[10]={0};  //0号单元不用
    int curValue=0;
    for(int i=0;i<9;i++)  //对每一行进行检查
    {
        for(int j=0;j<9;j++)
        {
            curValue=board[i][j];
            tag[curValue]=1;    //如果有重复也会是1，但是缺少的数字相应的位置上就会是0
        }
        if(!review(tag))
            return false;   //有重复元素

        zero_tag(tag);//每次判断后对tag数组清零
    }

    for(int i=0;i<9;i++)  //对每一列进行检查
    {
        for(int j=0;j<9;j++)
        {
            curValue=board[j][i];
            tag[curValue]=1;
        }

        if(!review(tag))
            return false;   //有重复元素

        zero_tag(tag);//每次判断后对tag数组清零
    }

    for(int k=0;k<9;k=k+3)  //对每一3x3方块进行检查
    {
        for(int t=0;t<9;t=t+3)  //对1-3行，1-9列进行检查
        {
            for(int i=k;i<k+3;i++)  //计算每一个方块的和
                for(int j=t;j<t+3;j++)
                {
                    curValue=board[j][i];
                    tag[curValue]=1;
                }

            if(!review(tag))
                return false;   //有重复元素

            zero_tag(tag);//每次判断后对tag数组清零
        }
    }

    return true;  //经过了所有的行，列块的检查

}


TEST(SudokuTest, IsValidTest) {
    vector<vector<int>> board = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    EXPECT_TRUE(isValid(board, 0, 2, 4));
    EXPECT_FALSE(isValid(board, 0, 2, 5));
    EXPECT_FALSE(isValid(board, 0, 2, 6));
    EXPECT_FALSE(isValid(board, 0, 2, 9));
}

//GenerateSudokuTest：生成指定数量的数独终盘，并检查它们是否已解决。
TEST(SudokuTest, GenerateSudokuTest2) {
    vector<vector<int>> board(9, vector<int>(9, 0));
    ASSERT_TRUE(generateSudoku(board, 0, 0));
    EXPECT_TRUE(isSolved(board));
}

//SolveProblemTest：对给定的数独问题求解，并检查求解后的数独是否已解决
TEST(SudokuTest, SolveProblemTest) {
    vector<vector<int>> problem = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    ASSERT_TRUE(solveProblem(problem));
    EXPECT_TRUE(isSolved(problem));
}

TEST(SudokuTest, SolveProblemTest2) {
    vector<vector<int>> problem = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    vector<vector<int>> expected_solution = {
        {5, 3, 4, 6, 7, 8, 9, 1, 2},
        {6, 7, 2, 1, 9, 5, 3, 4, 8},
        {1, 9, 8, 3, 4, 2, 5, 6, 7},
        {8, 5, 9, 7, 6, 1, 4, 2, 3},
        {4, 2, 6, 8, 5, 3, 7, 9, 1},
        {7, 1, 3, 9, 2, 4, 8, 5, 6},
        {9, 6, 1, 5, 3, 7, 2, 8, 4},
        {2, 8, 7, 4, 1, 9, 6, 3, 5},
        {3, 4, 5, 2, 8, 6, 1, 7, 9}
    };
    int cnt=0;
    solveProblem(problem);
    EXPECT_EQ(problem, expected_solution);
}

TEST(SudokuTest, FindUnassignedLocationTest) {
    vector<vector<int>> problem = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    int row, col;
    ASSERT_TRUE(findUnassignedLocation(problem, row, col));
    EXPECT_EQ(row, 0);
    EXPECT_EQ(col, 2);
}



//DigHolesTest：挖空指定数量、难度和空格数量范围的数独问题，并检查挖空后的数独是否符合预期的空格数量。
TEST(SudokuTest, DigHolesTest) {
    vector<vector<int>> board = {
        {5, 3, 4, 6, 7, 8, 9, 1, 2},
        {6, 7, 2, 1, 9, 5, 3, 4, 8},
        {1, 9, 8, 3, 4, 2, 5, 6, 7},
        {8, 5, 9, 7, 6, 1, 4, 2, 3},
        {4, 2, 6, 8, 5, 3, 7, 9, 1},
        {7, 1, 3, 9, 2, 4, 8, 5, 6},
        {9, 6, 1, 5, 3, 7, 2, 8, 4},
        {2, 8, 7, 4, 1, 9, 6, 3, 5},
        {3, 4, 5, 2, 8, 6, 1, 7, 9}
    };

    int num_holes = 40;
    digHoles(board, num_holes);

    int holes_count = 0;
    for (const auto& row : board) {
        holes_count += count(row.begin(), row.end(), 0);
    }
    EXPECT_EQ(holes_count, num_holes);
}

//PrintBoardsTest：将数独数据打印到控制台。将标准输出重定向到一个字符串流，以便捕获输出,检查输出字符串是否非空
TEST(SudokuTest, PrintBoardsTest) {
    vector<vector<int>> board = {
        {5, 3, 4, 6, 7, 8, 9, 1, 2},
        {6, 7, 2, 1, 9, 5, 3, 4, 8},
        {1, 9, 8, 3, 4, 2, 5, 6, 7},
        {8, 5, 9, 7, 6, 1, 4, 2, 3},
        {4, 2, 6, 8, 5, 3, 7, 9, 1},
        {7, 1, 3, 9, 2, 4, 8, 5, 6},
        {9, 6, 1, 5, 3, 7, 2, 8, 4},
        {2, 8, 7, 4, 1, 9, 6, 3, 5},
        {3, 4, 5, 2, 8, 6, 1, 7, 9}
    };

    // Redirect stdout to a stringstream
    stringstream buffer;
    streambuf* prevbuf = cout.rdbuf(buffer.rdbuf());

    printSudoku(board);

    // Restore stdout
    cout.rdbuf(prevbuf);

    string output = buffer.str();
    EXPECT_FALSE(output.empty());
}

//SolveSudokuTest：对给定的有唯一解的数独问题求解，并检查count是否得到1

TEST(SudokuTest, SolveSudokuTest) {
    vector<vector<int>> input_board = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    int cnt=0;
    solveSudoku(input_board, 0, 0, cnt);
    ASSERT_EQ(cnt,1);

}
//首先使用digHolesUnique函数从完整的数独终局中挖去num_holes个空格，然后计算挖去的空格数量是否与num_holes相等。接着，我们使用solveSudoku函数计算生成的数独问题的解的数量，并检查是否只有一个解，以确保问题具有唯一解。
TEST(SudokuTest, DigHolesUniqueTest) {
    vector<vector<int>> board = {
        {5, 3, 4, 6, 7, 8, 9, 1, 2},
        {6, 7, 2, 1, 9, 5, 3, 4, 8},
        {1, 9, 8, 3, 4, 2, 5, 6, 7},
        {8, 5, 9, 7, 6, 1, 4, 2, 3},
        {4, 2, 6, 8, 5, 3, 7, 9, 1},
        {7, 1, 3, 9, 2, 4, 8, 5, 6},
        {9, 6, 1, 5, 3, 7, 2, 8, 4},
        {2, 8, 7, 4, 1, 9, 6, 3, 5},
        {3, 4, 5, 2, 8, 6, 1, 7, 9}
    };

    int num_holes = 30;
    digHolesUnique(board, num_holes);

    int holes_count = 0;
    for (const auto& row : board) {
        holes_count += count(row.begin(), row.end(), 0);
    }
    EXPECT_EQ(holes_count, num_holes);

    // Check if the generated problem has a unique solution
    int count = 0;
    solveSudoku(board, 0, 0, count);
    EXPECT_EQ(count, 1);
}




TEST(SudokuTest, ParameterCheckTest) {
    // 创建临时输入文件
    ofstream input_file("temp_input.txt");
    input_file << "[1]\n";
    input_file << "5 3 0 0 7 0 0 0 0\n";
    input_file << "6 0 0 1 9 5 0 0 0\n";
    input_file << "0 9 8 0 0 0 0 6 0\n";
    input_file << "8 0 0 0 6 0 0 0 3\n";
    input_file << "4 0 0 8 0 3 0 0 1\n";
    input_file << "7 0 0 0 2 0 0 0 6\n";
    input_file << "0 6 0 0 0 0 2 8 0\n";
    input_file << "0 0 0 4 1 9 0 0 5\n";
    input_file << "0 0 0 0 8 0 0 7 9\n";
    input_file.close();

    // 模拟命令行参数
    char* argv[] = {
        "sudoku.exe",
        "-s",
        "temp_input.txt"
    };
    int argc = sizeof(argv) / sizeof(argv[0]);

    // 调用parameterCheck函数
    parameterCheck(argv);

    // 检查输出文件的内容
    ifstream output_file("output.txt");
    string line;
    vector<string> output_lines;
    while (getline(output_file, line)) {
        output_lines.push_back(line);
    }
    output_file.close();

    // 删除临时输入文件
    remove("temp_input.txt");

    // 验证输出文件的内容
    ASSERT_EQ(output_lines.size(), 10);
    EXPECT_EQ(output_lines[0], "[1]");
    EXPECT_EQ(output_lines[1], "5 3 4 6 7 8 9 1 2 ");
    EXPECT_EQ(output_lines[2], "6 7 2 1 9 5 3 4 8 ");
    EXPECT_EQ(output_lines[3], "1 9 8 3 4 2 5 6 7 ");
    EXPECT_EQ(output_lines[4], "8 5 9 7 6 1 4 2 3 ");
    EXPECT_EQ(output_lines[5], "4 2 6 8 5 3 7 9 1 ");
    EXPECT_EQ(output_lines[6], "7 1 3 9 2 4 8 5 6 ");
    EXPECT_EQ(output_lines[7], "9 6 1 5 3 7 2 8 4 ");
    EXPECT_EQ(output_lines[8], "2 8 7 4 1 9 6 3 5 ");
    EXPECT_EQ(output_lines[9], "3 4 5 2 8 6 1 7 9 ");
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
// To run this test:
// g++ -o sudoku_test sudoku_test.cpp Sudoku.cpp -lgtest -lgtest_main -std=c++14
// ./sudoku_test