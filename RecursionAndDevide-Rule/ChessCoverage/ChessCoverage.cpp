/*
    问题描述：在一个2^k×2^k 个方格组成的棋盘中，恰有一个方格与其它方格不同，
    称该方格为一特殊方格，且称该棋盘为一特殊棋盘。在棋盘覆盖问题中，要用图
    示的4种不同形态的L型骨牌覆盖给定的特殊棋盘上除特殊方格以外的所有方格，
    且任何2个L型骨牌不得重叠覆盖。
*/

#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

const int MAXN = 9;
int board[1 << MAXN][1 << MAXN];  //棋盘

//覆盖棋盘的函数，(tr, tc)为棋盘左上角坐标，size为棋盘边长，(dr, dc)为特殊方格坐标
void cover(int tr, int tc, int size, int dr, int dc){
    if(size == 1) return; //棋盘大小为1，直接返回

    int type;  //骨牌的类型，从1到4分别为右下角缺口、左下角缺口、右上角缺口、左上角缺口
    int s = size / 2;    //子棋盘边长

    //特殊方格在左上子棋盘
    if(dr < tr + s && dc < tc + s){
        cover(tr, tc, s, dr, dc);                     //递归覆盖左上子棋盘
        type = 4;                                     //确定骨牌类型
        board[tr + s - 1][tc + s] = type;             //放置骨牌
        board[tr + s][tc + s - 1] = type;
        board[tr + s][tc + s] = type;
        cover(tr, tc + s, s, tr + s - 1, tc + s);     //递归覆盖右上子棋盘
        cover(tr + s, tc, s, tr + s, tc + s - 1);     //递归覆盖左下子棋盘
        cover(tr + s, tc + s, s, tr + s, tc + s);     //递归覆盖右下子棋盘
    }
    //特殊方格在右上子棋盘
    else if(dr < tr + s && dc >= tc + s){
        cover(tr, tc + s, s, dr, dc);                 //递归覆盖右上子棋盘
        type = 3;                                     //确定骨牌类型
        board[tr + s - 1][tc + s - 1] = type;         //放置骨牌
        board[tr + s][tc + s - 1] = type;
        board[tr + s][tc + s] = type;
        cover(tr, tc, s, tr + s - 1, tc + s - 1);     //递归覆盖左上子棋盘
        cover(tr + s, tc, s, tr + s, tc + s - 1);     //递归覆盖左下子棋盘
        cover(tr + s, tc + s, s, tr + s, tc + s);     //递归覆盖右下子棋盘
    }
    //特殊方格在左下子棋盘
    else if(dr >= tr + s && dc < tc + s){
        cover(tr + s, tc, s, dr, dc);                 //递归覆盖左下子棋盘
        type = 2;                                     //确定骨牌类型
        board[tr + s - 1][tc + s - 1] = type;            //放置骨牌
        board[tr + s - 1][tc + s] = type;
        board[tr + s][tc + s] = type;
        cover(tr, tc, s, tr + s - 1, tc + s - 1);     //递归覆盖左上子棋盘
        cover(tr, tc + s, s, tr + s - 1, tc + s);     //递归覆盖右上子棋盘
        cover(tr + s, tc + s, s, tr + s, tc + s);     //递归覆盖右下子棋盘
    }
    //特殊方格在右下子棋盘
    else{
        cover(tr + s, tc + s, s, dr, dc);             //递归覆盖右下子棋盘
        type = 1;                                     //确定骨牌类型
        board[tr + s - 1][tc + s - 1] = type;            //放置骨牌
        board[tr + s - 1][tc + s] = type;
        board[tr + s][tc + s - 1] = type;
        cover(tr, tc, s, tr + s - 1, tc + s - 1);     //递归覆盖左上子棋盘
        cover(tr, tc + s, s, tr + s - 1, tc + s);     //递归覆盖右上子棋盘
        cover(tr + s, tc, s, tr + s, tc + s - 1);     //递归覆盖左下子棋盘
    }
}

int main(){
    freopen("chess.in", "r", stdin);
    freopen("chess.out", "w", stdout);

    memset(board, 0, sizeof(board));  //初始化棋盘

    int k, dr, dc;
    cin >> k >> dr >> dc;
    int size = 1 << k;  //计算棋盘边长2^k

    cover(0, 0, size, dr, dc);  //覆盖棋盘

    //输出结果
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            cout << board[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}