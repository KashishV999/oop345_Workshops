#include <iostream>
#include <fstream>
#include <string>
#include "spamFilterPlugin.h"

namespace seneca {

	int SpamFilterPlugin::m_cnt = 0;


	SpamFilterPlugin::SpamFilterPlugin(const char* filename)
	{
		std::ifstream file(filename);
		if (file.is_open() == false) {
			const char* msgFile = "File cannot be opened";
			throw msgFile;
		}
		for (auto i = 0; i < CAPACITY_SP; ++i) {
			std::getline(file, spam[i], '\n');
		}
	}

	void SpamFilterPlugin::operator()(Message& msg)
	{
		//for (auto i = 0; i < 3; ++i) {
		for(std::string& spamW: spam){
			/*
			std::string::find can be used to check if a substring exists within a string
			 It returns the starting position of the substring if it is found,
			 and std::string::npos if it is not found.
			*/

			if (msg.m_subject.find(spamW) != std::string::npos && spamW!="") {
				msg.m_subject = "[SPAM] " + msg.m_subject;

				++m_cnt;
			}
		}
	}

	void SpamFilterPlugin::showStats() const
	{
		std::cout << "[Spam Filter Plugin] Identified " << m_cnt << " spam messages." << "\n";
	}



}

