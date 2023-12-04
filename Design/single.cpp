// 单例模式 - 懒汉式
class singleton {
private:
    singleton() {}
    static singleton *p;
public:
    static singleton *instance();
};
singleton *singleton::p = nullptr;
singleton *singleton::instance() {
    if (p == nullptr) {
        p = new singleton();
    }
    return p;
}
// 实现原理: 将构造函数声明为private或protect防止被外部函数实例化，内部有一个静态的类指针保存唯一的实例，
// 实例的实现由一个public方法来实现，该方法返回该类的唯一实例。
// 多线程时不安全: 考虑两个线程同时首次调用instance方法且同时检测到p是nullptr，
// 则两个线程会同时构造一个实例给p，这将违反了单例的准则。

// 单例模式 - 饿汉式(线程安全)
class singleton2 {
private:
    singleton2() {}
    static singleton2 *p;
public:
    static singleton2 *instance();
};
singleton2 *singleton2::p = new singleton2();
singleton2 *singleton2::instance() {
    return p;
}

#include <mutex>
// 单例模式 - 懒汉式(多线程加锁)
class singleton3
{
private:
    singleton3() {}
    static singleton3 *p;
    static std::mutex lock_;
public:
    static singleton3 *instance();

    // 实现一个内嵌垃圾回收类
    class CGarbo
    {
    public:
        ~CGarbo()
        {
            if (singleton3::p)
            {
                delete singleton3::p;
            }
        }
    };
    static CGarbo Garbo; // 定义一个静态成员变量，程序结束时，系统会自动调用它的析构函数从而释放单例对象
};
singleton3 *singleton3::p = nullptr;
singleton3 *singleton3::instance()
{
    // 加锁，但是这样会导致每次调用都要加锁，效率低
    // std::lock_guard<std::mutex> guard(lock_); // RAII
    // if (p == nullptr) {
    //     p = new singleton3();
    // }
    // 双重检查锁定
    if (p == nullptr) { // 第一次检查
        std::lock_guard<std::mutex> guard(lock_); // RAII
        if (p == nullptr) { // 第二次检查
            p = new singleton3();
        }
    }
    return p;
}
// 第二次检查是必要，因为就像我们刚刚看到的，很有可能另一个线程偶然在第一次检查之后，获得锁成功之前初始化p。
// 漏洞: 内存读写的乱序执行(编译器问题)
// 对于 p = new singleton; 分三个步骤:1. 分配内存 2. 构造对象 3. p指向内存
// 1一定最先执行，但2未必在3之前，因此仍然可能在线程切换时导致错误(对象还未构造，但已指向内存，此时被挂起，另一个线程调用)
// 在C++11中规定了新的内存模型，保证了执行上述3个步骤的时候不会发生线程切换，相当这个初始化过程是
// “原子性”的的操作，DCL又可以正确使用了，不过在C++11下却有更简洁的多线程singleton写法了

// 简洁写法
// singleton3 *singleton3::instance()
// {
//     static singleton3 p;
//     return &p;
// }

int main()
{
    singleton *p1 = singleton::instance();
    singleton *p2 = singleton::instance();
    return 0;
}