#include <iostream>
#include <unordered_map>
#include <chrono>
#include <thread>

class CooldownSystem {
public:
    bool isAllowed(const std::string& key) {
        auto now = getCurrentTime();

        if (cooldowns.find(key) != cooldowns.end() && (now - cooldowns[key] < cooldownPeriod)) {
            return false;
        }

        cooldowns[key] = now;
        return true;
    }

    const long long cooldownPeriod = 3000;
private:
    std::unordered_map<std::string, long long> cooldowns;

    long long getCurrentTime() {
        return std::chrono::duration_cast<std::chrono::milliseconds>(
                   std::chrono::steady_clock::now().time_since_epoch())
            .count();
    }
};