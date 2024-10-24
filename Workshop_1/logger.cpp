/*
Name: Kashish Verma
Id: 151579232
Email: kverma45@myseneca.ca
Date: 29 September 2024
*/


#include <iostream>
#include "logger.h"
namespace seneca {
	Logger::Logger()
	{
		m_events = new Event[m_capacity];
	}

	Logger::~Logger() {
		delete[] m_events;
	}

	Logger::Logger(Logger&& other) noexcept {
		*this = std::move(other);
	}

	Logger& Logger:: operator=(Logger&& other) noexcept {
		//self assignment
		if (this != &other) {
			//cleanup
			delete[] m_events;

				//shallow copy nothing
			m_size = other.m_size;
			m_capacity = other.m_capacity;
				//copy address
			m_events = other.m_events;

			//set existing resource to empty
			other.m_events = nullptr;
			other.m_size = 0;
			
		}
		return *this;
	}

	//dynamic resizing
	void Logger::addEvent(const Event& event)
	{
		if (m_size == m_capacity) {
			int newCapacity = 2 * m_capacity;
			Event* temp{};
			temp = new Event[newCapacity];

			//old to new
			for (size_t i = 0; i < m_size; i++) {
				temp[i] = m_events[i];
			}

			delete[] m_events;

			m_events = temp;
			m_capacity = newCapacity;
		}

		m_events[m_size] = event;
		m_size++;

	}



	std::ostream& operator<<(std::ostream& os, const Logger& other)
	{
		for (size_t i = 0; i < other.m_size; i++) {
			std::cout << other.m_events[i] << std::endl;
		}
		return os;
	}

}
