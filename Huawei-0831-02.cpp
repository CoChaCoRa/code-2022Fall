/*
 *   给一个n*m的矩阵，其中元素值为0表示空地，1表示障碍，2是起点，3是重点，4是陷阱，6是炸弹。
 *   任务：从2开始走到3。每走1格花费1个单位时间。1不能走，4要花费3个单位时间，走到6能把上下左右的1置0。
 *   输出：从2到3的最短路径。
 */

// DFS + 剪枝 需要注意（1）将当前节点置1防止走回头路；（2）回溯时不仅要恢复当前节点，还要恢复被炸弹炸开的节点

#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

int m, n;
int bestStep = INT_MAX;
vector<vector<int>> maze;
pair<int, int> start;

void dfs(int row, int col, int curStep);

int main()
{
    ifstream infile;
    infile.open("huawei-0831-02.txt");
    infile >> m >> n;
    maze = vector<vector<int>>(m, vector<int>(n));
    for(int i = 0; i < m; ++i) {
        for(int j = 0; j < n; ++j) {
            infile>>maze[i][j];
            if(maze[i][j] == 2) {
                start.first = i;
                start.second = j;
            }
        }
    }
    infile.close();
    for(int i = 0; i < m; ++i) {
        for(int j = 0; j < n; ++j) {
            cout << maze[i][j] << ' ';
        }
        cout<<endl;
    }
    
    dfs(start.first, start.second, 0);

    cout<<bestStep<<endl;
}

void dfs(int row, int col, int curStep) {
    // cout<<"Current position: ("<<row<<", "<<col<<"), Step: "<< curStep <<endl;
    if(row < 0 || row >= m || col < 0 || col >= n || maze[row][col] == 1) return;
    
    int curVal = maze[row][col];

    if(curVal == 3){
        bestStep = bestStep < curStep ? bestStep : curStep;
    }

    if(curVal == 4) {
        curStep += 3;
    }

    int originW, originS, originA, originD;
    if(curVal == 6) {
        if(row > 0) {
            originW = maze[row - 1][col];
            maze[row - 1][col] = 0;
        }
        if(row < m - 1) {
            originS = maze[row + 1][col];
            maze[row + 1][col] = 0;
        }
        if(col > 0) {
            originA = maze[row][col - 1];
            maze[row][col - 1] = 0;
        }
        if(col < n - 1) {
            originD = maze[row][col + 1];
            maze[row][col + 1] = 0;
        }
    }

    ++curStep;
    maze[row][col] = 1; // 防止走回头路
    dfs(row - 1, col, curStep);
    dfs(row + 1, col, curStep);
    dfs(row, col - 1, curStep);
    dfs(row, col + 1, curStep);

    // 还原
    maze[row][col] = curVal;
    if(curVal == 6) {
        if(row > 0) {
            maze[row - 1][col] = originW;
        }
        if(row < m - 1) {
            maze[row + 1][col] = originS;
        }
        if(col > 0) {
            maze[row][col - 1] = originA;
        }
        if(col < n - 1) {
            maze[row][col + 1] = originD;
        }
    }

    return;
}