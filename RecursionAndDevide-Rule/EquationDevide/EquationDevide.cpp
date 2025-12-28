#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

// 全局变量用于计数（或通过引用传递）
int totalCount = 0;

void dfs(int n, int remaining, int maxAllowed, vector<int>& current) {
    if (remaining == 0) {
        if (current.size() >= 2) {
            // 输出划分
            cout << n << "=" << current[0];
            for (size_t i = 1; i < current.size(); ++i) {
                cout << "+" << current[i];
            }
            cout << endl;
            totalCount++;
        }
        return;
    }

    // 下一个加数不能超过 min(remaining, maxAllowed)，且 ≥1
    int upper = min(remaining, maxAllowed);
    for (int next = upper; next >= 1; --next) {
        current.push_back(next);
        dfs(n, remaining - next, next, current); // 非增：下一次最大为 next
        current.pop_back();
    }
}

int main() {
    freopen("equationdevide.in", "r", stdin);
    freopen("equationdevide.out", "w", stdout);

    int n, m;
    cin >> n >> m;

    totalCount = 0;
    vector<int> current;

    // 第一个加数最大只能是 min(n-1, m)（因为至少两项，所以不能是 n）
    int firstMax = min(n - 1, m);
    for (int first = firstMax; first >= 1; --first) {
        current.clear();
        current.push_back(first);
        dfs(n, n - first, first, current);
    }

    // 输出总方案数
    cout << totalCount << endl;

    return 0;
}