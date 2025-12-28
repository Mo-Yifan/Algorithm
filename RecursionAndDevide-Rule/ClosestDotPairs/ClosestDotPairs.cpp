#include<iostream>
#include<vector>
#include<cmath>
#include<limits>
#include<algorithm>
#include<fstream>
#include<sstream>

using namespace std;
struct Point {
    double x, y;
};

// 比较函数：按 x 坐标排序，采用内联函数，速度更快
inline bool compareX(const Point &a, const Point &b) {
    return a.x < b.x;
}

// 比较函数：按 y 坐标排序，采用内联函数，速度更快
inline bool compareY(const Point &a, const Point &b) {
    return a.y < b.y;
}

// 计算两点间欧式距离，采用内联函数，速度更快
inline double distCount(const Point &a, const Point &b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

// 合并两个按 y 坐标排序的子数组
void Merge(vector<Point> &points, int left, int mid, int right){
    vector<Point> leftPoints(points.begin() + left, points.begin() + mid);
    int i = left;
    int j = 0;
    int k = mid;
    while(i < right){
        if(j < leftPoints.size() && (k == right || leftPoints[j].y <= points[k].y)){
            points[i++] = leftPoints[j++];
        } 
        if(k < right && (j == leftPoints.size() || points[k].y < leftPoints[j].y)){
            points[i++] = points[k++];
        }
    }
}

// 分治法寻找最近点对距离
double findClosest(vector<Point> &points, int left, int right){
    
    //如果只有两个点，就直接计算距离并返回
    if(right - left == 2)
    {
        if(points[left].y > points[right - 1].y)
            swap(points[left], points[right - 1]);
        return distCount(points[left], points[right - 1]);
    }
    
    //如果只有三个点，它们默认只能连接成一个三角形，计算三条边的距离并返回最小值
    if(right - left == 3)
    {
        sort(points.begin() + left, points.begin() + right, compareY);
        double d1 = distCount(points[left], points[left + 1]);
        double d2 = distCount(points[left + 1], points[right - 1]);
        double d3 = distCount(points[left], points[right - 1]);
        return min(d1, min(d2, d3));
    }
    
    //其他情况，继续分治，直至只有两个或三个点
    int mid = (left + right) / 2;
    double midx = points[mid].x;
    double dleft = findClosest(points, left, mid);      // 递归处理左半部分
    double dright = findClosest(points, mid, right);        // 递归处理右半部分
    double d = min(dleft, dright);
    Merge(points, left, mid, right);    // 合并两个子数组，保证按 y 坐标排序
    vector<Point> strip;       // 存储横跨分割线且距离小于 d 的点
    
    //找出所有横跨分割线且距离小于 d 的点
    for(int i = left; i < right; i++){
        if(fabs(points[i].x - midx) < d){
            strip.push_back(points[i]);
        }
    }
    
    //在 strip 区域内寻找更近的点对
    for(int i = 0; i < strip.size(); i++){
        for(int j = i + 1; j < strip.size(); ++j){
            if((strip[j].y - strip[i].y) >= d) break;
            double dist = distCount(strip[i], strip[j]);
            if(dist < d){
                d = dist;
            }
        }
    }
    return d;
}

int main()
{
    vector<Point> points;
    ifstream file("points.txt", ifstream::in);
    string line;
    while (getline(file, line)) {
        Point p;
        stringstream ss(line);
        ss >> p.x >> p.y;
        points.push_back(p);
    }
    sort(points.begin(), points.end(), compareX);
    cout << findClosest(points, 0, points.size()) << endl;
    return 0;
}