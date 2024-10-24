/*
Name: Kashish Verma
Id: 151579232
Email: kverma45@myseneca.ca
Date: 29 September 2024
*/

#ifndef SENECA_SETTINGS_H
#define SENECA_SETTINGS_H
#include <string>
namespace seneca {

	struct Settings {
		bool m_show_all = false;
		bool m_verbose = false;
		std::string m_time_units = "nanoseconds";
	};

	extern Settings g_settings; //global variable
}

#endif
