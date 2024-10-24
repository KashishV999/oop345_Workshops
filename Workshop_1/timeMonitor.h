/*
Name: Kashish Verma
Id: 151579232
Email: kverma45@myseneca.ca
Date: 29 September 2024
*/


#ifndef  SENECA_TIMEMONITOR_H
#define  SENECA_TIMEMONITOR_H
#include <chrono>
#include "event.h"
namespace seneca {

	class TimeMonitor {

		std::string m_name{};
		std::chrono::steady_clock::time_point m_startTime{};
		std::chrono::steady_clock::time_point m_endTime{};

	public:
		void startEvent(const char* name);
		Event stopEvent();

	};

}

#endif
