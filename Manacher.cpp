#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string manacher(const string &);
string preprocess(const string &);
int expand(const string &, int, int);
string postprocess(const string &, int, int);

int main() {
    string s = "acbbcbe";
    cout<<manacher(s)<<endl;
}

string manacher(const string &s) {
    string s_new = preprocess(s);
    int n = s_new.length();
    vector<int> arm_len(n, 0);
    int last_center = -1, right_bound = -1;
    int start = -1, last = -1;
    for(int i = 0; i < n; ++i) {
        if(i <= right_bound) {
            int i_mirror = 2 * last_center - i;
            int skip_arm_len = arm_len[i_mirror];
            int arm_len_new = expand(s_new, i - skip_arm_len, i + skip_arm_len);
            arm_len[i] = arm_len_new;
        }
        else {
            int arm_len_new = expand(s_new, i, i);
            arm_len[i] = arm_len_new;
        }
        if(i + arm_len[i] > right_bound) {
            last_center = i;
            right_bound = i + arm_len[i];
        }
        if(2 * arm_len[i] + 1 > last - start) {
            start = i - arm_len[i];
            last = i + arm_len[i];
        }
    }
    return postprocess(s_new, start, last);
}

string preprocess(const string &s) {
    string t;
    t.append(1, '#');
    for(auto c : s) {
        t.append(1, c);
        t.append(1, '#');
    }
    return t;
}

int expand(const string &s, int l, int r) {
    while(l >= 0 && r < s.length()) {
        if(s[l] == s[r]) {
            --l;
            ++r;
        }
        else break;
    }
    ++l;
    --r;
    return (r - l) >> 1;
}

string postprocess(const string &s, int start, int last) {
    string t;
    for(int i = start; i <= last; ++i) {
        if(s[i] != '#') {
            t.append(1, s[i]);
        }
    }
    return t;
}