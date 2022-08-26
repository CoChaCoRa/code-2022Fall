/*
 *   微软笔试题
 *   输入：字符串S，'a' - 'z'
 *   输出：每个字母出现偶数次的最长子序列长度
 *   例如：abcabc，输出6
 */

#include <iostream>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

int main() {
    string S = "aadbbcefghhgfj";
    
    int n = S.length();
    int state = 0;
    map<int, int> m;
    m[state] = -1;
    int maxLen = 0;
    for(int i = 0; i < n; ++i) {
        state ^= 2 << S[i] - 'a';
        if(!m.count(state)) {
            m[state] = i;
        }
        else{
            int distance = i - m[state];
            maxLen = max(maxLen, distance);
        }
    }
    cout<<maxLen<<endl;

    return 0;
}