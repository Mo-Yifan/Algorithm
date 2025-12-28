#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <sstream>

using namespace std;

struct Container {
    int id;
    int weight;
};

// ========== 快速排序实现 =============
void swap(Container& a, Container& b) {
    Container temp = a;
    a = b;
    b = temp;
}

int Partition(vector<Container>& arr, int low, int high) {
    Container pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j].weight <= pivot.weight) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void Quicksort(vector<Container>& arr, int low, int high) {
    if (low < high) {
        int pi = Partition(arr, low, high);
        Quicksort(arr, low, pi - 1);
        Quicksort(arr, pi + 1, high);
    }
}

// ======== 处理全角逗号函数 =======
void normalizeComma(std::string& s) {
    // 全角逗号 "，" 的 UTF-8 编码是 \xEF\xBC\x8C
    const std::string fullwidth_comma = "\xEF\xBC\x8C";
    size_t pos = 0;
    while ((pos = s.find(fullwidth_comma, pos)) != std::string::npos) {
        s.replace(pos, fullwidth_comma.length(), ",");
        pos += 1; // 替换后从下一个位置继续（"," 长度为1）
    }
}

int main() {
    // 输入输出重定向（根据题目要求）
    freopen("BoxScheduling_input.txt", "r", stdin);
    freopen("BoxScheduling_output.txt", "w", stdout);

    //int C;
    //cin >> C;
    //cin.ignore(); // 忽略换行符

    vector<Container> containers;
    string line;

    while (getline(cin, line)) {
        if (line.empty()) continue; // 跳过空行

        normalizeComma(line); // 统一逗号为半角

        // 使用 stringstream 分割
        stringstream ss(line);
        string token;
        vector<string> tokens;
        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        if (tokens.size() != 2) continue; // 格式错误跳过

        // 去除前后空格
        auto trim = [](string& str) {
            size_t start = str.find_first_not_of(" \t\r\n");
            size_t end = str.find_last_not_of(" \t\rn");
            if (start == string::npos) {
                str = "";
            } else {
                str = str.substr(start, end - start + 1);
            }
        };

        trim(tokens[0]);
        trim(tokens[1]);

        if (tokens[0].empty() || tokens[1].empty()) continue;

        try {
            int id = stoi(tokens[0]);
            int weight = stoi(tokens[1]);
            containers.push_back({id, weight});
        } catch (...) {
            // 转换失败则跳过该行
            continue;
        }
    }

    Quicksort(containers, 0, containers.size() - 1);

    // 输出排序后的所有集装箱
    for (const auto& c : containers) {
        cout << c.id << "," << c.weight << endl;
    }
    
    /*
    // 贪心选择：尽可能多地装集装箱
    vector<int> loaded;
    int currentWeight = 0;

    for (const auto& c : containers) {
        if (currentWeight + c.weight <= C) {
            loaded.push_back(c.id);
            currentWeight += c.weight;
        } else {
            break;
        }
    }

    // 输出上船的集装箱编号（一行一个）
    for (int id : loaded) {
        cout << id << endl;
    }
    */

    // 关闭文件（可选）
    fclose(stdin);
    fclose(stdout);

    return 0;
}