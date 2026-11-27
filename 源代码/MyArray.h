// MyArray.h
// 动态整型数组类的头文件，只放声明，具体实现写在 MyArray.cpp 里
#ifndef MYARRAY_H
#define MYARRAY_H

class MyArray
{
private:
    int *p;      // 指向动态申请的数组
    int N;       // 元素个数

public:
    MyArray();                              // 默认构造，空数组
    MyArray(int n, int value = 0);          // n 个元素，初始值都是 value
    MyArray(const MyArray &other);          // 拷贝构造，要做深拷贝
    ~MyArray();                             // 析构，释放内存

    int size();                             // 元素个数
    int get(int index);                     // 读一个元素
    void set(int index, int value);         // 改一个元素
    void display();                         // 输出成 {a, b, c}

    MyArray merge(const MyArray &other);    // 合并，返回新对象
    MyArray add(const MyArray &other);      // 加
    MyArray subtract(const MyArray &other); // 减
    MyArray multiply(const MyArray &other); // 乘
    MyArray divide(const MyArray &other);   // 除
};

#endif
