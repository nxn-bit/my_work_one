/*
 * card_operations.cpp —— 校园一卡通消费管理系统 · 函数实现文件
 *
 * 实现模块二～模块六：
 *   模块二  命名空间与格式化输出
 *   模块三  动态内存管理与账户录入
 *   模块四  充值、消费、只读查询
 *   模块五  金额单位换算
 *   模块六  报表输出
 */
#include "card_operations.h"

#include <iomanip>
#include <iostream>
#include <limits>
#include <stdexcept>

using namespace std;

/* ============================================================
 * 模块二：命名空间与格式化输出模块
 * ============================================================ */
namespace card {

// 打印 len 个字符 c 组成的分隔线
void printLine(char c, int len) {
    if (len < 0)
        len = 0;
    for (int i = 0; i < len; ++i)
        cout << c;
    cout << '\n';
}

// 打印标题：上下各一条与标题等宽的分隔线
void title(const string& s) {
    int len = static_cast<int>(s.size()) + 8;
    if (len < 20)
        len = 20;

    printLine('=', len);
    cout << "  " << s << '\n';
    printLine('=', len);
}

} // namespace card

/* ============================================================
 * 模块三：动态内存管理与账户录入模块
 * ============================================================ */

// 用 new[] 动态创建 n 个账户；分配失败时抛出 bad_alloc，由 main 捕获
Card* createCards(int n) {
    if (n <= 0)
        throw invalid_argument("账户数量必须大于 0");
    return new Card[n];
}

// 用 delete[] 释放账户数组（p 为空时也安全）
void destroyCards(Card* p) {
    delete[] p;
}

// 循环读入学号、姓名、初始余额，交易次数初始化为 0
void inputCards(Card* arr, int n) {
    for (int i = 0; i < n; ++i) {
        while (true) {
            cout << "请输入第 " << (i + 1)
                 << " 个账户（学号 姓名 初始余额）：";

            try {
                int    id = 0;
                string name;
                double balance = 0.0;

                // 模块九：输入格式异常检测
                if (!(cin >> id >> name >> balance)) {
                    if (cin.eof())
                        throw runtime_error("输入结束，账户信息不完整");
                    throw runtime_error("输入格式错误，应为“学号 姓名 初始余额”");
                }

                // 模块九：负数余额属于非法数据
                if (balance < 0)
                    throw runtime_error("初始余额不能为负数");

                arr[i].id = id;
                arr[i].name = name;
                arr[i].balance = balance;
                arr[i].transactions = 0;
                break;
            }
            catch (const exception& e) {
                // 输入流已结束，无法继续重试，交给主程序处理
                if (cin.eof())
                    throw;

                cin.clear();                                        // 清除错误标志
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 丢弃当前行
                cout << "输入错误（" << e.what() << "），请重新输入！" << '\n';
            }
        }
    }
}

/* ============================================================
 * 模块四：账户操作模块（常引用与指向常量的指针）
 * ============================================================ */

// 充值：扣除手续费后增加余额，并累加交易次数
void deposit(Card& c, double amount, double fee) {
    if (amount <= 0)
        throw invalid_argument("充值金额必须大于 0");
    if (fee < 0.0 || fee >= 1.0)
        throw invalid_argument("手续费率必须在 [0, 1) 范围内");

    c.balance += amount * (1.0 - fee);
    ++c.transactions;
}

// 消费（基础版）：余额足够则扣款并返回 true，余额不足返回 false
// 负消费金额属于非法数据，按模块九要求抛出异常
bool spend(Card& c, double cost) {
    if (cost < 0)
        throw invalid_argument("消费金额不能为负数");   // 模块九：消费金额异常

    if (c.balance < cost)
        return false;                                  // 模块四：余额不足返回 false

    c.balance -= cost;
    ++c.transactions;
    return true;
}

// 消费（重载版）：先输出消费项目，再调用基础版完成扣款
bool spend(Card& c, double cost, const string& item) {
    cout << "消费项目：" << item << '\n';
    return spend(c, cost);
}

// 常引用查询：只读访问，函数内部不能修改账户数据
void showBalance(const Card& c) {
    cout << fixed << setprecision(2)
         << "账户余额：" << c.balance << " 元" << '\n';
}

// 指向常量的指针查询：只读访问，不能通过 p 修改账户数据
void viewStudentID(const Card* p) {
    if (p == nullptr)
        throw invalid_argument("账户指针为空");
    cout << "账户ID：" << p->id << '\n';
}

/* ============================================================
 * 模块五：强制类型转换模块（元 → 分）
 * ============================================================ */
int toCent(double amount) {
    if (amount < 0)
        throw invalid_argument("金额不能为负数");
    return static_cast<int>(amount * 100);
}

/* ============================================================
 * 模块六：报表输出模块
 * ============================================================ */
void printReport(const Card* arr, int n) {
    if (arr == nullptr || n <= 0) {
        cout << "没有可显示的账户。" << '\n';
        return;
    }

    cout << fixed << setprecision(2);
    card::title("账户报表");

    // 表头
    cout << left << setw(12) << "ID"
                 << setw(18) << "Name"
                 << setw(12) << "Balance"
                 << setw(14) << "Transactions" << '\n';
    card::printLine();

    // 数据行
    for (int i = 0; i < n; ++i) {
        cout << left << setw(12) << arr[i].id
                     << setw(18) << arr[i].name
                     << setw(12) << arr[i].balance
                     << setw(14) << arr[i].transactions << '\n';
    }

    card::printLine();

    // 低余额提醒（使用 WARNING_BALANCE 常量，放在表格之后以免打断对齐）
    bool hasWarning = false;
    for (int i = 0; i < n; ++i) {
        if (arr[i].balance < WARNING_BALANCE) {
            if (!hasWarning) {
                cout << "\n[低余额提醒]" << '\n';
                hasWarning = true;
            }
            cout << "  账户 " << arr[i].id << "（" << arr[i].name
                 << "）余额 " << arr[i].balance
                 << " 元，低于警戒值 " << WARNING_BALANCE << " 元" << '\n';
        }
    }
}
