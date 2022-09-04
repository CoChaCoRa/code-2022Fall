#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

vector<int> buildNext(string needle) {
    vector<int> next(needle.size(),0);
    int x = 1, now = 0;
    while(x < needle.length()) {
        if(needle[x] == needle[now]) {
            ++x;
            ++now;
            next[x] = now;
        }
        else if(now) {
            now = next[now - 1];
        }
        else {
            next[x] = 0;
            ++x;
        }
    }
    return next;
}

int strStr(string haystack, string needle) {
    if(needle.length() == 0) return 0;

    vector<int> nex;
    nex = buildNext(needle);

    int tar = 0, pos = 0;
    while(tar < haystack.length()) {
        if(haystack[tar] == needle[pos]) {
            ++tar;
            ++pos;
        }
        else {
            if(pos == 0) ++tar;
            else pos = nex[pos - 1];
        }
        if(pos == needle.length()) {
            return tar - needle.length();
        }
    }

    return -1;
}

int main()
{
    string haystack = "hello";
    string needle = "ll";
    cout<<strStr(haystack, needle)<<endl;
}