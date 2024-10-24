/*
Name: Kashish Verma
Id: 151579232
Email: kverma45@myseneca.ca
Date: 29 September 2024
*/

#include "timeMonitor.h"

namespace seneca {

	void seneca::TimeMonitor::startEvent(const char* name)
	{
		m_startTime = std::chrono::steady_clock::now();
		m_name = name;
	}

	Event seneca::TimeMonitor::stopEvent()
	{
		
		m_endTime = std::chrono::steady_clock::now();
		std::chrono::nanoseconds duration = m_endTime - m_startTime;
		Event event1(m_name.c_str(), duration);
		return event1;
	}


}
