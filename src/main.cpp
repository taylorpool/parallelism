#include <algorithm>
#include <chrono>
#include <execution>
#include <iostream>
#include <vector>

void print_vector(const std::vector<double> vec) {
  for (const auto x : vec) {
    std::cout << x << ", ";
  }
  std::cout << "\n";
}

int main(int argc, char *argv[]) {

  // We will start with this vector
  std::vector<double> vec0{0.0, 1.0, 2.0, 3.0};

  std::cout << "original vector\n";
  print_vector(vec0);
  std::cout << "\n";

  {
    const auto start = std::chrono::system_clock::now();

    // Transform each element sequentially and time it!
    // std::transform transforms a container that has a begin and a end iterator
    // (can think of these as pointers).
    // The begin iterator of the output range also has to be passed in. Note
    // that std::transform does not do any allocation, so the output vector
    // already has to have the correct number of allocated elements prior to
    // passing to std::transform. Otherwise, you can use std::back_inserter and
    // it will allocate as you go. But using std::back_inserter is naturally
    // slower
    std::transform(vec0.begin(), vec0.end(), vec0.begin(),
                   [](double &x) { return x + 1; });
    const auto end = std::chrono::system_clock::now();

    std::cout << "sequentially transformed vector\n";
    std::cout << "took "
              << std::chrono::duration_cast<std::chrono::nanoseconds>(end -
                                                                      start)
                     .count()
              << " nanoseconds \n";
    print_vector(vec0);
    std::cout << "\n";
  }

  {
    const auto start = std::chrono::system_clock::now();

    // Transform each element in parallel unsequenced and time it! Unsequenced
    // means it does not matter which element is transformed first.
    std::transform(std::execution::par_unseq, vec0.begin(), vec0.end(),
                   vec0.begin(), [](double &x) { return x + 1; });
    const auto end = std::chrono::system_clock::now();

    std::cout << "parallel unsequenced transformed vector\n";
    std::cout << "took "
              << std::chrono::duration_cast<std::chrono::nanoseconds>(end -
                                                                      start)
                     .count()
              << " nanoseconds \n";
    print_vector(vec0);
    std::cout << "\n";
  }

  return 0;
}
