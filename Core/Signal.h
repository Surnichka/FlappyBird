#pragma once
#include <map>
#include <vector>
#include <functional>

class Signal
{
public:
    using Slot = std::function<void()>;

    void Connect(std::string key, Slot slot);
    void Dispatch(std::string key);
private:
    std::map<std::string, std::vector<Slot>> m_slots;
};
Signal& GetSignal();
