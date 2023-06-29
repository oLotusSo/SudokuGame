# SudokuGame

请使用cmd控制台测试Sudoku.exe程序。

例如：Sudoku.exe -c 100 表示生成100个数独终局至文件。

参数&emsp;&emsp;意义&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;范围限制&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;示例

-c&emsp;&emsp;生成数独终局 &emsp; &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;1-1000000&emsp; &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;Sudoku.exe -c 20

-s&emsp;&emsp;求解数独(会输出至output.txt) 绝对或相对路径&emsp;&emsp;&emsp;&emsp;&emsp;Sudoku.exe -s solveFile.txt 

-n&emsp;&emsp;生成数独游戏($表示需要填) &emsp;1-10000&emsp; &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;Sudoku.exe -n 1000

-m  &emsp;生成游戏难度(1简单，3难)&emsp;&emsp;1-3 &emsp; &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;Sudoku.exe -n 1000 -m 1

-r&emsp;&emsp;生成游戏挖空数量范围 &emsp; &emsp;&emsp;20-55 &emsp; &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;Sudoku.exe -n 20 -r 30~45

-u&emsp;&emsp;生成数独游戏的解唯一  &emsp;&emsp;&emsp;无参数 &emsp;  &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;Sudoku.exe -n 20 -u

生成或求解的数独格式：

[序号(整数)]

九行九列81个1-9的数字，其中$表示需要填数的空格，以空格隔开。

例如：

[1] <br/>
9 $ $ $ 6 1 $ 3 $ <br/>
1 $ 3 4 9 8 7 2 $ <br/>
7 4 8 $ 2 3 6 9 1 <br/>
6 3 4 1 $ 9 2 5 8 <br/>
$ 8 1 $ 4 6 9 $ $ <br/>
2 $ $ $ $ 5 4 1 $ <br/>
8 1 $ $ $ 2 3 4 7 <br/>
4 $ $ 6 $ $ $ 8 9 <br/>
3 7 9 $ 1 4 5 6 2

