#include <iostream>
#include <vector>
#include <climits>
using namespace std;

const int MAXN = 505;  // 假设 n <= 500

long long dp[MAXN][MAXN];
int split[MAXN][MAXN];
vector<pair<int, int> > brackets;
int d[MAXN];           // 维度数组 d[0..n]
int n_global;          // 全局 n，用于 collectBrackets 边界判断（其实不需要）

// 递归收集括号区间（i, j 是 0-indexed）
void collectBrackets(int i, int j) {
    if (i == j) return;
    // 当前子表达式 [i, j] 需要一对括号（因为不是单个矩阵）
    brackets.push_back(make_pair(i + 1, j + 1)); // 转为 1-indexed
    int k = split[i][j];
    collectBrackets(i, k);
    collectBrackets(k + 1, j);
}

int main() {
    freopen("MatrixMul.in", "r", stdin);
    freopen("MatrixMul.out", "w", stdout);
    int n;
    cin >> n;

    if (n == 1) {
        cout << 0 << endl;
        return 0;
    }

    vector<int> p(n), q(n);
    for (int i = 0; i < n; ++i) {
        cin >> p[i] >> q[i];
    }

    // 构建维度数组 d[0..n]
    d[0] = p[0];
    for (int i = 0; i < n; ++i) {
        d[i + 1] = q[i];
    }

    // 初始化 dp 和 split
    for (int i = 0; i < n; ++i) {
        dp[i][i] = 0;
        split[i][i] = -1;
    }

    // 动态规划：len 从 2 到 n
    for (int len = 2; len <= n; ++len) {
        for (int i = 0; i <= n - len; ++i) {
            int j = i + len - 1;
            dp[i][j] = LLONG_MAX;
            split[i][j] = -1;
            for (int k = i; k < j; ++k) {
                long long cost = dp[i][k] + dp[k + 1][j] + 1LL * d[i] * d[k + 1] * d[j + 1];
                if (cost < dp[i][j]) {
                    dp[i][j] = cost;
                    split[i][j] = k;
                }
            }
        }
    }

    // 清空括号列表
    brackets.clear();

    // 获取整条链的最优分割点（根）
    int root_k = split[0][n - 1];

    // 只对左右子表达式递归收集括号（跳过最外层 [0, n-1]）
    collectBrackets(0, root_k);
    collectBrackets(root_k + 1, n - 1);

    // 输出结果
    cout << brackets.size() << "\n";
    for (int i = 0; i < brackets.size(); ++i) {
        cout << brackets[i].first << " " << brackets[i].second << "\n";
    }

    //输出最小乘法次数
    cout << dp[0][n - 1] << "\n";

    return 0;
}