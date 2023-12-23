#include "threadpool.h"

#include <iostream>
#include <thread>
#include <mutex>


int main() {
    ThreadPool pool(4);
    std::mutex m;
    int n = 20;
    for (int i = 0; i < n; i++) {
        std::cout << "submitting " << i << std::endl;
        pool.submit([&m, i] {
            std::unique_lock<std::mutex> lock(m);
            std::cout << i << "from thread" << std::this_thread::get_id() << std::endl;
        });
    }
}