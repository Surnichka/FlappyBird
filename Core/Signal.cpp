#include "Signal.h"

void Signal::Connect(std::string key, Signal::Slot slot)
{
    m_slots[key].push_back(slot);
}

void Signal::Dispatch(std::string key)
{
    auto it = m_slots.find(key);
    if (it != m_slots.end())
    {
        for (auto& slot : it->second)
        {
            slot();
        }
    }
}

Signal &GetSignal()
{
    static Signal signal;
    return signal;
}
