#include "TimeManager.h"

double Sald::TimeManager::CalculateFrameRate(bool writeToConsole = false)
{
	static double frameCount = 0.0f;
	static double timeSinceLastFPSRefresh = GetTime(); // This will hold the time per second to test against
	static double timeSinceLastFrame = GetTime();	   // This will hold the time from the last frame
	static double currentFPS = 0.0f;				   // This stores the current frames per second

	CurrentTime = GetTime();
	DeltaTime = CurrentTime - timeSinceLastFrame;
	timeSinceLastFrame = CurrentTime;

	++frameCount;

	if (CurrentTime - timeSinceLastFPSRefresh >= 1000.0f) // If last FPS refresh was 1 sec or longer ago
	{
		// Multiply by 1000 to convert milliseconds to seconds
		currentFPS = frameCount * 1000 / (CurrentTime - timeSinceLastFPSRefresh);

		if (writeToConsole)
			fprintf(stdout, "Current Frames Per Second: %f ---- DeltaTime: %f\n", currentFPS, DeltaTime);

		frameCount = 0;
		timeSinceLastFPSRefresh = CurrentTime;
	}
	return currentFPS;
}

// This returns the current time in milliseconds (uses C++ 11 system_clock)
double Sald::TimeManager::GetTime()
{
	auto beginningOfTime = std::chrono::system_clock::now().time_since_epoch();
	auto ms = duration_cast<std::chrono::milliseconds>(beginningOfTime).count();
	return ms;
}

// This pauses the current thread for an amount of time in milliseconds
void Sald::TimeManager::SleepThread(int ms)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}