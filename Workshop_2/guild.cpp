/*
Name: Kashish Verma
Id: 151579232
Email: kverma45@myseneca.ca
Date: 20 october 2024
*/


#include <iostream>
#include "guild.h"
using namespace std;

namespace seneca {
	Guild::Guild(const char* name) {
		m_name = name;
		m_character = new Character * [m_capacity];
	}

	//Rule of five
	//Destructor
	Guild::~Guild() {
		delete[] m_character;
	}

	//Copy Constructor
	Guild::Guild(const Guild& other) {
		*this = other;
	}

	//Move Constructor
	Guild::Guild(Guild&& other) noexcept
	{
		*this = move(other);
	}

	//Copy Assignment
	//Copy Assignment
	Guild& Guild:: operator=(const Guild& other) {
		//check self-assignment
		if (this != &other) {
			//clean-up
			delete[] m_character;

			//shallow copy
			m_name = other.m_name;
			m_size = other.m_size;
			m_capacity = other.m_capacity;

			//deep copy
			m_character = new Character * [m_size];

			for (size_t i = 0; i < m_size; ++i) {
				m_character[i] = other.m_character[i];
			}

		}

		return *this;
	}


	//Move assignment
	Guild& Guild::operator=(Guild&& other) noexcept {
		//check self-assignment
		if (this != &other) {
			//clean-up
			delete[] m_character;

			//shallow copy
			m_name = other.m_name;
			m_size = other.m_size;
			m_capacity = other.m_capacity;

			//copy address
			m_character = other.m_character;

			//empty other
			other.m_character = nullptr;
			other.m_name = "";
			other.m_size = 0;
			other.m_capacity = 0;
		}
		return *this;
	}

	Character* Guild:: operator[](size_t idx) const {
		if (idx < m_size) {
			return m_character[idx];

		}
		return nullptr;
	}


	void Guild::showMembers() const {

		if (m_name != "") {
			cout << "[Guild] " << m_name << endl;
			for (size_t i = 0; i < m_size; ++i) {
				cout << "    " << i + 1 << ": " << (*m_character[i]) << endl;
			}
		}
		else {
			cout << "No guild." << endl;
		}
	}


	void Guild::addMember(Character* c) {
		bool isFound = false;
		for (size_t i = 0; i < m_size && !isFound; ++i) {
			if (m_character[i] == c) {
				isFound = true;
			}
		}

		if (!isFound)
		{
			if (m_size == m_capacity) {
				size_t newCapacity = 2 * m_capacity;
				Character** newTemp{};
				newTemp = new Character * [newCapacity];

				//copy
				for (size_t i = 0; i < m_size; ++i) {
					newTemp[i] = m_character[i];
				}

				//delete
				delete[] m_character;

				m_character = newTemp;
				m_capacity = newCapacity;



			}

			m_character[m_size] = c;
			++m_size;

			int healthMax = c->getHealthMax();
			c->setHealthMax(healthMax + 300);
		}
	}



	void Guild::removeMember(const std::string& c)
	{
		bool isFound = false;
		size_t index{};
		for (size_t i = 0; i < m_size && !isFound; ++i) {
			if (m_character[i]->getName() == c) {
				isFound = true;
				index = i;
			}
		}

		if (isFound) {

			int healthMax = m_character[index]->getHealthMax();
			m_character[index]->setHealthMax(healthMax - 300);


			for (size_t i = index; i < m_size - 1; ++i) {
				m_character[i] = m_character[i + 1];
			}

			m_character[m_size - 1] = nullptr;
			--m_size;
		}

	}

}

