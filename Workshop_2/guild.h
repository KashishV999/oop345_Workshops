/*
Name: Kashish Verma
Id: 151579232
Email: kverma45@myseneca.ca
Date: 20 october 2024
*/


#ifndef SENECA_GUILD_H
#define SENECA_GUILD_H
#include <string>
#include "character.h"
namespace seneca {
	//aggregation
	class Guild {
		std::string m_name{};
		//array of pointers to Character.
		Character** m_character{};
		size_t m_size{};
		size_t m_capacity = 1;

	public:
		Guild() = default;
		Guild(const char* name);
		void addMember(Character* c);
		void removeMember(const std::string& c);
		Character* operator[](size_t idx) const;
		void showMembers() const;

		//Rule of Five
		~Guild();
		Guild(const Guild& other);
		Guild& operator=(const Guild& other);
		Guild(Guild&& other) noexcept;
		Guild& operator=(Guild&& other) noexcept;
			
	};
}

#endif