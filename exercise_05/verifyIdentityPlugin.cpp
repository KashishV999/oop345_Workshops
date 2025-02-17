#include <iostream>
#include <fstream>
#include <string>
#include "verifyIdentityPlugin.h"

namespace seneca {
	VerifyIdentityPlugin::VerifyIdentityPlugin(const char* filename)
	{
		std::ifstream file(filename);
		if (file.is_open() == false) {
			const char* msgFile = "File cannot be opened";
			throw msgFile;
		}

		for (auto i = 0; i < 3; ++i) {
			std::getline(file, trusted[i], '\n');
		}
	}

	void VerifyIdentityPlugin::operator()(Message& msg)
	{
		for (auto i = 0; i < 3; ++i)
		{
			if (msg.m_fromAddress == trusted[i]) {
				msg.m_subject = "[TRUSTED] " + msg.m_subject;
				break;

			}
		}
	}

	void VerifyIdentityPlugin::showStats() const
	{
		std::cout << "[Identity Checker Plugin] can validate identity for ";
		for (auto i = 0; i < CAPACITY_VIP && trusted[i]!=""; ++i) {
			std::cout << trusted[i];
			if (i < 2) {
				std::cout << ", ";
			}
			else if (i == 2) {
				std::cout << "\n";
			}
		}
	}

}
