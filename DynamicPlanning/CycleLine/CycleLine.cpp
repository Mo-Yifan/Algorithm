#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#define MAXN 100005
using namespace std;
int pi[MAXN]; // pi[i] 表示上端 i 连到下端 pi[i]
int dp[MAXN]; // dp 数组用于存储最长不相交连线数

int main() {
    freopen("CycleLine.in", "r", stdin);
    freopen("CycleLine.out", "w", stdout);
    int n;
    cin >> n;

    for (int i = 1; i <= n; i++) {
        int p, q;
        cin >> p >> q;
        pi[p] = q;  
        dp[i] = 1; // 初始化 dp 数组，每个位置的最小值为 1
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < i; j++) {
            if (pi[j] < pi[i]) {
                if (dp[j] + 1 > dp[i]) {
                    dp[i] = dp[j] + 1;
                }
            }
        }
    }

    // 找最大长度
    int max_len = 0;
    for (int i = 1; i <= n; i++) {
        if (dp[i] > max_len) {
            max_len = dp[i];
        }
    }

    // 从后往前找字典序最小的方案
    vector<int> selected; // 存选中的上端编号 i
    int last_i = n + 1;   // 上一次选的位置（初始设为 n+1）
    int last_val = 1000000000; // 上一次选的下端编号（设一个很大的数）

    // 从 LIS 的最后一层（max_len）往回找
    for (int level = max_len; level >= 1; level--) {
        // 从前往后找第一个符合条件的 i
        for (int i = 1; i < last_i; i++) {
            if (dp[i] == level && pi[i] < last_val) {
                selected.push_back(i);
                last_val = pi[i];
                last_i = i;
                break; // 找到就跳出，保证选最小的 i
            }
        }
    }

    // 因为我们是从后往前找的，所以要反转
    vector<int> result;
    for (int i = selected.size() - 1; i >= 0; i--) {
        result.push_back(selected[i]);
    }

    // 输出
    cout << max_len << endl;
    for (int i = 0; i < result.size(); i++) {
        int idx = result[i];
        cout << idx << " " << pi[idx] << endl;
    }

    return 0;
}