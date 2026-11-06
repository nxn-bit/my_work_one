/*
 * 实验任务二：指向常量的指针特性考察
 * 题目：编写函数 int countVowels(const char* p)，统计字符串中元音字母
 *       （a, e, i, o, u）的个数。
 * 要求：
 *   1. 使用指向常量的指针 const char* 遍历字符串；
 *   2. 在主函数中输入一行字符串，调用函数并输出结果。
 */
#include <iostream>
#include <cctype>   // 提供 tolower()
using namespace std;

// 使用指向常量的指针 const char* 遍历字符串，统计元音字母个数
int countVowels(const char* p) {
    int count = 0;

    // p 指向的字符内容不可修改（const 保护），但指针本身可以移动
    while (*p != '\0') {
        // 先转换为 unsigned char，避免对负值字符调用 tolower() 产生未定义行为
        unsigned char ch = static_cast<unsigned char>(*p);
        char lower = static_cast<char>(tolower(ch));

        if (lower == 'a' || lower == 'e' || lower == 'i' ||
            lower == 'o' || lower == 'u')
            ++count;

        ++p;    // 指针移动到下一个字符
    }
    return count;
}

int main() {
    char str[256];

    // 输入一行字符串（可含空格）；若输入失败则按空串处理
    if (!cin.getline(str, sizeof(str)))
        str[0] = '\0';

    cout << "Number of vowels: " << countVowels(str) << endl;

    return 0;
}
