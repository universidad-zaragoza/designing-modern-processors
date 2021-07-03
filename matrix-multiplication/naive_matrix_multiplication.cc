#include <chrono>
#include <iostream>
#include <random>

#include <Eigen/Dense>

constexpr size_t rows_cols = 1024;
using matrix = Eigen::Matrix<float, rows_cols, rows_cols>;

namespace {

void
naive_matrix_multiplication(const matrix& a, const matrix& b, matrix&c)
{
  for(int i = 0 ; i < a.cols(); ++i) {
    for(int j = 0; j < b.rows(); ++j) {
      float sum = 0.0f;
      for(int k = 0; k < a.rows(); ++k) {
        sum+=a(i,k)+b(k,j);
      }
      c(i,j)=sum;
    }
  }
}

}

int
main(int , const char *[])
{

  matrix a, b, c;

   std::random_device rd;
   std::mt19937 gen(rd());
   std::uniform_real_distribution<float> dis(-1.0f, 1.0f);

  for(size_t i = 0; i < rows_cols; ++i) {
    for(size_t j = 0; j < rows_cols; ++j) {
      a(i, j) = dis(gen);
    }
  }

  // perform matrix multiplication
   auto start = std::chrono::steady_clock::now();
   naive_matrix_multiplication(a, b, c);
   auto stop = std::chrono::steady_clock::now();
   double ex_time = std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count();

   std::cout << "The delay of multiplying two " << rows_cols << " x " << rows_cols
     << " matrices is: " << ex_time << "ms." << std::endl;
   std::cout << "c(1,1) = " << c(1,1) << std::endl;
}




