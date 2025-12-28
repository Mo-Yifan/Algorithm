//代码实现了求两个序列的最长公共子序列（LCS）长度及其内容的功能。
#include<bits/stdc++.h>
using namespace std;
#define MAXN 1005 // 假设序列长度不超过 1000

int dp[MAXN][MAXN]; // dp[i][j] 表示 A[0..i-1] 和 B[0..j-1] 的最长公共子序列长度
string A, B; // 输入的两个序列
vector<char> lcs_sequence; // 用于存储最长公共子序列

void printLCS(int i, int j) {
    if (i == 0 || j == 0) return;
    if (A[i - 1] == B[j - 1]) {
        printLCS(i - 1, j - 1);
        lcs_sequence.push_back(A[i - 1]);
    } else if (dp[i - 1][j] > dp[i][j - 1]) {
        printLCS(i - 1, j);
    } else {
        printLCS(i, j - 1);
    }
}

int main() {
    freopen("LongestSubseq.in", "r", stdin);
    freopen("LongestSubseq.out", "w", stdout);
    cin >> A >> B;
    int n = A.length();
    int m = B.length();

    // 初始化 dp 数组
    for (int i = 0; i <= n; ++i) {
        dp[i][0] = 0;
    }
    for (int j = 0; j <= m; ++j) {
        dp[0][j] = 0;
    }

    // 填充 dp 数组
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (A[i - 1] == B[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } 
            else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    // 输出最长公共子序列长度
    cout << dp[n][m] << endl;

    // 回溯输出最长公共子序列
    printLCS(n, m);
    for (char c : lcs_sequence) {
        cout << c;
    }
    cout << endl;

    return 0;
}