/*
    问题描述：给定凸多边形P，要求确定该凸多边形的三角剖分，使得该三角剖分中诸三角形的周长之和最小。
*/

#include<bits/stdc++.h>
using namespace std;
#define MAXN 105 // 假设点的数量不超过100
#define INF 0x7FFFFFFF

int dist[MAXN][MAXN]; // dist[i][j]表示点i和点j之间的距离
long long dp[MAXN][MAXN]; // dp[i][j]表示从点i到点j的最小三角剖分周长和
int split[MAXN][MAXN]; // split[i][j]记录点i到点j的最优分割点
vector<tuple<int, int, int>> triangles; // 用于存储三角形的顶点
int n; // 点的数量

// 递归收集三角形顶点（i, j 是 0-indexed）
void collectTriangles(int i, int j) {
    if (j - i < 2) return; // 少于3个点无法构成三角形
    int k = split[i][j];
    triangles.push_back(make_tuple(i + 1, k + 1, j + 1)); // 转为1-indexed
    collectTriangles(i, k);
    collectTriangles(k, j);
}

int main() {
    freopen("TriangleDevision.in", "r", stdin);
    freopen("TriangleDevision.out", "w", stdout);
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> dist[i][j];
        }
    }

    // 初始化 dp 和 split
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            dp[i][j] = 0;
            split[i][j] = -1;
        }
    }
    
    // 动态规划计算最小三角剖分周长和
    for (int len = 2; len < n; len++) {          // len = j - i
        for (int i = 0; i + len < n; i++) {
            int j = i + len;
            dp[i][j] = INF;
            for (int k = i + 1; k < j; k++) {
                long long cost = dp[i][k] + dp[k][j] + dist[i][k] + dist[k][j] + dist[i][j];
                if (cost < dp[i][j]) {
                    dp[i][j] = cost;
                    split[i][j] = k;
                }
            }
        }
    }

    // 收集三角形顶点
    collectTriangles(0, n - 1);

    // 输出最小三角剖分周长和
    cout << dp[0][n - 1] << "\n";
    
    // 输出三角形顶点
    for (size_t i = 0; i < triangles.size(); ++i) {
        cout << get<0>(triangles[i]) << " " << get<1>(triangles[i]) << " " << get<2>(triangles[i]) << "\n";
    }

    return 0;
}