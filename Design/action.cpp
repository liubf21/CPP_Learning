#include <iostream>
using namespace std;

// 模版方法是一种针对接口编程的设计。模版方法的思想是，基类是一个模板（也可以称作原型）。
// 基类体现的是“抽象概念”，里面定义若干个纯虚函数，这些函数提供了这个类的“接口”。
class AbstractClass {
public:
    virtual void Operation1() = 0;
    virtual void Operation2() = 0;
};

class ConcreteClassA: public AbstractClass {
public:
    void Operation1() {
        cout << "Do Operation 1 of A" << endl;
    }
    void Operation2() {
        cout << "Do Operation 2 of A" << endl;
    }
};

class ConcreteClassB: public AbstractClass {
public:
    void Operation1() {
        cout << "Do Operation 1 of B" << endl;
    }
    void Operation2() {
        cout << "Do Operation 2 of B" << endl;
    }
};

// 现在我们有了很多继承自同一个抽象类的实现类，该怎么实现多态呢？
// 我们知道，模板多态是依赖于指针和引用的。编译器能够通过指针和引用判断实际指向的类型，并且调用实际类型
// 里面 override 了的虚函数。所以在使用模板模式的时候，常常创建基类指针来调用实现类的函数。

int test1() {
    AbstractClass *abstract;
    abstract = new ConcreteClassB();
    abstract->Operation1();
    abstract->Operation2();
    return 0;
}

// 策略模式：定义一系列算法并加以封装，使得这些算法可以互相替换。
// 这样，一种算法就不需要依附于某个实现类了，而是自成一类。
// 具体而言：每一种行为各自有方法虚基类 A、B 每一个方法基类 A 有若干具体的方法 A1、A2、A3​，每一种都会继承 A​
// 所有对象具有一个对象基类 O​，对象基类 O​ 含有所有的方法基类指针 A*​、B*​，从而实现多态。
// 注意到对象基类如果仅含有方法基类指针，实际上没法调用方法基类的方法，故而还需要调用接口
// 每种对象是一个具体的对象类 O1、O2、O3​，每种都会继承对象类 O​，同时让方法基类指针 A*​、B* ​具体指向方法派生类上 Ax、By​

class FlyBehavior {
public:
    virtual ~FlyBehavior() { };
    virtual void fly() = 0;
};

class QuackBehavior {
public:
    virtual ~QuackBehavior() { };
    virtual void quack() = 0;
};

class Duck{
public:
    Duck(FlyBehavior* p_FlyBehavior, QuackBehavior* p_QuackBehavior) {
        pFlyBehavior = p_FlyBehavior;
        pQuackBehavior = p_QuackBehavior;
    }

    virtual ~Duck() { };
    virtual void display() { };

    void performFly() {
        pFlyBehavior->fly();
    }

    void performQuack() {
        pQuackBehavior->quack();
    }

private:
    FlyBehavior* pFlyBehavior;
    QuackBehavior* pQuackBehavior;
};

class FlyWithWings: public FlyBehavior {
public:
    void fly() {
        std::cout << "I'm flying!!" << std::endl;
    }
};

class FlyNoWay: public FlyBehavior {
public:
    void fly() {
        std::cout << "I can't fly" << std::endl;
    }
};

class Quack: public QuackBehavior {
public:
    void quack() {
        std::cout << "Quack" << std::endl;
    }
};

class MuteQuack: public QuackBehavior {
public:
    void quack() {
        std::cout << "<< Slience >>" << std::endl;
    }
};

class Squeak: public QuackBehavior {
public:
    void quack() {
        std::cout << "Squeak" << std::endl;
    }
};

class MallardDuck: public Duck { // 继承了对象基类，就已经有了方法基类指针
public:
    MallardDuck(
        FlyBehavior* fly_behavior = new FlyWithWings(), // 构造函数含有缺省值
        QuackBehavior* quack_behavior = new Quack())
            : Duck(fly_behavior, quack_behavior) { } // 绿头鸭的构造函数，飞行和叫声的基类指针分别指向了对应的实现类

    void display() {
        std::cout << "I'm a real Mallard duck" << std::endl;
    }
};

class RubberDuck: public Duck {
public:
    RubberDuck(
        FlyBehavior* fly_behavior = new FlyNoWay(),
        QuackBehavior* quack_behavior = new Squeak())
            : Duck(fly_behavior, quack_behavior) { }

    void display() {
        std::cout << "I'm a Rubber duck" << std::endl;
    }
};

class DecoyDuck: public Duck {
public:
    DecoyDuck(
        FlyBehavior* fly_behavior = new FlyNoWay(),
        QuackBehavior* quack_behavior = new MuteQuack())
            : Duck(fly_behavior, quack_behavior) { }

    void display() {
        std::cout << "I'm just a Decoy duck" << std::endl;
    }
};

int test2() {
    Duck* mallard = new MallardDuck();
    mallard->display();
    mallard->performFly();
    mallard->performQuack();

    Duck*rubber = new RubberDuck();
    rubber->display();
    rubber->performQuack();
    return 0;
}

int main() {
    test1();
    test2();
    return 0;
}

/*
output:
Do Operation 1 of B
Do Operation 2 of B
I'm a real Mallard duck
I'm flying!!
Quack
I'm a Rubber duck
Squeak
*/