/*
 * 实验三  任务三：MyArray 类的测试程序
 * 计工本2504  肖依诺  202511160408
 */
#include <iostream>
#include "MyArray.h"
using namespace std;

int main()
{
    // 测试一：两个一样长的数组，做合并和四则运算
    MyArray A(3), B(3);
    A.set(0, 6);
    A.set(1, 8);
    A.set(2, 9);
    B.set(0, 3);
    B.set(1, 2);
    B.set(2, 4);

    cout << "A = ";
    A.display();
    cout << endl;
    cout << "B = ";
    B.display();
    cout << endl;

    MyArray M = A.merge(B);
    cout << "A merge B = ";
    M.display();
    cout << endl;

    MyArray S = A.add(B);
    cout << "A + B = ";
    S.display();
    cout << endl;

    MyArray Sub = A.subtract(B);
    cout << "A - B = ";
    Sub.display();
    cout << endl;

    MyArray Mul = A.multiply(B);
    cout << "A * B = ";
    Mul.display();
    cout << endl;

    MyArray Div = A.divide(B);
    cout << "A / B = ";
    Div.display();
    cout << endl;

    // 测试二：长度不一样的时候
    MyArray C(3), D(2);
    C.set(0, 1);
    C.set(1, 2);
    C.set(2, 3);
    D.set(0, 4);
    D.set(1, 5);

    cout << "C = ";
    C.display();
    cout << endl;
    cout << "D = ";
    D.display();
    cout << endl;

    MyArray S2 = C.add(D);
    cout << "C + D = ";
    S2.display();
    cout << endl;

    // 测试三：深拷贝。把 E 改了，A 里原来的值不应该跟着变
    MyArray E = A;
    E.set(0, 100);
    cout << "E = ";
    E.display();
    cout << endl;
    cout << "A = ";
    A.display();
    cout << endl;

    // 测试四：size 和 get，以及下标越界
    cout << "size of A = " << A.size() << ", A.get(1) = " << A.get(1) << endl;

    A.set(5, 1);
    cout << "A.get(9) = " << A.get(9) << endl;

    // 测试五：除数是 0 的情况
    MyArray F(3), G(3);
    F.set(0, 6);
    F.set(1, 8);
    F.set(2, 9);
    G.set(0, 3);
    G.set(1, 0);
    G.set(2, 4);

    MyArray Div2 = F.divide(G);
    cout << "F / G = ";
    Div2.display();
    cout << endl;

    // 测试六：默认构造函数得到的空数组
    MyArray Empty;
    cout << "Empty = ";
    Empty.display();
    cout << endl;
    cout << "size of Empty = " << Empty.size() << endl;

    return 0;
}
