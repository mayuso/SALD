#pragma once
#include "Sald/Core/Core.h"

namespace Sald
{
    class TimeManager
    {
    public:
        static TimeManager &Instance()
        {
            static TimeManager instance;

            return instance;
        }

        SALD_API double CalculateFrameRate(bool writeToConsole = false);
        // Milliseconds on a monotonic clock
        SALD_API double GetTime();
        SALD_API void SleepThread(int ms);

        // This is the time slice that stores the total time in milliseconds that has elapsed since the last frame
        double DeltaTime = 0;

        // This is the current time in milliseconds
        double CurrentTime = 0;

    private:
        TimeManager() = default; // Private: use Instance()
        TimeManager(TimeManager const &) = delete;
        TimeManager &operator=(TimeManager const &) = delete;
    };
}
