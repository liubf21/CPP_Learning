#include <iostream>
#include <chrono>
#include <thread>
#include <dlfcn.h>

int main() {
  // 加载动态链接库
  void* plugin_handle = dlopen("./plugins/libmyplugin.dylib", RTLD_NOW);

  if (!plugin_handle) {
    std::cerr << "Error loading plugin: " << dlerror() << std::endl;
    return 1;
  }

  // 调用函数
  typedef void (*TimerFunc)(int);
  TimerFunc timer_func = (TimerFunc)dlsym(plugin_handle, "timer");

  if (!timer_func) {
    std::cerr << "Error loading symbol: " << dlerror() << std::endl;
    return 1;
  }

  // 调用定时器函数
  timer_func(5);

  // 卸载动态链接库
  dlclose(plugin_handle);

  return 0;
}
