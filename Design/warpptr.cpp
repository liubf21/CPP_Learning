#include <iostream>
#include <stdexcept>

// WrapPtr is a class template that wraps a pointer to a dynamically allocated array
template <typename T>
class WrapPtr
{
    T * ptr_;

    // prohibit copying and assignment: prevent resource being shared
    WrapPtr(WrapPtr const &) = delete;
    WrapPtr & operator = (WrapPtr const &) = delete;

public:
    // constructor
    explicit WrapPtr(T *p = 0) : ptr_(p) {}

    // destructor
    ~WrapPtr() { delete ptr_; std::cout << "destructor called" << std::endl; }
    
    // move constructor
    WrapPtr(WrapPtr && wp) noexcept : ptr_(wp.ptr_) { wp.ptr_ = nullptr; }

    // move assignment
    WrapPtr & operator = (WrapPtr && wp) noexcept
    {
        if (this != &wp)
        {
            delete ptr_;
            ptr_ = wp.ptr_;
            wp.ptr_ = nullptr;
        }
        return *this;
    }

    T& operator [] (size_t index) noexcept { return ptr_[index]; } // noexcept makes compiler do more optimization
    T const & operator [] (size_t index) const noexcept { return ptr_[index]; }
    T * get_data() const noexcept { return ptr_; }
};

void testWrapPtr()
{
    auto p = new double[10];
    if (!p) throw "memory allocation failure";
    WrapPtr<double> wp(p);
    for (auto i = 0; i < 10; ++i)
    {
        // auto score{0.0}; // {} is safer than () for initialization because it prevents narrowing
        // std::cin >> score;
        // if (score < 0) throw "score must be non-negative";
        // else wp[i] = score;
        wp[i] = i * 0.5 + 1;
    }
    std::cout << "wp[1] = " << wp[1] << std::endl;
    std::cout << "wp[2] = " << wp[2] << std::endl;

    // test move constructor
    WrapPtr<double> wp2(std::move(wp));
    // WrapPtr<double> wp2(wp.get_data()); // will call destructor twice 
    std::cout << "wp2[1] = " << wp2[1] << std::endl;
    std::cout << "wp2[2] = " << wp2[2] << std::endl;
}

int main()
{
    try {
        testWrapPtr();
    }
    catch (std::exception const & e)
    {
        std::cerr << "exception: " << e.what() << std::endl;
    }
    return 0;
}