#include <chrono>
#include <iostream>
#include <random>

constexpr size_t rows_cols = 1024;
using matrix = Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic>;

namespace {

void
eigen_matrix_multiplication(const matrix& a, const matrix& b, matrix&c)
{
  c=a*b;
}

} // namespace anonymous

int
main(int , const char *[])
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

  // perform matrix multiplication
  auto start = std::chrono::steady_clock::now();
  eigen_matrix_multiplication(a, b, c);
  auto stop = std::chrono::steady_clock::now();
  double ex_time = std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count();

  std::cout << "The delay of multiplying two " << rows_cols << " x " << rows_cols
     << " matrices is: " << ex_time << "ms." << std::endl;
  std::cout << "c(1,1) = " << c(1,1) << std::endl;

  return 0;
}

