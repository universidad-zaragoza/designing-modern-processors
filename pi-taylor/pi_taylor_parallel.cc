#include <chrono>
#include <iomanip>
#include <iostream>
#include <limits>
#include <numeric>
#include <string>
#include <thread>
#include <utility>
#include <vector>

using my_float = long double;
using tid_time = std::pair<std::thread::id, double>;

template<typename F, typename... Args>
tid_time
time_ms(F f, Args&&... args)
{
    auto start = std::chrono::steady_clock::now();
    f(std::forward<Args>(args)...);
    auto stop = std::chrono::steady_clock::now();

    auto tid = std::this_thread::get_id();
    double ex_time = std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count();
    return std::make_pair(tid, ex_time);
}

void
pi_taylor_chunk(std::vector<my_float> &output,
        size_t thread_id, size_t start_step, size_t stop_step)
{

    my_float acc = 0.0f;
    int sign = start_step & 0x1 ? -1 : 1;

    for (size_t i = start_step; i < stop_step; ++i) {
        my_float divider = 2.0f * i + 1.0f;
        acc += static_cast<my_float>(sign) / divider;
       sign = -sign;
    }
    output[thread_id] = acc;
}

std::pair<size_t, size_t>
usage(int argc, const char *argv[]) {
    // read the number of steps from the command line
    if (argc != 3) {
        std::cerr << "Invalid syntax: pi_taylor <steps> <threads>" << std::endl;
        exit(1);
    }

    size_t steps = std::stoll(argv[1]);
    size_t threads = std::stoll(argv[2]);

    if (steps < threads ){
        std::cerr << "The number of steps should be larger than the number of threads" << std::endl;
        exit(1);

    }
    return std::make_pair(steps, threads);
}

int
main(int argc, const char *argv[])
{

    auto ret_pair = usage(argc, argv);
    auto steps = ret_pair.first;
    auto threads = ret_pair.second;

    std::vector<std::thread> thread_vector;
    std::vector<my_float> partial_results(threads);
    std::vector<tid_time> ids_with_times(threads);

    // divide the steps into threads
    auto steps_per_thread = steps / threads;

    auto save_times = [&partial_results, &ids_with_times](size_t begin, size_t end, size_t i) {
        ids_with_times[i]=time_ms(pi_taylor_chunk,
                    partial_results, i, begin, end);
    };

    thread_vector.reserve(threads);
    for(size_t i = 0; i < threads; ++i) {
        auto begin = i * steps_per_thread;
        auto end = std::min(begin + steps_per_thread, steps);
        thread_vector.push_back(std::thread(save_times, begin, end, i));
    }

    for(auto &t: thread_vector) {
        t.join();
    }

    my_float pi = 4.0L * std::accumulate(partial_results.begin(),
        partial_results.end(), 0.0L);

    std::cout << "For " << steps << " steps, pi value: "
        << std::setprecision(std::numeric_limits<long double>::digits10 + 1)
        << pi << std::endl;

    for(const auto& e: ids_with_times) {
        std::cout << "thread id: " << e.first << ", time: " << e.second << "ms" << std::endl;
    }
}

