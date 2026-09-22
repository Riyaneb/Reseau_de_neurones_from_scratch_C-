#include "utils/Timer.hpp"

void Timer::reset() {
    instant = std::chrono::steady_clock::now();
}

double Timer::elapsed() const {
    std::chrono::time_point<std::chrono::steady_clock> end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - instant;
    return elapsed_seconds.count();
}
