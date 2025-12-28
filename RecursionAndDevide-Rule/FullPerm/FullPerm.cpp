//代码呈现了如何使用递归策略生成全排列

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

template<class Type>
void my_swap(Type& a, Type& b) {
    Type temp = a;
    a = b;
    b = temp;
}

// 通用递归全排列函数（模板）
template<class Type>
void perm(vector<Type>& R, int k, int m, int& count) {
    if(k == m){
        cout<<"Permutation "<< ++count<< ": ";
        for(int i = 0; i <= m; i++){
            cout<< R[i];
            if(i != m) cout<<", ";
        }
        cout<<endl;
    }
    else{
        for(int i = k; i <= m; i++){
            swap(R[k], R[i]);
            perm(R, k + 1, m, count);
            swap(R[k], R[i]);
        }
    }
}

int main() {
    // 重定向标准输入输出到文件
    freopen("perm.in", "r", stdin);
    freopen("perm.out", "w", stdout);

    vector<string> R;
    string line;

    // 逐行读取 perm.in 中的每个元素（支持含空格的元素）
    while (getline(cin, line)) {
        // 可选：跳过空行
        if (line.empty()) continue;
        R.push_back(line);
    }

    if (R.empty()) {
        cout << "No elements provided.\n";
        fclose(stdin);
        fclose(stdout);
        return 0;
    }
    int count = 0;

    // 生成全排列（使用 string 实例化模板）
    perm<string>(R, 0, R.size() - 1, count);

    // 输出结果到 output.out
    cout << "Total permutations: " << count << "\n";
    
    return 0;
}