/*
 * 实验任务三：C++ 特色函数考察 —— 简易多功能计算器
 * 功能：
 *   1. 内联函数 inline double square(double x)            —— 计算平方
 *   2. 带默认参数的函数 double power(double base, int exponent = 2)
 *                                                        —— 计算乘幂，缺省指数时默认平方
 *   3. 两个重载函数 calc(double,...) 与 calc(int,...)      —— 加、减、乘、除
 *      除数为 0 时输出 "Error: divide by zero"
 * 输入：两个操作数和一个运算符，例如：3 5 +
 */
#include <iostream>
#include <iomanip>
using namespace std;

// 1. 内联函数：计算平方
inline double square(double x) {
    return x * x;
}

// 2. 带默认参数值的函数：计算乘幂，指数缺省为 2（即默认求平方）
double power(double base, int exponent = 2) {
    if (exponent == 0)
        return 1.0;

    int e = (exponent < 0) ? -exponent : exponent;  // 统一按正指数计算
    double result = 1.0;
    for (int i = 0; i < e; ++i)
        result *= base;

    return (exponent < 0) ? 1.0 / result : result;  // 负指数取倒数
}

// 3a. 重载函数（double 版本）：四则运算
double calc(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return (b != 0.0) ? a / b : 0.0;  // 除 0 由主函数先行提示
        default:  return 0.0;
    }
}

// 3b. 重载函数（int 版本）：四则运算（两个操作数都是整数时调用）
int calc(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return (b != 0) ? a / b : 0;      // 整数除法
        default:  return 0;
    }
}

int main() {
    double a, b;
    char op;

    // 输入两个操作数和一个运算符
    if (!(cin >> a >> b >> op)) {
        cerr << "Invalid input." << endl;
        return 1;
    }

    cout << fixed << setprecision(2);

    // 分别演示内联函数与带默认参数的函数
    cout << "square(" << a << ") = " << square(a) << endl;
    cout << "power(" << a << ") = " << power(a) << endl;        // 使用默认指数 2
    cout << "power(" << a << ",3) = " << power(a, 3) << endl;    // 显式指定指数

    bool isInt = (a == static_cast<int>(a)) && (b == static_cast<int>(b));

    if (op != '+' && op != '-' && op != '*' && op != '/') {
        cout << "Error: unknown operator" << endl;
    } else if (op == '/' && b == 0) {
        cout << "Error: divide by zero" << endl;
    } else if (isInt) {
        // 两个操作数都是整数：调用 int 版本重载（整数除法）
        int result = calc(static_cast<int>(a), static_cast<int>(b), op);
        cout << a << " " << op << " " << b << " = "
             << static_cast<double>(result) << endl;
    } else {
        // 至少一个操作数是浮点数：调用 double 版本重载
        cout << a << " " << op << " " << b << " = " << calc(a, b, op) << endl;
    }

    return 0;
}
