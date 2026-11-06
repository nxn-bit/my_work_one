/*
 * CampusCardSystem.cpp —— 校园一卡通消费管理系统 · 主程序文件
 *
 * 模块八：主程序集成
 *   1. 输出系统标题，输入学生数量；
 *   2. 动态创建账户数组并录入账户信息；
 *   3. 对第一个账户充值 100 元、消费 8.5 元（项目："食堂午餐"）；
 *   4. 显示该账户余额与账户 ID；
 *   5. 将余额换算为分并输出；
 *   6. 输出全部账户报表，最后释放动态内存。
 *
 * 模块九：统一捕获输入异常、消费异常和内存分配异常。
 *
 * 编译方法（三个文件放在同一目录）：
 *   Visual Studio：新建“控制台应用”项目，把三个文件加入项目后按 F5；
 *   g++：g++ -std=c++11 CampusCardSystem.cpp card_operations.cpp -o card_system
 */
#include "card_operations.h"

#include <iostream>
#include <new>
#include <stdexcept>

using namespace std;

int main() {
    try {
        // 1. 系统标题 + 输入学生数量
        card::title("校园一卡通消费管理系统");

        int n = 0;
        cout << "请输入学生数量：";
        if (!(cin >> n) || n <= 0)
            throw invalid_argument("学生数量必须为正整数");

        // 2. 动态创建账户数组并录入信息
        Card* cards = createCards(n);

        // 内层 try：无论录入或后续操作是否抛出异常，都保证释放动态内存
        try {
            inputCards(cards, n);

            // 3. 第一个账户充值 100 元、消费 8.5 元（项目："食堂午餐"）
            cout << "\n[1] 账户充值\n";
            deposit(cards[0], 100.0);   // 使用默认手续费率 FEE_RATE
            cout << "充值 100.00 元，手续费率 "
                 << static_cast<int>(FEE_RATE * 100) << "%。" << '\n';

            cout << "\n[2] 账户消费\n";
            // 模块四：spend 返回 false 表示余额不足；
            // 模块九：主程序把失败转换为异常并提示，防止非法扣款
            if (!spend(cards[0], 8.5, "食堂午餐"))
                throw runtime_error("余额不足，消费失败");

            // 4. 显示余额与账户 ID（常引用 + 指向常量的指针）
            cout << "\n[3] 账户查询\n";
            showBalance(cards[0]);
            viewStudentID(&cards[0]);

            // 5. 余额换算为分（static_cast<int>）
            int cents = toCent(cards[0].balance);
            cout << "余额换算：" << cents << " 分" << '\n';

            // 6. 输出全部账户报表
            cout << '\n';
            printReport(cards, n);
        }
        catch (...) {
            destroyCards(cards);   // 异常路径也要释放内存
            throw;                 // 交给外层统一处理
        }

        destroyCards(cards);
    }
    catch (const bad_alloc& e) {
        // 模块九：内存申请失败，安全退出
        cerr << "内存分配失败：" << e.what() << '\n';
        return 1;
    }
    catch (const exception& e) {
        // 模块九：捕获其余所有标准异常
        cerr << "程序异常终止：" << e.what() << '\n';
        return 1;
    }

    return 0;
}
