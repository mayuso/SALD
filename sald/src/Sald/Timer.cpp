#include "saldpch.h"
#include "Timer.h"

#include <stdio.h>

Sald::Timer::Timer()
{
	m_StartTimepoint = std::chrono::high_resolution_clock::now();
}
Sald::Timer::~Timer()
{
	Stop();
}
void Sald::Timer::Stop()
{
	auto endTimepoint = std::chrono::high_resolution_clock::now();

	auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
	auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

	auto duration = end - start;

	printf("%lld μs\n", duration);
}
