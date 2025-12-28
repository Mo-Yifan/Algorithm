//代码实现了求一个数列的最大子段和问题，使用动态规划的方法。
#include<bits/stdc++.h>
using namespace std;
#define MAXN 100005 // 假设序列长度不超过 100000

int dp[MAXN]; // dp[i] 表示以第 i 个元素结尾的最大子段和
int arr[MAXN]; // 输入的数列
int n; // 数列长度

int maxSubseqSum() {
    dp[0] = arr[0];
    int maxSum = dp[0];
    for (int i = 1; i < n; ++i) {
        dp[i] = max(arr[i], dp[i - 1] + arr[i]);    //状态转移：如果当前位置的值更大，则从这里直接开始
        if (dp[i] > maxSum) {
            maxSum = dp[i];
        }
    }
    return maxSum;
}

int main(){
    freopen("MaxSubseqSum.in", "r", stdin);
    freopen("MaxSubseqSum.out", "w", stdout);
    cin >> n;
    for(int i = 0; i < n; ++i){
        cin >> arr[i];
    }
    int result = maxSubseqSum();
    cout << max(result, 0) << endl;     //如果最大子段和为负数，则输出0，表示整个数列全为负数
    return 0;
}