#pragma once
#include <functional>
#include <chrono>

class Timer
{
public:
    using CallbackFn = std::function<void()>;
    void RunOnceAfter(std::chrono::milliseconds delay, const CallbackFn& callbackFn)
    {
        m_elapsed = std::chrono::milliseconds::zero();
        m_delay = delay;
        m_callbackFn = callbackFn;
    }

    void Update(std::chrono::milliseconds dt)
    {
        if(m_elapsed >= m_delay)
        {
            return;
        }

        m_elapsed += dt;
        if(m_elapsed >= m_delay)
        {
            if(nullptr != m_callbackFn)
            {
                m_callbackFn();
            }
        }
    }
private:
    std::chrono::milliseconds m_elapsed;
    std::chrono::milliseconds m_delay;
    CallbackFn m_callbackFn;
};

