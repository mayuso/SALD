#ifndef _TimeManager_H
#define _TimeManager_H
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

        SALD_API double CalculateFrameRate(bool writeToConsole);
        SALD_API double GetTime();
        SALD_API void SleepThread(int ms);

        // This is the time slice that stores the total time in seconds that has elapsed since the last frame
        double DeltaTime = 0;

        // This is the current time in seconds
        double CurrentTime = 0;

    private:
        TimeManager(){};                             // Private so that it can  not be called
        TimeManager(TimeManager const &);            // copy constructor is private
        TimeManager &operator=(TimeManager const &); // assignment operator is private
    };
}

#endif