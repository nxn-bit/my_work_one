/*
 * 实验任务四：引用特性考察
 * 题目：编写函数 void swap(int& x, int& y)，使用 C++ 引用交换两个整数的值；
 *       然后重载该函数，实现对两个整数的交换。
 * 要求：
 *   1. 不得使用全局变量；
 *   2. 在 main() 中输入两个整数，调用 swap 函数并输出交换前后的结果。
 */
#include <iostream>
using namespace std;

// 版本一：使用 C++ 引用交换两个整数的值（引用是实参的别名）
void swap(int& x, int& y) {
    int temp = x;
    x = y;
    y = temp;
}

// 版本二：重载——使用指针（地址）交换两个整数的值
void swap(int* x, int* y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

int main() {
    int x, y;

    // 输入两个整数
    if (!(cin >> x >> y)) {
        cerr << "Invalid input." << endl;
        return 1;
    }

    cout << "Before swap: x=" << x << ", y=" << y << endl;

    // 调用引用版本的 swap，实参直接被修改
    ::swap(x, y);
    cout << "After  swap: x=" << x << ", y=" << y << endl;

    // 调用指针重载版本的 swap，再交换回来
    ::swap(&x, &y);
    cout << "After pointer swap (back to original): x=" << x << ", y=" << y << endl;

    return 0;
}
