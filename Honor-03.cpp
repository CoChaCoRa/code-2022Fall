/*
 *   荣耀0825笔试第三题
 *   输入：长度为N的int数组，元素为各item体积
 *   输出：仓库最小容积，使得两个这样的仓库能容纳所有item
 */
#include <iostream>
#include <numeric>
#include <vector>
#include <algorithm>

using namespace std;

int minCapcity(int a[], int n)
{
    int sum = accumulate(a, a + n, 0);
    int halfSum = sum / 2;
    vector<int> dp(halfSum + 1);
    for (int cap = 0; cap <= halfSum; ++cap)
        dp[cap] = cap >= a[0] ? a[0] : 0;

    for (int i = 0; i < n; ++i)
    {
        for (int cap = halfSum; cap >= 0; --cap)
        {
            dp[cap] = cap >= a[i] ? max(dp[cap], dp[cap - a[i]] + a[i]) : dp[cap];
        }
    }

    return sum - dp[halfSum];
}

int main()
{
    int items[] = {2,3,4,5,6};
    cout << minCapcity(items, 5) << endl;

    return 0;
}
