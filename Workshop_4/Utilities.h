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


/*This module helps in parsing of input file*/

#ifndef SENECA_UTILITIES_H
#define SENECA_UTILITIES_H

#include <string>
namespace seneca {
	class Utilities
	{
		int m_widthField=1;	//instance variable
		static char m_delimiter;//class variable , initialize separately outside of class

	public:
		void setFieldWidth(size_t newWidth);
		size_t getFieldWidth() const;
		std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
		static void setDelimiter(char newDelimiter);
		static char getDelimiter();
		//trim
		void trim(std::string& str);
	};


}

#endif

