# CPP learning

面向成为优秀程序员(找到高薪工作)的C++学习之路

1. 熟悉C++程序的编译链接过程
2. 熟悉C++高级用法和现代C++的主要特性
3. 用C++实现一些常用的数据结构和算法，与STL进行比较
4. 熟悉C++多线程和网络编程
5. 用C++实现一些常用的设计模式
6. 熟悉单元测试
7. 熟悉性能分析和调优
8. 项目

[应对面试](https://csguide.cn/cpp/intro.html)

[TOC]

## 编译链接过程

在 C++ 中，理解编译和链接过程对初学者来说是非常重要的，因为它帮助你理解从源代码到可执行文件的转换过程，以及在这个过程中可能遇到的问题。

### 编译过程

1. **预处理 (Preprocessing)**: 
   - 预处理器(如 `cpp`)处理源代码文件。这一步包括展开宏定义，处理条件编译指令(如 `#ifdef`, `#ifndef`, `#endif`)，以及包含头文件(`#include`)。
   - 预处理后的代码不包含宏定义和头文件引用，而是包含了这些宏和头文件的实际内容。

2. **编译 (Compilation)**:
   - 编译器(如 `g++` 或 `clang`)将预处理过的代码转换成汇编代码。
   - 在这个阶段，编译器还会进行语法和语义分析，确保代码符合 C++ 的规则，并生成汇编代码。

3. **汇编 (Assembly)**:
   - 汇编器将汇编代码转换为机器码，生成目标文件(通常是 `.o` 或 `.obj` 文件)。
   - 每个源文件都会被单独编译和汇编成一个目标文件。

### 链接过程

1. **链接 (Linking)**:
   - 链接器(如 `ld`)将一个或多个目标文件与必要的库文件链接在一起，生成最终的可执行文件或库文件。
   - 有两种链接方式：
     - **静态链接**：所有需要的代码都会被复制到最终的可执行文件中，使其体积增大，但是运行时不依赖外部库。
     - **动态链接**：链接时不复制代码，而是在运行时从动态链接库(如 `.dll` 或 `.so` 文件)中加载。这减小了可执行文件的大小，但运行时需要确保动态库可用。

### 构建系统

- 在 C++ 中，还有一些构建系统工具，如 `cmake`, `xmake`, `bazel` 等，这些工具可以自动化编译和链接过程。
- 它们通常提供了跨平台构建的能力，可以根据不同平台和编译器的需求，自动生成相应的构建文件和指令。

### 面试官可能的提问

在面试中，面试官可能会问到与编译链接相关的问题，比如：

1. 解释 C++ 编译和链接过程的每个阶段。
2. 静态链接和动态链接有什么区别？
3. C++ 中预处理器是做什么的？
4. 为什么需要不同的构建系统，如 `cmake` 或 `bazel`？
5. 在编译过程中会进行哪些优化？

> 深入学习，参考《深入理解计算机系统》《程序员的自我修养》

确实，为了成为 C++ 编程大师，了解和掌握 C++ 的高级用法和现代特性是非常关键的。以下是按照一定顺序组织的提纲，旨在全面覆盖高级用法和现代 C++ 的主要特性：

## C++ 高级用法和现代 C++ 的主要特性

### 标准库

1. **标准模板库 (STL)**
   - 容器：`vector`, `map`, `set`, `list` 等。
   - 迭代器：用于遍历和操作容器中的元素。
   - 算法：`sort`, `find`, `transform`, `accumulate` 等。
   - 函数对象：包括函数指针、Lambda 表达式和仿函数。

2. **输入/输出 (I/O) 库**
   - 标准输入输出流：`cin`, `cout`, `cerr`。
   - 文件读写：`fstream`。

3. **字符串和字符处理**
   - `std::string` 和 `std::wstring`。
   - C 风格字符串函数。

4. **正则表达式处理**
   - `std::regex` 和相关函数。

5. **日期和时间处理**

6. **随机数生成**


### 高级语言特性

1. **类型系统和变量**
   - 基础数据类型、结构体、类、枚举、联合体。
   - 类型推导：`auto` 和 `decltype`。

2. **对象生命周期管理**
   - 构造函数、析构函数、拷贝控制、移动语义。

3. **宏和预处理器指令**
   - 宏定义、条件编译。
   - 宏在实现简单反射和代码生成的应用。

4. **错误处理和异常机制**
   - 异常类、异常捕获和抛出、异常安全性。

5. **类型转换和 RTTI**
   - 静态和动态类型转换。
   - 运行时类型信息(RTTI)：`typeid` 和 `dynamic_cast`。

### 模板和泛型编程

1. **模板编程**
   - 类和函数模板。
   - 模板特化和重载。
   - 变参模板和模板元编程(TMP)。
   - 类型萃取和类型推导。

2. **Lambda 表达式和函数对象**
   - Lambda 表达式的高级用法：捕获列表、返回类型推断、泛型 Lambda。
   - `std::function` 和 `std::bind`。

### 并发编程

- **多线程编程**
  - 线程的创建和管理：`std::thread`。
  - 同步机制：互斥量(`std::mutex`)、条件变量(`std::condition_variable`)、原子操作(`std::atomic`)。

### 内存管理

1. **原始内存管理**:
   - 包括使用 `new` 和 `delete` 管理动态内存。
   - 需要手动管理内存生命周期，容易导致内存泄漏、悬挂指针等问题。

2. **智能指针**
   - `std::unique_ptr`, `std::shared_ptr`, `std::weak_ptr`。

3. **自定义内存管理**
   - 内存池、自定义分配器。
   - RAII(资源获取即初始化)模式。

#### 智能指针

在 C++ 中，智能指针是一种自动管理资源(如动态分配的内存)生命周期的对象。它们主要包括 `std::unique_ptr`, `std::shared_ptr`, 和 `std::weak_ptr`。以下是这些智能指针的详细使用示例，以及它们的主要成员函数和特性。

##### 1. `std::unique_ptr`

`std::unique_ptr` 是一种独占所有权的智能指针，一次只能有一个 `std::unique_ptr` 拥有对某个资源的所有权。当 `std::unique_ptr` 被销毁时(如离开作用域或被显式删除)，它指向的对象也会被自动删除。

**基本使用**:

```cpp
#include <memory>

struct MyClass {
    int x;
    MyClass(int val) : x(val) {}
    ~MyClass() { std::cout << "资源释放\n"; }
};

int main() {
    std::unique_ptr<MyClass> ptr(new MyClass(10));
    std::cout << ptr->x << std::endl;  // 使用 -> 访问成员
}
```

**主要函数**:

- `get()`: 返回存储的指针。
- `reset()`: 释放所有权并可选择绑定到新的原始指针。
- `release()`: 释放所有权但不删除对象。
- `swap()`: 交换两个 `unique_ptr` 对象。

##### 2. `std::shared_ptr`

`std::shared_ptr` 是一种共享所有权的智能指针。可以有多个 `std::shared_ptr` 实例指向同一个对象。对象仅在最后一个指向它的 `std::shared_ptr` 被销毁或重置时被删除。

**基本使用**:

```cpp
#include <memory>

int main() {
    std::shared_ptr<MyClass> ptr1 = std::make_shared<MyClass>(20); // std::shared_ptr<MyClass> ptr1(new int(20));
    std::shared_ptr<MyClass> ptr2 = ptr1;  // ptr1 和 ptr2 共享所有权

    std::cout << ptr1->x << std::endl;
    std::cout << ptr2.use_count() << std::endl;  // 输出共享所有者的数量
}
```

**主要函数**:

- `get()`: 返回存储的指针。
- `reset()`: 释放所有权并可选择绑定到新的原始指针。
- `use_count()`: 返回指向对象的 `shared_ptr` 实例数量。
- `swap()`: 交换两个 `shared_ptr` 对象。

##### 3. `std::weak_ptr`

`std::weak_ptr` 是一种不控制所有权的智能指针。它被设计用来观察 `std::shared_ptr`，但不延长被观察对象的生命周期。当其指向的对象被删除时，`std::weak_ptr` 会自动变为空。

**基本使用**:

```cpp
#include <memory>

int main() {
    std::shared_ptr<MyClass> shared = std::make_shared<MyClass>(30);
    std::weak_ptr<MyClass> weak = shared;

    if (auto temp = weak.lock()) {  // 尝试将 weak_ptr 转换为 shared_ptr
        std::cout << temp->x << std::endl;
    }
}
```

**主要函数**:

- `expired()`: 检查所指对象是否已被删除。
- `lock()`: 尝试将 `std::weak_ptr` 转换为 `std::shared_ptr`。
- `reset()`: 释放对对象的观察。
- `swap()`: 交换两个 `std::weak_ptr` 对象。

总结:

智能指针的使用可以大大减少资源泄漏的风险，并使资源管理更加简单。它们是现代 C++ 中管理动态分配资源的首选方式，相较于裸指针，提供了更安全、更高效的资源管理机制。

### 元编程和编译时计算

- **编译时计算**
  - `constexpr` 函数和变量。
  - SFINAE(Substitution Failure Is Not An Error)。
  - 类型萃取和 C++20 的概念(Concepts)。

### 宏和反射

- **宏的高级用法**
  - 使用宏实现简单的编译时决策和代码生成。
  - 通过宏模拟 C++ 中的反射特性。


针对 C++ 的语法和特性，我们已经覆盖了许多关键内容，包括基础语法、高级特性、标准库的使用、模板编程、并发编程、内存管理等。不过，为了确保更全面，我们可以进一步探讨一些可能未被充分涉及的领域：

### C++ 语法和特性的补充

1. **操作符重载**
   - 允许给现有的 C++ 操作符提供用户定义的含义，用于自定义数据类型。

2. **命名空间**
   - 使用命名空间组织代码，避免命名冲突。

3. **C++17 和 C++20 新特性**
   - 结构化绑定、`if constexpr`、内联变量。
   - 概念(Concepts)、协程、范围(Ranges)。

4. **元类和反射**(C++23 及未来方向)
   - 元类提议是一个正在讨论的特性，旨在引入反射和更强大的元编程能力。

5. **依赖注入**
   - 虽然不是语言内置特性，但在现代 C++ 开发中，依赖注入作为一种设计模式，用于提高代码的模块化和可测试性。

6. **异步编程和事件驱动编程**
   - 使用异步 I/O 模型和事件循环来处理并发。

7. **文件系统交互**
   - C++17 引入的 `<filesystem>` 库的使用。

8.  **C++ 互操作性**
    - 与其他语言(如 C、Python)的互操作性。

9.  **C++ 编译器特有的扩展**
    - 了解不同编译器(如 GCC, Clang, MSVC)提供的特定扩展。

10. **跨平台开发**
    - 编写可以在不同操作系统(如 Windows, Linux, macOS)上编译和运行的代码。



## 多线程和网络编程

阅读《Linux 多线程服务端编程》

- **线程管理**：创建和控制线程的生命周期。
- **同步机制**：互斥量、锁、条件变量、原子操作。
- **并行算法**：利用多核处理器进行数据并行处理。
  - 线程库 (`std::thread`)，任务异步执行 (`std::async`)。
  - 原子操作和内存模型(`std::atomic`)。
    - 并行算法(`std::for_each`，`std::transform`，`std::reduce`)。


依赖注入（Dependency Injection，简称 DI）是一种软件设计模式，其目的是实现控制反转（Inversion of Control，简称 IoC）的一种形式，用于减少代码之间的耦合。虽然依赖注入并非 C++ 语言特有的概念，但它在 C++ 中的应用同样重要。

依赖注入指的是组件间依赖关系（通常是服务、配置数据等）不是由组件内部自行创建或查找，而是由外部容器或框架在运行时提供。这种方式有几个关键好处：

1. 降低耦合：组件不需要了解如何创建其依赖项。
2. 增强模块化：更容易替换组件的实现或配置。提高测试性：便于对组件进行单元测试，因为依赖可以被模拟（mock）或存根（stub）。


## 数据结构和算法

链表 核心：哨兵节点+虚拟节点+链表指针的移动
快排，堆排(要点在于实现上滤和下滤操作，用循环即可;删除是将堆顶与最后一个元素交换，对堆顶进行下滤) 
OpenMP 实现多线程
归并，希尔
vector string map
shared_ptr
memcpy
LRU
redis中的跳表
图论各种算法
并查集
字符串 KMP，BM 算法
字典树 线段树 K-D树 
AVL树 Splay树 B树和B+树 红黑树(https://juejin.cn/post/6844903842513944583)
常见的贪心和DP问题

## 设计模式

https://www.liaoxuefeng.com/wiki/1252599548343744/1264742167474528

1. **设计模式**:
   - 常见的设计模式，如单例、工厂、观察者、策略、适配器模式等。

2. **软件工程原则**:
   - SOLID 原则，DRY (Don't Repeat Yourself)。

行为性模式:策略 
结构性模式:适配器 
创建性模式:单例 工厂

观察者模式
工厂模式： 简单工厂模式 工厂方式模式和抽象工厂模式 模板工厂模式
https://zhuanlan.zhihu.com/p/83535678


Observer 模式是一种设计模式，允许对象(观察者)订阅另一个对象(主题)的状态变化，当主题状态变化时，自动通知所有观察者。这在多线程环境中尤为重要，因为状态的改变可能由不同的线程触发。

Observer 定义了对象之间的一对多依赖关系，使得当一个对象(称为“subject”或“observable”)改变状态时，所有依赖它的对象(称为“observers”)都会得到通知并自动更新。下面是使用 C++ 实现的 Observer 设计模式的示例：

首先，定义 Observer 和 Observable 的接口：

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

// Observer 接口声明了更新接口，用于从 subjects 接收更新
class Observer {
public:
    virtual ~Observer() {}
    virtual void Update(const std::string &message_from_subject) = 0;
};

// Subject 接口声明了一系列管理 observers 的方法
class Subject {
public:
    virtual ~Subject() {}
    virtual void Attach(Observer *observer) = 0;
    virtual void Detach(Observer *observer) = 0;
    virtual void Notify() = 0;
};
```

然后，实现具体的 Subject 类，它在状态改变时通知所有的 Observers：

```cpp
// ConcreteSubject 管理观察者的订阅和取消订阅，并通知他们状态改变
class ConcreteSubject : public Subject {
public:
    void Attach(Observer *observer) override {
        list_observer_.push_back(observer);
    }

    void Detach(Observer *observer) override {
        list_observer_.remove(observer);
    }

    void Notify() override {
        std::list<Observer *>::iterator iterator = list_observer_.begin();
        HowManyObserver();
        while (iterator != list_observer_.end()) {
            (*iterator)->Update(message_);
            ++iterator;
        }
    }

    void CreateMessage(std::string message = "Empty") {
        this->message_ = message;
        Notify();
    }

    void HowManyObserver() {
        std::cout << "There are " << list_observer_.size() << " observers in the list.\n";
    }

private:
    std::list<Observer *> list_observer_;
    std::string message_;
};
```

最后，实现具体的 Observer 类，它会接收来自 Subject 的更新：

```cpp
// ConcreteObserver 每次收到更新消息时都会打印输出
class ConcreteObserver : public Observer {
public:
    ConcreteObserver(Subject &subject) : subject_(subject) {
        this->subject_.Attach(this);
        std::cout << "Hi, I'm the Observer \"" << ++ConcreteObserver::static_number_ << "\".\n";
        this->number_ = ConcreteObserver::static_number_;
    }

    virtual ~ConcreteObserver() {
        std::cout << "Goodbye, I was the Observer \"" << this->number_ << "\".\n";
    }

    void Update(const std::string &message_from_subject) override {
        message_from_subject_ = message_from_subject;
        PrintInfo();
    }

    void RemoveMeFromTheList() {
        subject_.Detach(this);
        std::cout << "Observer \"" << number_ << "\" removed from the list.\n";
    }

    void PrintInfo() {
        std::cout << "Observer \"" << this->number_ << "\": a new message is available --> " << this->message_from_subject_ << "\n";
    }

private:
    std::string message_from_subject_;
    Subject &subject_;
    static int static_number_;
    int number_;
};

int ConcreteObserver::static_number_ = 0;

void ClientCode() {
    ConcreteSubject *subject = new ConcreteSubject;
    ConcreteObserver *observer1 = new ConcreteObserver(*subject);
    ConcreteObserver *observer2 = new ConcreteObserver(*subject);
    ConcreteObserver *observer3 = new ConcreteObserver(*subject);
    ConcreteObserver *observer4;
    ConcreteObserver *observer5;

    subject->CreateMessage("Hello World! :D");
    observer3->RemoveMeFromTheList();

    subject->CreateMessage("The weather is hot today! :p");
    observer4 = new ConcreteObserver(*subject);

    observer2->RemoveMeFromTheList();
    observer5 = new ConcreteObserver(*subject);

    subject->CreateMessage("My new car is great! ;)");
    observer5->RemoveMeFromTheList();

    observer4->RemoveMeFromTheList();
    observer1->RemoveMeFromTheList();

    delete observer5;
    delete observer4;
    delete observer3;
    delete observer2;
    delete observer1;
    delete subject;
}

int main() {
    ClientCode();
    return 0;
}
```

在这个例子中，`ConcreteSubject` 类是一个具体的被观察

对象，它维护一个 Observer 列表并在状态改变时通知它们。`ConcreteObserver` 类是一个具体的观察者，它实现了 `Update` 方法来接收来自 Subject 的消息。`ClientCode` 函数演示了如何创建 Subject 和多个 Observers，并展示了当 Subject 状态改变时如何通知它们。

Observer 模式广泛用于实现事件处理系统、数据模型与视图的分离(如 MVC 架构)以及发布/订阅系统。

## 单元测试

Google Test

## 性能分析和调优

使用工具(如 Valgrind、gprof)进行性能分析

## 项目

正则解析 
json解析 https://github.com/miloyip/json-tutorial
WebServer
光栅化渲染器：
光线追踪渲染器：

Muduo C++网络库：
brpc 百度的 C++ RPC 框架：
workflow 搜狗开源的 C++ 轻量级工作流引擎：
在 C++ 上实现类似 Go goroutine 的库：https://github.com/idealvin/coost
阿里开源的轻量级 C++ 异步框架：https://github.com/alibaba/async_simple
一款简单、高效的实时视频服务器：https://github.com/ossrs/srs 
轻量级中文 OCR 项目：https://github.com/DayBreak-u/chineseocr_lite 
游戏《金庸群侠传》的 C++ 复刻版：https://github.com/scarsty/kys-cpp

