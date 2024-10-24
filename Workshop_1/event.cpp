/*
Name: Kashish Verma
Id: 151579232
Email: kverma45@myseneca.ca
Date: 29 September 2024
*/


#include <iostream>
#include <iomanip>
#include "event.h"
#include "settings.h"
using namespace std;
namespace seneca{
	Event::Event(const char* name, const std::chrono::nanoseconds& duration) {
		if(name)
		m_name = name;
		m_duration = duration;
	}

	ostream& operator<<(ostream& os, const Event& other) {
		static int counter = 0;
		counter++;
		int width{};
		
		os << setw(2) << right << counter << ":";
		os << setw(41) << right << other.m_name << " -> ";

		//custom field width and casting of duration based on unit of time
		if (g_settings.m_time_units == "seconds") {
			width = 2;

			const auto duration = std::chrono::duration_cast<std::chrono::seconds>(other.m_duration);
			os << setw(width) << right << duration.count() << " ";
		}
		else if (g_settings.m_time_units == "milliseconds") {
			width = 5;
			const auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(other.m_duration);
			os << setw(width) << right << duration.count() << " ";
		}
		else if (g_settings.m_time_units == "microseconds") {
			width = 8;
			const auto duration = std::chrono::duration_cast<std::chrono::microseconds>(other.m_duration);
			os << setw(width) << right << duration.count() << " ";
		}
		else if (g_settings.m_time_units == "nanoseconds") {
			width = 11;
			const auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(other.m_duration);
			os << setw(width) << right << duration.count() << " ";
		}

		
		os << g_settings.m_time_units;
		
		return os;

	}

}