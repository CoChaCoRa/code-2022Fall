/*
 *   题干：平面上有N个矩形，定义有效矩形为 和其他矩形有重叠部分 的矩阵
 *       矩形(0,0,2,2)和(1,1,4,3)有交叉，两者是有效矩形，覆盖面积为9 (4+6-1)
 *       矩形(2,4,4,7)包含(2,5,3,6)，两者是有效矩形，覆盖面积为6 (6+1-1)
 *   输入：N个长度为4的数组(x0, y0, x1, y1)，保证0<=x0<x1<=1000, 0<=y0<y1<=1000
 *   输出：有效矩阵的覆盖面积
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int space[1000][1000] = {0};

void paintArea(vector<int> &rectangle) {
    for(int x = rectangle[0]; x < rectangle[2]; ++x){
        for(int y = rectangle[1]; y < rectangle[3]; ++y) {
            space[x][y] = 1;
        }
    }
}

int getSum() {
    int sum = 0;
    for(int i = 0; i < 1000; ++i) {
        for(int j = 0; j < 1000; ++j) {
            sum += space[i][j];
        }
    }
    return sum;
}

inline void checkIfValid(vector<vector<int>> &rectangles, int left, int right, vector<bool> &isValid)
{
    if (rectangles[left][2] > rectangles[right][0] ||
        rectangles[left][2] >= rectangles[right][2])
    {
        isValid[left] = true;
        isValid[right] = true;
    }
}

bool myCompare(vector<int> &lhs, vector<int> &rhs)
{
    return lhs[0] == rhs[0] ? (lhs[1] <= rhs[1]) : (lhs[0] <= rhs[0]);
}

int main()
{
    vector<vector<int>> rectangles = {{0, 0, 2, 2}, {1, 1, 4, 3}, {2, 4, 4, 7}, {2, 5, 3, 6}};

    int N = rectangles.size();
    vector<bool> isValid(N, false);
    sort(rectangles.begin(),rectangles.end(),myCompare);
    for(int i = 0; i < N; ++i) {
        for(int j = i + 1; j < N; ++j) checkIfValid(rectangles, i, j, isValid);
    }
    for(int i = 0; i < N; ++i) {
        if(isValid[i]) paintArea(rectangles[i]);
    }
    cout << getSum() <<endl;

    return 0;
}