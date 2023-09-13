#include <chrono>
#include <iostream>
#include <random>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <limits>
#include <numeric>
#include <string>
#include <thread>
#include <utility>
#include <vector>
#include <Eigen/Dense>

constexpr size_t rows_cols = 1024;
using matrix = Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic>;



namespace {

void
naive_matrix_multiplication(const matrix& a, const matrix& b, matrix& c, int inicio, int final)
{
  for(int i = inicio ; i < final; ++i) {
    for(int j = inicio; j < final; ++j) {
      float sum = 0.0f;
      for(int k = inicio; k < final; ++k) {
        sum+=a(i,k)+b(k,j);
      }
      c(i,j)=sum;
    }
  }
}

}


int
main(int , const char *argv[])
{


  matrix a(rows_cols, rows_cols), b(rows_cols, rows_cols), c(rows_cols, rows_cols);

   std::random_device rd;
   std::mt19937 gen(rd());
   std::uniform_real_distribution<float> dis(-1.0f, 1.0f);

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

  auto threads = std::stoll(argv[1]);
  std::vector<std::thread> thread_vector;

  // divide the steps into threads
  auto steps_per_thread = rows_cols / threads;

//  auto save_times = [&partial_results, &ids_with_times](size_t begin, size_t end, size_t i) {
//      ids_with_times[i]=time_ms(naive_matrix_multiplication,
//                  partial_results, i, begin, end);
//  };

  thread_vector.reserve(threads);
  for(int i = 0; i < threads; ++i) {
      int begin = i * steps_per_thread;
      int end = begin + (steps_per_thread - 1);
      thread_vector.push_back(std::thread(naive_matrix_multiplication, std::ref(a), std::ref(b), std::ref(c), begin, end));
  }


  for(auto &t: thread_vector) {
      t.join();
  }

  // perform matrix multiplication
   //auto start = std::chrono::steady_clock::now();
   //naive_matrix_multiplication(a, b, c);
   //auto stop = std::chrono::steady_clock::now();
   //double ex_time = std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count();

   //std::cout << "The delay of multiplying two " << rows_cols << " x " << rows_cols
   //  << " matrices is: " << ex_time << "ms." << std::endl;
   //std::cout << "c(1,1) = " << c(1,1) << std::endl;

   return 0;
}

