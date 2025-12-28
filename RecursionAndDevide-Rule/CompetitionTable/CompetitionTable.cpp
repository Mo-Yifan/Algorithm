/*
    问题描述：
    设计一个满足以下要求的比赛日程表：
    (1)每个选手必须与其他n-1个选手各赛一次；
    (2)每个选手一天只能赛一次；
    (3)循环赛一共进行n-1天。
*/

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

void Table(int k,int n,int **a)  
{  
    for(int i=1; i<=n; i++)  
        a[1][i]=i;//设置日程表第一行 
    int m = 1;//每次填充时，起始填充位置  
    for(int s=1; s<=k; s++)  
    {  
        n /= 2;  
        for(int t=1; t<=n; t++)  
        {  
            for(int i=m+1; i<=2*m; i++)//控制行  
            {  
                for(int j=m+1; j<=2*m; j++)//控制列  
                {  
                    a[i][j+(t-1)*m*2] = a[i-m][j+(t-1)*m*2-m];//右下角等于左上角  
                    a[i][j+(t-1)*m*2-m] = a[i-m][j+(t-1)*m*2];//左下角等于右上角  
                }                   
            }  
        }  
        m *= 2;  
    }  
}  

int main() {
    freopen("competitiontable.in", "r", stdin);
    freopen("competitiontable.out", "w", stdout);

    int k, n;   //k为轮数，n为选手数
    cin >> k >> n;
    int **a = new int*[n+1];
    for(int i=0; i<=n; i++) a[i] = new int[n+1];
    Table(k, n, a);
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            cout << a[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}