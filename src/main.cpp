#include <algorithm>
#include <chrono>
#include <execution>
#include <iostream>
#include <vector>

struct Timer {
  decltype(std::chrono::system_clock::now()) m_start;

  [[nodiscard]] Timer() : m_start(std::chrono::system_clock::now()) {}

  ~Timer() {
    const auto end = std::chrono::system_clock::now();
    std::cout << "Took "
              << std::chrono::duration_cast<std::chrono::nanoseconds>(end -
                                                                      m_start)
                     .count()
              << " nanoseconds\n";
  }
};

void print_vector(const std::vector<double> vec) {
  for (const auto x : vec) {
    std::cout << x << ", ";
  }
  std::cout << "\n";
}

int main(int argc, char *argv[]) {

  // We will start with this vector
  std::vector<double> vec0{0.0, 1.0, 2.0, 3.0, 4.0, 5.0,
                           6.0, 7.0, 8.0, 9.0, 10.0};

  std::cout << "original vector\n";
  print_vector(vec0);
  std::cout << "\n";

  // Transform each element sequentially and time it!
  // std::transform transforms a container that has a begin and a end iterator
  // (can think of these as pointers).
  // The begin iterator of the output range also has to be passed in. Note
  // that std::transform does not do any allocation, so the output vector
  // already has to have the correct number of allocated elements prior to
  // passing to std::transform. Otherwise, you can use std::back_inserter and
  // it will allocate as you go. But using std::back_inserter is naturally
  // slower
  std::cout << "sequentially transforming vector\n";
  {
    Timer timer;
    std::transform(vec0.begin(), vec0.end(), vec0.begin(),
                   [](double &x) { return x + 1; });
  }
  print_vector(vec0);
  std::cout << "\n";

  // Transform each element in parallel unsequenced and time it! Unsequenced
  // means it does not matter which element is transformed first.
  std::cout << "parallel unsequence transforming vector\n";
  {
    Timer timer;
    std::transform(std::execution::par_unseq, vec0.begin(), vec0.end(),
                   vec0.begin(), [](double &x) { return x + 1; });
  }
  print_vector(vec0);
  std::cout << "\n";

  std::cout << "sequential summing vector\n";
  {
    double tmp;
    {
      Timer timer;
      tmp = std::reduce(vec0.cbegin(), vec0.cend(), 0.0, std::plus<double>());
    }
    std::cout << "sum: " << tmp << "\n\n";
  }

  std::cout << "parallel unsequence summing vector\n";
  {
    double tmp;
    {
      Timer timer;
      tmp = std::reduce(std::execution::par_unseq, vec0.cbegin(), vec0.cend(),
                        0.0, std::plus<double>());
    }
    std::cout << "sum: " << tmp << "\n\n";
  }

  return 0;
}
