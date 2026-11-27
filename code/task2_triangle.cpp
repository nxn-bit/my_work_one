/*
 * 实验三  任务二：三角形类 Triangle
 * 计工本2504  肖依诺  202511160408
 */
#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

// 三角形类，三条边用 double 存
class Triangle
{
private:
    double a, b, c;

    // 把返回的数字翻译成中文名字
    string typeName(int t)
    {
        if (t == 1)
            return "直角三角形";
        if (t == 2)
            return "锐角三角形";
        if (t == 3)
            return "钝角三角形";
        if (t == 4)
            return "等腰三角形";
        if (t == 5)
            return "等边三角形";
        if (t == 6)
            return "等腰直角三角形";
        return "不是三角形";
    }

public:
    // 构造函数，三条边默认都是 1
    Triangle(double a = 1, double b = 1, double c = 1) : a(a), b(b), c(c)
    {
    }

    // 形参和成员变量同名，用 this-> 区分，this 指的就是当前这个对象
    void Init(double a, double b, double c)
    {
        this->a = a;
        this->b = b;
        this->c = c;
    }

    // 判断三条边能不能组成三角形
    bool isTriangle()
    {
        if (a <= 0 || b <= 0 || c <= 0)
            return false;
        if (a + b <= c)
            return false;
        if (a + c <= b)
            return false;
        if (b + c <= a)
            return false;
        return true;
    }

    double getSideA()
    {
        return a;
    }

    double getSideB()
    {
        return b;
    }

    double getSideC()
    {
        return c;
    }

    // 改边长，不是正数就不改
    void setSideA(double x)
    {
        if (x <= 0)
        {
            cout << "Invalid side: " << x << endl;
            return;
        }
        a = x;
    }

    void setSideB(double x)
    {
        if (x <= 0)
        {
            cout << "Invalid side: " << x << endl;
            return;
        }
        b = x;
    }

    void setSideC(double x)
    {
        if (x <= 0)
        {
            cout << "Invalid side: " << x << endl;
            return;
        }
        c = x;
    }

    // 周长
    double perimeter()
    {
        return a + b + c;
    }

    // 面积用海伦公式：先算半周长 p，再开根号
    double area()
    {
        if (!isTriangle())
        {
            cout << "Error: cannot form a triangle" << endl;
            return 0;
        }
        double p = perimeter() / 2;
        return sqrt(p * (p - a) * (p - b) * (p - c));
    }

    /* 判断类型：0不构成 1直角 2锐角 3钝角 4等腰 5等边 6等腰直角
       选做部分扩展了 4、5、6，类型重叠时按这个优先级来：
       等边 > 等腰直角 > 等腰 > 直角 > 锐角 > 钝角 */
    int typeTriangle()
    {
        if (!isTriangle())
            return 0;

        // 先把最长边挪到 z 上，这样后面只比一次
        double x = a;
        double y = b;
        double z = c;
        if (x > z)
        {
            double t = x;
            x = z;
            z = t;
        }
        if (y > z)
        {
            double t = y;
            y = z;
            z = t;
        }

        // 浮点数不能直接用 == 比，误差小于 1e-6 就算相等
        bool isosceles = false;
        if (fabs(x - y) < 1e-6)
            isosceles = true;
        if (fabs(y - z) < 1e-6)
            isosceles = true;
        if (fabs(x - z) < 1e-6)
            isosceles = true;

        bool equilateral = fabs(x - y) < 1e-6 && fabs(y - z) < 1e-6;
        bool rightAngle = fabs(x * x + y * y - z * z) < 1e-6;

        // 从优先级最高的开始判断
        if (equilateral)
            return 5;
        if (isosceles && rightAngle)
            return 6;
        if (isosceles)
            return 4;
        if (rightAngle)
            return 1;
        if (x * x + y * y > z * z)
            return 2;
        return 3;
    }

    // 输出三边、周长、面积和类型，都保留两位小数
    void display()
    {
        cout << fixed << setprecision(2);
        cout << "Sides: " << a << " " << b << " " << c << endl;

        if (!isTriangle())
        {
            cout << "Error: cannot form a triangle" << endl;
            return;
        }

        cout << "Perimeter: " << perimeter() << endl;
        cout << "Area: " << area() << endl;
        cout << "Type: " << typeName(typeTriangle()) << endl;
    }
};

int main()
{
    double a, b, c;
    cin >> a >> b >> c;

    Triangle t(a, b, c);
    t.display();

    return 0;
}
