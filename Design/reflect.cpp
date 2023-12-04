#include <iostream>
#include <map>
#include <string>

// 基类
class Object {
public:
    virtual std::string getClassName() const = 0;
};

// 宏定义，本质上和写在类中一样，但能够便于重用
#define REFLECT(CLASS) \
    static std::string className; \
    virtual std::string getClassName() const { \
        return className; \
    }

// 宏定义，声明派生类的反射信息
#define REFLECT_DEFINE(CLASS) \
    std::string CLASS::className = #CLASS

// 派生类
class MyClass : public Object {
public:
    REFLECT(MyClass)
};

// 定义派生类的反射信息
REFLECT_DEFINE(MyClass);

int main() {
    MyClass obj;
    std::cout << obj.getClassName() << std::endl; // 输出 "MyClass"
    return 0;
}


/*
反射是指在程序运行时获取类型信息的能力，C++通过RTTI（Run-Time Type Information）实现了部分反射机制。
RTTI允许程序在运行时查询和操作类的类型信息，包括类的名字、继承关系、成员变量和函数等信息。
可以通过使用typeid运算符获取对象的类型信息，也可以使用dynamic_cast运算符进行动态类型转换。

此外，C++也可以使用预处理器和模板等技术来实现基本的反射功能。
在上面的例子中，使用了 REFLECT 宏来声明一个虚函数 getClassName ，并在宏中生成了一个 className 静态变量。
这样，每个派生类都可以通过实现 REFLECT 宏来自动获取自己的类名，无需手动实现 getClassName 函数。
同时，在每个派生类中通过 REFLECT_DEFINE 宏来定义自己的类名。

但是使用宏定义可以减少代码的重复性，使代码更加简洁和易读。
而且如果有多个类需要进行反射，使用宏定义可以大幅减少代码量和维护成本。
*/