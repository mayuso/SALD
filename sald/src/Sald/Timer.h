#pragma once
#include "Sald/sald_api.h"

/*
------------------------ HOW TO USE: ----------------------------
{
	Sald::Timer timer;
	// CODE TO TIME HERE, PRINTS TO TERMINAL AUTOMATICALLY
}
*/

#include <chrono>

namespace Sald
{
	class Timer
	{
	public:
		SALD_API Timer();
		SALD_API ~Timer();

	private:
		void Stop();
		std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;
	};

}
