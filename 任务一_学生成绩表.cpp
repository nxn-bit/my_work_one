/*
 * 实验任务一：C++ 的输入输出控制考察
 * 题目：输入若干名学生的信息（姓名、三门课程成绩），计算每名学生的平均成绩，
 *       并输出每位学生的成绩信息表。
 * 要求：
 *   1. 第一行输入学生人数 n；
 *   2. 每位学生输入格式：姓名 语文 数学 英语；
 *   3. 输出：姓名与三门成绩及平均分；平均成绩保留两位小数；
 *      平均分 >= 90 的学生后面标注 "Excellent"；输出格式整齐对齐。
 */
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

int main() {
    int n;

    // 1. 输入学生人数，并检查输入是否合法
    if (!(cin >> n) || n <= 0) {
        cerr << "Invalid student number." << endl;
        return 1;
    }

    // 2. 动态申请内存存储学生信息（姓名、三门成绩、平均分）
    string* names  = new string[n];      // 姓名
    double* scores = new double[n * 3];  // 第 i 名学生：scores[i*3] ~ scores[i*3+2]
    double* avg    = new double[n];      // 平均分

    // 3. 输入每位学生的信息并计算平均分
    for (int i = 0; i < n; ++i) {
        cin >> names[i]
            >> scores[i * 3]
            >> scores[i * 3 + 1]
            >> scores[i * 3 + 2];

        double total = scores[i * 3] + scores[i * 3 + 1] + scores[i * 3 + 2];
        avg[i] = total / 3.0;
    }

    // 4. 输出表头与成绩信息表（保留两位小数，整齐对齐）
    cout << fixed << setprecision(2);  // 所有浮点数保留两位小数

    cout << left << setw(12) << "Name"
                 << setw(10) << "Chinese"
                 << setw(10) << "Math"
                 << setw(10) << "English"
                 << setw(10) << "Average"
                 << "Note" << endl;

    for (int i = 0; i < n; ++i) {
        cout << left << setw(12) << names[i]
                     << setw(10) << scores[i * 3]      // 语文
                     << setw(10) << scores[i * 3 + 1]  // 数学
                     << setw(10) << scores[i * 3 + 2]  // 英语
                     << setw(10) << avg[i];            // 平均分
        if (avg[i] >= 90.0)
            cout << "Excellent";                       // 优秀标记
        cout << endl;
    }

    // 5. 释放动态内存
    delete[] names;
    delete[] scores;
    delete[] avg;

    return 0;
}
