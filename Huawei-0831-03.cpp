/*
 *   从A地开车到B地，距离为D（0-1000000）。车续航是1000公里，速度是100km/h。A到B之间有N个充电站，充电可能需要排队，固定花1小时充满。
 *   输入：
 *   D N
 *   充电站1到起点距离  充电排队时长
 *   充电站2到起点距离  充电排队时长
 *   ...
 *   充电站N到起点距离  充电排队时长
 *   输出：最短时间。如果无法到达输出-1。
 *   1500    4
 *   300     0
 *   600     1
 *   1000    0
 *   1200    1
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

int main()
{
    ifstream infile;
    infile.open("examples.txt");
    int N , D;
    infile>>N>>D;
    vector<pair<int, int>> stations;
    int dis, waiting;
    stations.push_back(make_pair(0, 0));
    while (infile >> dis >> waiting)
    {
        stations.push_back(make_pair(dis, waiting));
    }
    stations.push_back(make_pair(N, 0));

    vector<int> dp(D + 2, 1e7);
    dp[0] = 0;
    for (int i = 1; i < D + 2; ++i)
    {
        for (int j = i - 1; j >= 0; --j)
        {
            if (stations[i].first - stations[j].first > 1000)
                continue;
            else
            {
                int distance = stations[i].first - stations[j].first;
                int timeCost = dp[j] + stations[j].second + (distance / 100);
                if (j != 0)
                    ++timeCost;
                dp[i] = min(dp[i], timeCost);
            }
        }
        if (dp[i] == 1e7)
        {
            cout << -1 << endl;
            return 0;
        }
    }

    cout << dp[D + 1] << endl;
    return 0;
}