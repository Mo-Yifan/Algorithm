#include <bits/stdc++.h>
using namespace std;

struct Point {
    double x, y;
};

bool cmpX(const Point& a, const Point& b) {
    return a.x < b.x;
}
bool cmpY(const Point& a, const Point& b) {
    return a.y < b.y;
}

// 计算两点间欧式距离
double dist(const Point& a, const Point& b) {
    return hypot(a.x - b.x, a.y - b.y); // sqrt((x1-x2)^2 + (y1-y2)^2)
}

// 处理 strip 区域，保证严格正确
double stripClosest(vector<Point>& strip, double d) {
    double minDist = d;
    sort(strip.begin(), strip.end(), cmpY);

    for (size_t i = 0; i < strip.size(); i++) {
        // 只需要检查最多 7 个与之 y 坐标相近的点（理论保证）
        for (size_t j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) < minDist; j++) {
            minDist = min(minDist, dist(strip[i], strip[j]));
        }
    }
    return minDist;
}

// 分治核心函数
double closestUtil(vector<Point>& pts, int left, int right) {
    if (right - left <= 3) {
        double minDist = DBL_MAX;
        for (int i = left; i <= right; i++)
            for (int j = i + 1; j <= right; j++)
                minDist = min(minDist, dist(pts[i], pts[j]));
        return minDist;
    }

    int mid = (left + right) / 2;
    double dLeft = closestUtil(pts, left, mid);
    double dRight = closestUtil(pts, mid + 1, right);
    double d = min(dLeft, dRight);

    // 构造 strip 区域
    vector<Point> strip;
    for (int i = left; i <= right; i++)
        if (fabs(pts[i].x - pts[mid].x) < d)
            strip.push_back(pts[i]);

    return stripClosest(strip, d);
}

// 主函数接口：传入点数组，返回最近距离
double closestPair(vector<Point>& pts) {
    sort(pts.begin(), pts.end(), cmpX);
    return closestUtil(pts, 0, pts.size() - 1);
}

// 示例：可自行添加测试
int main() {
    ifstream fin("points.txt");
    if (!fin.is_open()) {
        cerr << "Error: Cannot open points.txt" << endl;
        return 1;
    }

    vector<Point> pts;
    Point temp;
    while (fin >> temp.x >> temp.y) {  // 读到结束
        pts.push_back(temp);
    }
    fin.close();

    if (pts.size() < 2) {
        cout << "Not enough points." << endl;
        return 0;
    }

    double ans = closestPair(pts);
    cout << fixed << setprecision(6) << ans << endl;
    return 0;
}
