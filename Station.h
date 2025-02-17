/*
Name: Kashish Verma
email: kverma45@myseneca.ca
Student ID: 151579232
date: 1 December 2024

I declare that this submission is the result of my own work 
and I only copied the code that my professor provided to complete
my workshops and assignments. This submitted piece of work has not been
shared with any other student or 3rd party content provider.
*/


#ifndef SENECA_STATION_H
#define SENECA_STATION_H

#include <string>

namespace seneca {
	class Station
	{
		int m_id{};
		std::string m_name{}; //item name
		std::string m_desc{};
		size_t m_serNo{};//serial number to be assigned to an item
		size_t m_num; //number of items in stock

		//class variables, initialized outside of class
		static size_t m_widthField;
		static size_t id_generator;

	public:
		//reference to an unmodifiable std::string
		Station(const std::string& record);

		const std::string& getItemName() const;
		size_t getNextSerialNumber();
		size_t getQuantity() const;
		void updateQuantity();
		void display(std::ostream& os, bool full) const;
	};
}
#endif
