#include <chrono> // for std::chrono::seconds
#include <thread>
#include <iostream>

extern"C" void timer(int duration) {
  std::cout << "Timer started. Duration: " << duration << " seconds." << std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(duration));
  std::cout << "Timer finished." << std::endl;
}
