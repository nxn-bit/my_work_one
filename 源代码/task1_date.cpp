/*
 * 实验三  任务一：日期类 Date
 * 计工本2504  肖依诺  202511160408
 */
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

// 日期类
class Date
{
private:
    int year;
    int month;
    int day;

    // 判断闰年：能被400整除，或者能被4整除但不能被100整除
    bool isLeap(int y)
    {
        if (y % 400 == 0)
            return true;
        if (y % 100 == 0)
            return false;
        if (y % 4 == 0)
            return true;
        return false;
    }

    // 某一年某个月有几天
    int monthDays(int y, int m)
    {
        if (m == 2)
        {
            if (isLeap(y))
                return 29;
            return 28;
        }
        // 4、6、9、11 月是 30 天
        if (m == 4 || m == 6 || m == 9 || m == 11)
            return 30;
        return 31;
    }

    // 检查日期合不合法，年月日都要看
    bool isValid(int y, int m, int d)
    {
        if (y < 1)
            return false;
        if (m < 1 || m > 12)
            return false;
        if (d < 1 || d > monthDays(y, m))
            return false;
        return true;
    }

public:
    // 构造函数：用初始化列表给三个数据成员赋值，顺便检查一下日期
    Date(int y = 1900, int m = 1, int d = 1) : year(y), month(m), day(d)
    {
        if (!isValid(y, m, d))
        {
            cout << "Invalid date, reset to 1900-01-01" << endl;
            year = 1900;
            month = 1;
            day = 1;
        }
    }

    // 手工初始化。跟构造函数比一下就知道区别了：这个得自己调用，忘了就还是脏数据
    void Init(int y, int m, int d)
    {
        if (!isValid(y, m, d))
        {
            cout << "Invalid date, reset to 1900-01-01" << endl;
            year = 1900;
            month = 1;
            day = 1;
            return;
        }
        year = y;
        month = m;
        day = d;
    }

    // 下面三个是读数据用的
    int getYear()
    {
        return year;
    }

    int getMonth()
    {
        return month;
    }

    int getDay()
    {
        return day;
    }

    // 下面三个是写数据用的，不合法的值不写进去
    void setYear(int y)
    {
        if (y < 1)
        {
            cout << "Invalid year: " << y << endl;
            return;
        }
        year = y;
    }

    void setMonth(int m)
    {
        if (m < 1 || m > 12)
        {
            cout << "Invalid month: " << m << endl;
            return;
        }
        month = m;
    }

    // 这里要看当前年月的天数，所以改日期之前最好先把年、月改对
    void setDay(int d)
    {
        if (d < 1 || d > monthDays(year, month))
        {
            cout << "Invalid day: " << d << endl;
            return;
        }
        day = d;
    }

    // 选做1：判断当前年份是不是闰年
    bool isLeapYear()
    {
        return isLeap(year);
    }

    // 选做2：日期往后加一天，月末、年末、闰年2月都要考虑
    void nextDay()
    {
        if (day < monthDays(year, month))
            day = day + 1;
        else if (month < 12)
        {
            day = 1;
            month = month + 1;
        }
        else
        {
            day = 1;
            month = 1;
            year = year + 1;
        }
    }

    // 输出成 YYYY-MM-DD，月和日不够两位就在前面补0
    void display()
    {
        cout << "Date: " << year << "-";
        cout << setfill('0') << setw(2) << month << "-";
        cout << setw(2) << day << setfill(' ') << endl;
    }

    // 用基姆拉尔森公式算星期几，1月和2月要当成上一年的13月、14月
    int calWeekday()
    {
        int y = year;
        int m = month;
        int d = day;
        if (m == 1 || m == 2)
        {
            m = m + 12;
            y = y - 1;
        }
        int w = (d + 2 * m + 3 * (m + 1) / 5 + y + y / 4 - y / 100 + y / 400 + 1) % 7;
        return w;
    }
};

int main()
{
    int y, m, d;
    cin >> y >> m >> d;

    Date date(y, m, d);
    date.display();

    // 0~6 分别对应星期日到星期六，用数组查一下
    string week[7] = {"星期日", "星期一", "星期二", "星期三", "星期四", "星期五", "星期六"};
    cout << "Weekday: " << week[date.calWeekday()] << endl;

    // 选做部分：先看是不是闰年，再把日期往后推一天
    cout << "Leap year: ";
    if (date.isLeapYear())
        cout << "yes" << endl;
    else
        cout << "no" << endl;

    date.nextDay();
    cout << "Next day: " << date.getYear() << "-";
    cout << setfill('0') << setw(2) << date.getMonth() << "-";
    cout << setw(2) << date.getDay() << setfill(' ') << endl;

    return 0;
}
