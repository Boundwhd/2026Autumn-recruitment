#include <stdio.h>
#include <iostream>

using namespace std;

class Stu
{
public:
	static int age;
	
    static int add(int a, int b)
    {
        return a + b;
    }
	int BMI = weight + height;
private:
	static int weight;
	static int height;
};

int Stu::age = 19;
int Stu::weight = 119;
int Stu::height = 180;

int main()
{   

	static int whd;
	cout << whd << endl;
    int c = Stu::add(1, 2);
    cout << c << endl;
	cout<<Stu::age<<endl;//输出19；
	// cout<<Stu::height<<endl;//错误的，私有无法访问。
	Stu s;
	cout<<s.age<<endl;//输出19；
	cout << s.BMI << endl;
	// cout<<s.height<<endl;//错误的，私有无法访问。
	return 0;
}

/*静态成员可以不用实例化对象调用，并且所有对象共享这个静态变量成员*/
/*静态成员必须类外初始化*/
/*静态成员初始化可以不赋初值*/


