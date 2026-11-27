/*
 * 实验三  任务四：空间点类 Point（友元函数）
 * 计工本2504  肖依诺  202511160408
 */
#include <cmath>
#include <iomanip>
#include <iostream>
using namespace std;

// 三维空间里的一个点
class Point
{
private:
    double x, y, z;

public:
    // 构造函数，三个坐标默认都是 0
    Point(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z)
    {
    }

    // 形参和成员同名，用 this-> 区分
    void Init(double x, double y, double z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    double getX()
    {
        return x;
    }

    double getY()
    {
        return y;
    }

    double getZ()
    {
        return z;
    }

    void setX(double x)
    {
        this->x = x;
    }

    void setY(double y)
    {
        this->y = y;
    }

    void setZ(double z)
    {
        this->z = z;
    }

    void display()
    {
        cout << "(" << x << ", " << y << ", " << z << ")";
    }

    // 成员函数算欧氏距离，另一个点只能用参数传进来
    double distanceTo(const Point &other);

    // 下面几个是友元函数。它们不是类的成员，但能直接用私有成员，
    // 适合两个点地位平等的运算
    friend double euclideanDistance(const Point &a, const Point &b);
    friend double manhattanDistance(const Point &a, const Point &b);
    friend double chebyshevDistance(const Point &a, const Point &b);
    friend Point midpoint(const Point &a, const Point &b);

    // 选做：重载 euclideanDistance，只传一个点就是算它到原点的距离
    friend double euclideanDistance(const Point &p);
};

double Point::distanceTo(const Point &other)
{
    double dx = x - other.x;
    double dy = y - other.y;
    double dz = z - other.z;
    return sqrt(dx * dx + dy * dy + dz * dz);
}

// 欧氏距离，就是勾股定理推广到三维
double euclideanDistance(const Point &a, const Point &b)
{
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    double dz = a.z - b.z;
    return sqrt(dx * dx + dy * dy + dz * dz);
}

// 选做：一个参数的版本，算到原点 (0,0,0) 的距离
double euclideanDistance(const Point &p)
{
    return sqrt(p.x * p.x + p.y * p.y + p.z * p.z);
}

// 曼哈顿距离：三个方向的距离直接加起来
double manhattanDistance(const Point &a, const Point &b)
{
    double dx = fabs(a.x - b.x);
    double dy = fabs(a.y - b.y);
    double dz = fabs(a.z - b.z);
    return dx + dy + dz;
}

// 切比雪夫距离：三个方向的差里取最大的那个
double chebyshevDistance(const Point &a, const Point &b)
{
    double dx = fabs(a.x - b.x);
    double dy = fabs(a.y - b.y);
    double dz = fabs(a.z - b.z);
    double m = dx;
    if (dy > m)
        m = dy;
    if (dz > m)
        m = dz;
    return m;
}

// 中点：两个点坐标各取平均，返回一个新的 Point 对象
Point midpoint(const Point &a, const Point &b)
{
    return Point((a.x + b.x) / 2, (a.y + b.y) / 2, (a.z + b.z) / 2);
}

int main()
{
    double x1, y1, z1, x2, y2, z2;
    cin >> x1 >> y1 >> z1;
    cin >> x2 >> y2 >> z2;

    Point A(x1, y1, z1);
    Point B(x2, y2, z2);

    // 下面都保留两位小数
    cout << fixed << setprecision(2);

    cout << "A = ";
    A.display();
    cout << endl;

    cout << "B = ";
    B.display();
    cout << endl;

    cout << "Euclidean distance: " << euclideanDistance(A, B) << endl;
    cout << "Manhattan distance: " << manhattanDistance(A, B) << endl;
    cout << "Chebyshev distance: " << chebyshevDistance(A, B) << endl;

    cout << "Midpoint: ";
    Point m = midpoint(A, B);
    m.display();
    cout << endl;

    // 成员函数和友元函数算出来应该是一样
    cout << "Member function distanceTo: " << A.distanceTo(B) << endl;

    // 选做：重载的那个版本，算到原点的距离
    cout << "Distance from A to origin: " << euclideanDistance(A) << endl;
    cout << "Distance from B to origin: " << euclideanDistance(B) << endl;

    return 0;
}
