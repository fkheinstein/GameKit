#include "Timing.h"

#include <numeric>
#include <chrono>


//https://github.com/heinsteinh/GameEngineECS/blob/5fb71e65dfbe56c6ffe378efb5f5312d014608e2/GameProjet/GameLib/Utility/olcTimer.h

namespace fts
{

    Clock::Clock() : m_lastTicks(ClockType::now()) {}


    void Clock::Reset()
    {
        m_lastTicks = std::chrono::high_resolution_clock::now();
    }

    float  Clock::Elapsed() const
    {
        return static_cast<float>(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - m_lastTicks).count()) * 0.000000001f;
    }

    float Clock::GetElapsedMS() const
    {
        return Elapsed() * 1000.0f;
        //return std::chrono::duration_cast<std::chrono::microseconds>(ClockType::now() - m_lastTicks).count() /  1000.f;
    }


    float Clock::Restart()
    {
        float elapsed = GetElapsedMS();
        m_lastTicks = ClockType::now();
        return elapsed;
    }

    FPSCounter::FPSCounter(uint8_t capacity) : m_capacity(capacity) {}

    void FPSCounter::Probe()
    {
        float time = static_cast<float>(m_clock.Restart());
        m_queue.push_back(time);
        if (m_queue.size() > m_capacity)
        {
            m_queue.pop_front();
        }
    }

    float FPSCounter::GetFPS() const { return 1000 / GetFrameTime(); }

    float FPSCounter::GetFrameTime() const
    {
        return std::accumulate(m_queue.begin(), m_queue.end(), 0.f) /
               m_queue.size();
    }
} // namespace fts
