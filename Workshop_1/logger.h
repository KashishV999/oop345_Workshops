/*
	Name: Kashish Verma
	Student ID: 151579232
	Email: kverma45@myseneca.ca
	Date of Completion: 27 September, 2024
*/
/*
Name: Kashish Verma
Id: 151579232
Email: kverma45@myseneca.ca
Date: 29 September 2024
*/


#ifndef SENECA_LOGGER_H
#define SENECA_LOGGER_H
#include "event.h"
namespace seneca {
	class Logger {
		Event* m_events{};	//dynamic allocated memory
		size_t m_size{};
		size_t m_capacity=1;
	public:
		Logger();

		//Rule of 5
		~Logger(); //DESTRUCTOR
		Logger(const Logger& other) = delete; // copy constructor
		Logger& operator=(const Logger& other) = delete; //Copy assignment

		Logger(Logger&& other) noexcept; //move constructor
		Logger& operator=(Logger&& other) noexcept; //move assignment
		

		void addEvent(const Event& event); 

		friend std::ostream& operator<<(std::ostream& os, const Logger& other);
	};
}

#endif
