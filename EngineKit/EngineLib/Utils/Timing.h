#ifndef E07DBA5E_5B51_4DC5_AD37_6ED76DC43AB2
#define E07DBA5E_5B51_4DC5_AD37_6ED76DC43AB2

#include <cstdint>
#include <queue>
#include <chrono>

namespace fts
{
using ClockType = std::chrono::high_resolution_clock;

class  Clock {
   public:
    Clock();

    float GetElapsedMS() const;

    // Restart the clock, and return elapsed millisecond.
    float Restart();

   private:
    std::chrono::time_point<ClockType> m_lastTicks;
};

class  FPSCounter {
   public:
    FPSCounter(uint8_t capacity);

    FPSCounter(const FPSCounter &) = delete;
    FPSCounter &operator=(const FPSCounter &) = delete;

    float GetFPS() const;
    float GetFrameTime() const;

    void Probe();

   private:
    Clock m_clock;
    std::deque<float> m_queue;
    uint8_t m_capacity;
};

} // namespace fts


#endif /* E07DBA5E_5B51_4DC5_AD37_6ED76DC43AB2 */
