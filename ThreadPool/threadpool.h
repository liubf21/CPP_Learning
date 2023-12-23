#include <iostream>
#include <thread>
#include <mutex>
#include <shared_mutex>
#include <condition_variable>
#include <chrono>
#include <ctime>
#include <vector>
#include <queue>
#include <functional>
#include <future>


template<typename T>
struct safe_queue {
    std::queue<T> _q;
    mutable std::shared_mutex _m; // mutable to allow locking in const methods

    bool empty() const {
        std::shared_lock<std::shared_mutex> lock(_m);
        return _q.empty();
    }
    auto size() const {
        std::shared_lock<std::shared_mutex> lock(_m);
        return _q.size();
    }
    void push(T& val) {
        std::unique_lock<std::shared_mutex> lock(_m);
        _q.push(val);
    }
    bool pop(T& val) {
        std::unique_lock<std::shared_mutex> lock(_m);
        if (_q.empty()) {
            return false;
        }
        val = std::move(_q.front());
        _q.pop();
        return true;
    }
};

class ThreadPool {
    class worker {
        ThreadPool* pool;
    public:
        worker(ThreadPool* pool): pool(pool) {}
        void operator()() {
            while (!pool->is_shutdown) {
                {
                    std::unique_lock<std::mutex> lock(pool->_m);
                    pool->_cv.wait(lock, [this] { return !pool->tasks.empty() || pool->is_shutdown; });
                }
                std::function<void()> task;
                if (pool->tasks.pop(task)) {
                    task();
                }
            }
        }
    };

public:
    bool is_shutdown;
    safe_queue<std::function<void()>> tasks;
    std::vector<std::thread> threads;
    std::mutex _m;
    std::condition_variable _cv; // std::condition_variable is a type that can be used to notify other threads

    ThreadPool(int n): is_shutdown{false}, threads(n) {
        for (auto& t: threads) {
            t = std::thread{ worker{this} }; // std::thread is a type that can be used to create a thread
        }
    }
    ThreadPool(const ThreadPool&) = delete; // delete copy constructor
    ThreadPool(ThreadPool&&) = delete; // delete move constructor
    ThreadPool& operator=(const ThreadPool&) = delete; // delete copy assignment
    ThreadPool& operator=(ThreadPool&&) = delete; // delete move assignment

    template<typename F, typename... Args>
    auto submit(F&& f, Args&&... args) -> std::future<decltype(f(args...))> { // std::future is a type that can be used to get the return value of a function
        std::function<decltype(f(args...))()> func = [&f, &args...]() { return f(args...); }; // [&f, &args...] is a lambda function that captures f and args by reference
        auto task = std::make_shared<std::packaged_task<decltype(f(args...))()>>(func); // std::packaged_task is a type that can be used to wrap a function
        std::function<void()> wrapper_func = [task]() { (*task)(); };
        tasks.push(wrapper_func);
        _cv.notify_one();
        return task->get_future();        
    }

    ~ThreadPool() {
        auto f = submit([]() {}); // submit a task that does nothing
        f.get(); // wait for the task to finish
        is_shutdown = true;
        _cv.notify_all();
        for (auto& t: threads) { 
            if (t.joinable()) {
                t.join(); // wait for the thread to finish
            }
        }
    }
};
