#include "Sald/Utils/TimeManager.h"
#include "saldpch.h"

#include "Sald/Core/Log.h"

double Sald::TimeManager::CalculateFrameRate(bool writeToConsole) {
  static double frameCount = 0.0f;
  static double timeSinceLastFPSRefresh =
      GetTime(); // This will hold the time per second to test against
  static double timeSinceLastFrame =
      GetTime(); // This will hold the time from the last frame
  static double currentFPS = 0.0f; // This stores the current frames per second

  CurrentTime = GetTime();
  DeltaTime = CurrentTime - timeSinceLastFrame;
  timeSinceLastFrame = CurrentTime;

  ++frameCount;

  if (CurrentTime - timeSinceLastFPSRefresh >=
      1000.0f) // If last FPS refresh was 1 sec or longer ago
  {
    // Multiply by 1000 to convert milliseconds to seconds
    currentFPS = frameCount * 1000 / (CurrentTime - timeSinceLastFPSRefresh);

    if (writeToConsole)
      SALD_CORE_LOG("Current Frames Per Second: {0} ---- DeltaTime: {1}",
                    currentFPS, DeltaTime);

    frameCount = 0;
    timeSinceLastFPSRefresh = CurrentTime;
  }
  return currentFPS;
}

// This returns the current time in milliseconds. steady_clock, not
// system_clock: the wall clock can jump (NTP, DST, manual changes), which
// would produce negative or huge deltas
double Sald::TimeManager::GetTime() {
  auto sinceEpoch = std::chrono::steady_clock::now().time_since_epoch();
  return std::chrono::duration<double, std::milli>(sinceEpoch).count();
}

// This pauses the current thread for an amount of time in milliseconds
void Sald::TimeManager::SleepThread(int ms) {
  std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}