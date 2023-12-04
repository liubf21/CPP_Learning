#include <iostream>

template <typename T>
class WrapPtr
{
    T * ptr_;
    // prohibit copying and assignment: prevent resource being shared
    WrapPtr(WrapPtr const &) = delete;
    WrapPtr & operator = (WrapPtr const &) = delete;

public:
    WrapPtr(T *p = 0) : ptr_(p) {}
    ~WrapPtr() { delete ptr_; std::cout << "destructor called" << std::endl; }
    T& operator [] (size_t index) noexcept { return ptr_[index]; } // noexcept makes compiler do more optimization
    T const & operator [] (size_t index) const noexcept { return ptr_[index]; }
    T * get_data() const noexcept { return ptr_; }
};

auto get_scores()
{
    auto p = new double[100];
    if (!p) throw "memory allocation failure";
    WrapPtr<double> wp(p);
    for (auto i = 0; i < 100; ++i)
    {
        auto score{0.0};
        std::cin >> score;
        if (score < 0) throw "score must be non-negative";
        else wp[i] = score;
    }
    return wp.get_data();
}

void fun()
{
    try 
    {
        std::cout << "Enter scores: " << std::endl;
        auto scores = get_scores();
        std::cout << scores[0] << std::endl;
    }
    catch (char const * msg)
    {
        std::cerr << msg << std::endl;
    }
}

int main()
{
    int i{1.5};
    // int i(1.5);
    fun();
    return 0;
}