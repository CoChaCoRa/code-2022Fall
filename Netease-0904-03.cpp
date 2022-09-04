/*
 *   输入数组，每次可以选择其中一个数减去x。希望k次操作后，该数组的最大值尽可能小。
 *   输入描述：
 *   第一行输入三个正整数n, k, x。代表数组长度、操作次数、减去的固定值。
 *   第二行输入n个正整数ai，表示输入数组。
 *   n : [1,10^5],   ai, k, x : [1,10^9]
 *   输出：k次操作后数组尽可能小的最大值
 */

// 尽可能小的最大值/尽可能大的最小值 -> 二分

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <time.h>

using namespace std;

int n, k, x;
vector<int> nums;

inline int countOperations(long long val, long long tar)
{
    if (tar >= val)
        return 0;
    int count = (val - tar + x - 1) / x;
    return count;
}

long long int getMin()
{
    long long int left = -1e18, right = 1e18;
    while (left <= right)
    {
        long long int mid = (left + right) >> 1;
        long long int count = 0;
        for (auto v : nums)
        {
            count += countOperations(v, mid);
        }
        if (count == k)
            return mid;
        if (count > k)
        {
            left = mid + 1;
        }
        if (count < k)
        {
            right = mid - 1;
        }
    }
    return INT_MAX;
}

int main()
{   
    clock_t start,end;
    start = clock();

    ifstream infile;
    infile.open("netease-0904-03.txt");
    infile >> n >> k >> x;
    nums.resize(n);
    for (int i = 0; i < n; ++i)
        infile >> nums[i];
    infile.close();

    cout << getMin() << endl;

    end = clock();
    cout<<"time = "<<double(end-start)/CLOCKS_PER_SEC<<"s"<<endl;
}