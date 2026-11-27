/*
 * 实验三  任务三：动态整型数组类 MyArray（实现部分）
 * 计工本2504  肖依诺  202511160408
 */
#include <iostream>
#include "MyArray.h"
using namespace std;

// ---------- 构造函数和析构函数 ----------

MyArray::MyArray()
{
    p = nullptr;
    N = 0;
}

// 申请 n 个 int 的空间，全部赋成 value
MyArray::MyArray(int n, int value)
{
    if (n < 0)
        n = 0;
    N = n;
    if (N == 0)
    {
        p = nullptr;
        return;
    }
    p = new int[N];
    for (int i = 0; i < N; i++)
        p[i] = value;
}

// 拷贝构造函数：重新申请一块内存再逐个复制，这就是深拷贝。
// 如果写成 p = other.p 就是浅拷贝，两个对象共用一块内存，析构时会重复释放
MyArray::MyArray(const MyArray &other)
{
    N = other.N;
    if (N == 0)
    {
        p = nullptr;
        return;
    }
    p = new int[N];
    for (int i = 0; i < N; i++)
        p[i] = other.p[i];
}

// new[] 申请的要配 delete[] 释放，释放完把指针置空
MyArray::~MyArray()
{
    delete[] p;
    p = nullptr;
    N = 0;
}

// ---------- 基本操作 ----------

int MyArray::size()
{
    return N;
}

// 数组下标从 0 开始，越界的话只提示不操作
int MyArray::get(int index)
{
    if (index < 0 || index >= N)
    {
        cout << "Error: index " << index << " out of range" << endl;
        return 0;
    }
    return p[index];
}

void MyArray::set(int index, int value)
{
    if (index < 0 || index >= N)
    {
        cout << "Error: index " << index << " out of range" << endl;
        return;
    }
    p[index] = value;
}

void MyArray::display()
{
    cout << "{";
    for (int i = 0; i < N; i++)
    {
        if (i > 0)
            cout << ", ";
        cout << p[i];
    }
    cout << "}";
}

// ---------- 合并和四则运算，都返回新的对象 ----------

// 合并：本对象的元素放前面，other 的放后面
MyArray MyArray::merge(const MyArray &other)
{
    MyArray result(N + other.N);
    for (int i = 0; i < N; i++)
        result.p[i] = p[i];
    for (int i = 0; i < other.N; i++)
        result.p[N + i] = other.p[i];
    return result;
}

MyArray MyArray::add(const MyArray &other)
{
    // 长度不一样就提醒一下，按短的算
    if (N != other.N)
    {
        cout << "Warning: different sizes (" << N << " vs " << other.N;
        cout << "), use the shorter one" << endl;
    }

    int n = (N < other.N) ? N : other.N;
    MyArray result(n);
    for (int i = 0; i < n; i++)
        result.p[i] = p[i] + other.p[i];
    return result;
}

MyArray MyArray::subtract(const MyArray &other)
{
    if (N != other.N)
    {
        cout << "Warning: different sizes (" << N << " vs " << other.N;
        cout << "), use the shorter one" << endl;
    }

    int n = (N < other.N) ? N : other.N;
    MyArray result(n);
    for (int i = 0; i < n; i++)
        result.p[i] = p[i] - other.p[i];
    return result;
}

MyArray MyArray::multiply(const MyArray &other)
{
    if (N != other.N)
    {
        cout << "Warning: different sizes (" << N << " vs " << other.N;
        cout << "), use the shorter one" << endl;
    }

    int n = (N < other.N) ? N : other.N;
    MyArray result(n);
    for (int i = 0; i < n; i++)
        result.p[i] = p[i] * other.p[i];
    return result;
}

// 除法要小心除数是 0，这一位的结果记成 0 就好
MyArray MyArray::divide(const MyArray &other)
{
    if (N != other.N)
    {
        cout << "Warning: different sizes (" << N << " vs " << other.N;
        cout << "), use the shorter one" << endl;
    }

    int n = (N < other.N) ? N : other.N;
    MyArray result(n);
    for (int i = 0; i < n; i++)
    {
        if (other.p[i] == 0)
        {
            cout << "Warning: divide by zero at index " << i << ", result is 0" << endl;
            result.p[i] = 0;
        }
        else
            result.p[i] = p[i] / other.p[i];
    }
    return result;
}
