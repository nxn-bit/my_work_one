/*
 * card_operations.h —— 校园一卡通消费管理系统 · 函数声明头文件
 *
 * 模块七：多文件编程
 *   - 头文件只放常量、结构体和函数声明，不放函数定义；
 *   - 使用 #ifndef / #define / #endif 防止头文件被重复包含。
 */
#ifndef CARD_OPERATIONS_H
#define CARD_OPERATIONS_H

#include <string>

/* ==================== 模块一：系统常量 ==================== */
const double FEE_RATE = 0.02;         // 充值手续费率（2%）
const double WARNING_BALANCE = 10.0;  // 低余额警戒值（元）

/* ==================== 模块一：账户数据结构 ==================== */
struct Card {
    int         id;            // 学号
    std::string name;          // 姓名
    double      balance;       // 当前余额（元）
    int         transactions;  // 交易次数
};

/* ==================== 模块二：命名空间与格式化输出 ==================== */
namespace card {
    void printLine(char c = '-', int len = 60);  // 打印分隔线
    void title(const std::string& s);            // 打印标题
}

/* ==================== 模块三：动态内存管理与账户录入 ==================== */
Card* createCards(int n);             // 用 new[] 创建账户数组
void  destroyCards(Card* p);          // 用 delete[] 释放账户数组
void  inputCards(Card* arr, int n);   // 循环录入账户信息

/* ==================== 模块四：账户操作 ==================== */
void deposit(Card& c, double amount, double fee = FEE_RATE);
bool spend(Card& c, double cost);
bool spend(Card& c, double cost, const std::string& item);
void showBalance(const Card& c);      // 常引用：只读查询余额
void viewStudentID(const Card* p);    // 指向常量的指针：只读查询 ID

/* ==================== 模块五：金额单位换算 ==================== */
int toCent(double amount);            // 元 → 分（static_cast<int>）

/* ==================== 模块六：报表输出 ==================== */
void printReport(const Card* arr, int n);

#endif // CARD_OPERATIONS_H
