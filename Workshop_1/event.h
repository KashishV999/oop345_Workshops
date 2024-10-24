/*
Name: Kashish Verma
Id: 151579232
Email: kverma45@myseneca.ca
Date: 29 September 2024
*/


#ifndef SENECA_EVENT_H
#define SENECA_EVENT_H
#include <string>
#include <chrono>
namespace seneca {
	class Event {
		std::string m_name{};		//Name of event
		std::chrono::nanoseconds m_duration{}; // Duration of event

	public:
		Event() = default; //constructor
		Event(const char* name, const std::chrono::nanoseconds& duration);  //Parameter Constructor
		friend std::ostream&  operator<<(std::ostream& os, const Event& other);
	};
}

#endif
