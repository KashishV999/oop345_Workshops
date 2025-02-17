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

#include <string>
#include "Utilities.h"
using namespace std;
namespace seneca {

	//class variable instantiate
	char Utilities::m_delimiter = '\0';

	//class member functions
	void Utilities::setDelimiter(char newDelimiter) {
		m_delimiter = newDelimiter;
	}

	char Utilities::getDelimiter() {
		return m_delimiter;
	}


	void Utilities::setFieldWidth(size_t newWidth) {
		m_widthField = newWidth;
	}

	size_t Utilities::getFieldWidth() const {
		return m_widthField;
	}

	void Utilities::trim(std::string& str) {
		size_t i = 0u;

		for (i = 0u; i < str.length() && str[i] == ' '; ++i);
		str = str.substr(i);

		for (i = str.length(); i > 0u && str[i - 1] == ' '; --i);
		str = str.substr(0, i);

	}




	std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {

		more = false;
		string token{};

		if (next_pos < str.length() && str[next_pos] == m_delimiter) {
			throw "Delimiter found";
		}

		else {

			size_t posE = str.find(m_delimiter, next_pos);

			if (posE == string::npos) {
				posE = 0u;
				if (next_pos < str.length()) {
					posE = str.length();

				}
				else {
					return "";
				}
			}

			token = str.substr(next_pos, posE - next_pos);

			trim(token);

			if (token != "") {
				next_pos = posE + 1;

				if (next_pos > str.length()) {
					more = false;
				}
				else {
					more = true;
				}
				if (getFieldWidth() < token.length()) {
					setFieldWidth(token.length());
				}
				return token;
			}

		}
		return token;

	}

}

