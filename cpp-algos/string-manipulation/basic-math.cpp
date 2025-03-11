#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>

using namespace std;

class Solution {
    unordered_map<string, int> lookup;

public:
    Solution() {
        lookup["one"] = 1;
        lookup["two"] = 2;
        lookup["three"] = 3;
        lookup["four"] = 4;
        lookup["five"] = 5;
    }


    int solve_expression(const string& s) {
        int res = 0;
        bool add = true;

        int i = 0, n = s.size();
        while (i < n) {
            int start = i;
            while (i < n && isalpha(s[i])) {
                i++;
            }
            int end = i;
            if (end > start) {
                int num = lookup[s.substr(start, end - start)];
                if (add)
                    res += num;
                else
                    res -= num;
            }

            if (s[i] == '+')
                add = true;
            else
                add = false;
            i++;
        }

        return res;
    }
};


int main() {
    Solution s;
    cout << s.solve_expression("one-three+four+five-two") << endl; // expecting 5
    cout << s.solve_expression("-one-five") << endl; // expecting -6
}