#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

const long long INF = 1e18;

long long solveLinear(const vector<long long>& vals, const vector<char>& ops) {
    int n = vals.size();
    if (n == 1) return vals[0];

    // DP tables
    vector<vector<long long>> max_dp(n, vector<long long>(n, -INF));
    vector<vector<long long>> min_dp(n, vector<long long>(n, INF));

    // 初始化：单个顶点的值
    for (int i = 0; i < n; ++i) {
        max_dp[i][i] = min_dp[i][i] = vals[i];
    }

    // 填充 DP 表
    for (int len = 2; len <= n; ++len) {
        for (int i = 0; i <= n - len; ++i) {
            int j = i + len - 1;
            max_dp[i][j] = -INF;
            min_dp[i][j] = INF;

            // 枚举从 i 到 j 的每一个分割点 k，将区间分为 [i..k] 和 [k+1..j]，决定删去哪个边，合并哪两个点
            for (int k = i; k < j; ++k) {
                long long maxL = max_dp[i][k];      // 从第 i 个到第 k 个顶点的最大值
                long long minL = min_dp[i][k];      // 从第 i 个到第 k 个顶点的最小值
                long long maxR = max_dp[k+1][j];    // 从第 k+1 个到第 j 个顶点的最大值
                long long minR = min_dp[k+1][j];    // 从第 k+1 个到第 j 个顶点的最小值
                char op = ops[k]; // operator between vals[k] and vals[k+1]

                long long candidates[4];
                long long val_max, val_min;

                if (op == '+') {
                    val_max = maxL + maxR;
                    val_min = minL + minR;
                } 
                else {                          //因为两个负数相乘会变成正数，所以需要考虑四种情况
                    candidates[0] = maxL * maxR;
                    candidates[1] = maxL * minR;
                    candidates[2] = minL * maxR;
                    candidates[3] = minL * minR;
                    val_max = *max_element(candidates, candidates + 4);
                    val_min = *min_element(candidates, candidates + 4);
                }

                if (val_max > max_dp[i][j]) max_dp[i][j] = val_max;
                if (val_min < min_dp[i][j]) min_dp[i][j] = val_min;
            }
        }
    }

    return max_dp[0][n-1];
}

int main() {
    freopen("PolygonGame.in", "r", stdin);
    freopen("PolygonGame.out", "w", stdout);

    int N;
    cin >> N;

    vector<long long> vertex(N);
    vector<char> op(N);

    // Read vertex values (N integers)
    for (int i = 0; i < N; ++i) {
        cin >> vertex[i];
    }

    // Read operators (N characters, may have spaces)
    for (int i = 0; i < N; ++i) {
        cin >> op[i];
    }

    long long global_max = -INF;

    // Try removing each edge (edge i connects vertex[i] and vertex[(i+1)%N])
    // Edge index in input: 1 to N → array index: 0 to N-1
    for (int cut = 0; cut < N; ++cut) {
        // Remove edge 'cut' (which is op[cut])
        // New chain starts at vertex[(cut + 1) % N]
        vector<long long> vals;
        vector<char> ops;

        // Build vertex sequence of length N
        for (int i = 0; i < N; ++i) {
            vals.push_back(vertex[(cut + 1 + i) % N]);
        }

        // Build operator sequence of length N-1
        // These are the edges that remain: all except op[cut]
        // They are: op[(cut+1)%N], op[(cut+2)%N], ..., op[(cut-1+N)%N]
        for (int i = 0; i < N - 1; ++i) {
            ops.push_back(op[(cut + 1 + i) % N]);
        }

        long long score = solveLinear(vals, ops);
        if (score > global_max) {
            global_max = score;
        }
    }

    cout << global_max << endl;

    return 0;
}