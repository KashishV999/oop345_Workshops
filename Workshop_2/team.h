/*
Name: Kashish Verma
Id: 151579232
Email: kverma45@myseneca.ca
Date: 20 october 2024
*/

#ifndef SENECA_TEAM_H
#define SENECA_TEAM_H
#include "character.h"
namespace seneca {
	//Composition
	class Team {
		std::string m_name{};
		//an array of pointers to Character
		 Character** m_character{};
		size_t m_size{};
		size_t m_capacity=1;

	public:
		Team()=default;
		//Constructor
		Team(const char* name);
		void addMember(const  Character* c);
		void removeMember(const std::string& c);
		Character* operator[](size_t idx) const;
		void showMembers() const;
		
		//Rule of Five
		~Team();
		Team(const Team& other);
		Team& operator=(const Team& other);
		Team( Team&& other) noexcept;
		Team& operator=( Team&& other) noexcept;

	};
}

#endif