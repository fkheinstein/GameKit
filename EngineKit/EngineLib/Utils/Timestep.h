#ifndef __TIMESTEP_H__
#define __TIMESTEP_H__

namespace fts
{
    class TimeStep
    {
    public:
        TimeStep(float time = 0.0f) : m_Time(time)
        {
        }

        operator float() const { return m_Time; }

        float GetSeconds() const { return m_Time; }
        float GetMilliseconds() const { return m_Time * 1000.0f; }
    private:
        float m_Time;
    };


    class Time
    {
    private:
        Time() = default;
        TimeStep _timestep;

    public:
        static TimeStep GetTimestep() { return _sInstance->_timestep; }
        static float GetTimeElapsed() { return _sInstance->_sTimeElapsed; }

    private:

        static void SetTimestep(TimeStep timestep) { _sInstance->_timestep = timestep; }
        static void SetTimeElapsed(float time) { _sTimeElapsed = time; }

    private:
        inline static Time* _sInstance;
        inline static float _sTimeElapsed;

        friend class Application;
    };
} // namespace fts

#endif // __TIMESTEP_H__