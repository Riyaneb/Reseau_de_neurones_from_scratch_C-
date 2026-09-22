#ifndef RESEAU_DE_NEURONES_FROM_SCRATCH_C_TIMER_HPP
#define RESEAU_DE_NEURONES_FROM_SCRATCH_C_TIMER_HPP

#include <chrono>

class Timer {
public:
    Timer() : instant(std::chrono::steady_clock::now()) {};
    void reset();
    double elapsed() const;
private:
    std::chrono::time_point<std::chrono::steady_clock> instant;
};

#endif //RESEAU_DE_NEURONES_FROM_SCRATCH_C_TIMER_HPP
