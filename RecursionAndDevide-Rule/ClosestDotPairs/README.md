# ? Closest Pair of Points in a Plane（平面最近点对算法）

本项目实现了二维平面中 **最近点对问题（Closest Pair of Points）** 的求解算法，包含：

- ? **对照组（标准实现）**：严格按照分治法（Divide & Conquer）实现，经过验证 100% 可靠；
- ? **自编程序（待验证实现）**：由本人独立编写，用于学习、调试算法；
- ? ? 输入数据来自 `points.txt` 文件，自动读取未知数量的点。

---

## ? 项目目标

? 理解最近点对算法的 **分治思想**  
? 实践高效算法与 **归并排序按 y 排序的技巧**  
? 对比自编版本与标准实现的差异  
? 通过 GitHub 项目管理和调试算法

---

## ? 算法说明

最近点对问题要求在二维平面中找到距离最近的两个点。  
本仓库中的 **标准代码** 使用了经典分治策略：

### ? 算法特点

| 特性 | 标准算法 |
|------|-----------|
| 时间复杂度 | \(O(n \log n)\) |
| 方法 | 先按 x 排序 → 分治 → strip 区域过滤 |
| 关键优化 | 在 strip 中只需检测若干个点 |
| 辅助步骤 | 使用归并思想按 y 合并排序 |

? **自编版本** 用于和标准算法进行运行、调试、性能与结果对照。

---

## ? 项目结构
│── /src
│   ├── my_version.cpp        # 自己编写的版本
│   ├── reference_code.cpp    # 已通过验证的标准算法实现
│
├── points.txt                # 测试数据（可自定义）
└── README.md                 # 说明文档

---

## ? 使用方法

### ? 1. 准备输入文件 `points.txt`

每行一个点（x y，用空格分隔），例如：

```
12.3 15.4
-4.2 3.1
102.5 8.8
……
```

### ? 2. 编译运行（以 g++ 为例）

```bash
g++ -o ClosestDotPairs_reference.cpp ClosestDotPairs_reference
./ClosestDotPairs_reference

g++ -o ClosestDotPairs.cpp ClosestDotPairs
./ClosestDotPairs
```

### ? 3. 结果比较

* 两个程序都会输出最近点对的 **距离值**；
* 可用不同 `points.txt` 进行测试；
* 若结果不同，可定位到 `Merge()` 或 strip 区域逻辑。

---

## ? 测试数据

仓库可添加多个 `points_xxx.txt` 文件进行测试，例如：

```
points_random.txt
points_circle.txt
points_dense.txt
points_sparse.txt
```

---

## ? 常见问题

| 问题描述           | 可能原因               |
| -------------- | ------------------ |
| 程序无输出/卡住       | Merge 归并逻辑错误导致死循环  |
| 结果偏差           | strip 检查条件不正确      |
| 读取失败           | `points.txt` 路径不正确 |
| Windows 中文路径报错 | 建议使用英文路径           |

---

## ? 未来改进方向

* 输出不仅是距离，还显示 **最近点对坐标**
* 使用图形化显示：绘制散点图并标注最近点
* 支持三维空间最近点对扩展

---

## ? 贡献与反馈

欢迎 Issues、Pull Requests 以及提出优化建议。
如果你喜欢这个项目，欢迎 Star ? 支持！

---

### ? License

本项目遵循 MIT License，详见仓库中的 `LICENSE` 文件。

```