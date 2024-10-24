#include <chrono>
#include <iostream>
#include <random>
#include <iomanip>
#include <iostream>
#include <limits>
#include <numeric>
#include <string>
#include <thread>
#include <utility>
#include <vector>
#include <Eigen/Dense>

#include <constants.h>

using namespace constants;
using matrix = Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic>;

namespace {

void
naive_matrix_multiplication(const matrix& a, const matrix& b, matrix& c, int begin, int end)
{
  for(int i = begin ; i < end; ++i) { // rows
    for(int j = 0; j < b.cols(); ++j) { // cols
      float sum = 0.0f;
      for(int k = 0; k < a.cols(); ++k) {
        sum+=a(i,k)*b(k,j);
      }
      c(i,j)=sum;
    }
  }
}

} // anonymous namespace


int
main(int argc, const char *argv[])
{
  matrix a(rows_cols, rows_cols), b(rows_cols, rows_cols), c(rows_cols, rows_cols);

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<float> dis(-1.0f, 1.0f);

  // check input arguments
   if (argc != 2) {
     std::cerr << "Invalid number of arguments" << std::endl;
     std::cerr << "Usage: naive_matrix_multiplication <number of threads>" << std::endl;
     return -1;
   }

   // initialize the matrices
   // only use random values for the first elements
   a(0, 0) = dis(gen);
   b(0, 0) = dis(gen);
   for(size_t i = 0; i < rows_cols; ++i) {
     for(size_t j = 0; j < rows_cols; ++j) {
       if((i==0) && (j==0)) {
         continue;
       }
       a(i, j) = static_cast<float>(i+j);
       b(i, j) = static_cast<float>(i-j);
     }
   }

   // ToDo Check range
  auto threads = std::stoll(argv[1]);
  std::vector<std::thread> thread_vector;

  auto start = std::chrono::steady_clock::now();

  // divide the steps into threads
  // ToDo ensure rows_cols is a multiple  of the number of threads
  auto steps_per_thread = rows_cols / threads;

  thread_vector.reserve(threads);
  for(int i = 0; i < threads; ++i) {
      int begin = i * steps_per_thread;
      int end = begin + (steps_per_thread - 1);
      thread_vector.push_back(std::thread(naive_matrix_multiplication, std::cref(a), std::cref(b), std::ref(c), begin, end));
  }

  // wait for all threads to complete
  for(auto &t: thread_vector) {
    t.join();
  }

  auto stop = std::chrono::steady_clock::now();
  double ex_time = std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count();
  std::cout << "The delay of multiplying two " << rows_cols << " x " << rows_cols
    << " matrices is: " << ex_time << "ms." << std::endl;
  std::cout << "c(1,1) = " << c(1,1) << std::endl;
  return 0;
}

