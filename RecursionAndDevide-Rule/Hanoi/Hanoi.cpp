//代码实现了汉诺塔游戏每一步的移动过程
#include<iostream>
using namespace std;

int step = 0;  //全局变量用于计数步数
/*表示目前有n个圆盘，需要从起始柱子s移动到目标柱子d，借助辅助柱子via*/
void move(int n, char s, char d, char via){
    if(n == 1){
        cout << "Step" << ++step << ": " << s << "->" << d << endl;   //只有一个圆盘，直接从起始柱子移动到目标柱子
        return ;
    }
    else{
        move(n-1, s, via, d);              //将上面的n-1个圆盘从起始柱子移动到辅助柱子
        cout << "Step" << ++step << ": " << s << "->" << d << endl;   //将第n个圆盘从起始柱子移动到目标柱子
        move(n-1, via, d, s);              //将辅助柱子上的n-1个圆盘移动到目标柱子
    }
}

int main(){
    freopen("hanoi.in", "r", stdin);
    freopen("hanoi.out", "w", stdout);
    int n;
    cin >> n;
    move(n, 'A', 'C', 'B');  //A是起始柱子，C是目标柱子，B是辅助柱子
    cout << "Total steps: " << step;
    return 0;
}