/*
Name: Kashish Verma
Id: 151579232
Email: kverma45@myseneca.ca
Date: 20 october 2024
*/


#include <iostream>
#include "team.h"
#include "character.h"
using namespace std;

namespace seneca {

	//Constructor
	Team::Team(const char* name) {
		m_name = name;

		m_character = new  Character * [m_capacity];
	}

	//Rule of Five
	//DESTRUCTOR
	Team::~Team() {
		for (size_t i = 0; i < m_size; i++) {
			delete m_character[i];
		}

		delete[] m_character;
	}

	//COPY CONSTRUCTOR
	Team::Team(const Team& other) {
		*this = other;
	}

	//Copy Assignment
	Team& Team::operator=(const Team& other) {
		//check self-assignment
		if (this != &other)
		{
			//cleanup
			for (size_t i = 0; i < m_size; i++) {
				delete m_character[i];
			}

			delete[] m_character;

			//shallow copy
			m_name = other.m_name;
			m_size = other.m_size;
			m_capacity = other.m_capacity;

			//deep copy
			m_character = new  Character * [m_size];
			for (size_t i = 0; i < m_size; ++i) {
				m_character[i] = other.m_character[i]->clone();
			}
		}

		return *this;
	}

	//Move constructor
	Team::Team( Team&& other) noexcept {
		*this = move(other);
	}
	
	//Move Assignment
	Team& Team::operator=( Team&& other) noexcept{
		//check self-assignmnet
		if (this != &other) {
			//cleanup
			for (size_t i = 0; i < m_size; i++) {
				delete m_character[i];
			}

			delete[] m_character;

			//shallow copy
			m_name = other.m_name;
			m_size = other.m_size;
			m_capacity = other.m_capacity;

			//copy address
			m_character = other.m_character;

			other.m_character = nullptr;
			other.m_name = "";
			other.m_size = 0;
			other.m_capacity = 0;

		}
		return *this;
	}


	void Team::addMember(const  Character* c) {

		//check whether to add or not?
		bool isPresent = false;
		for (size_t i = 0; i < m_size && !isPresent; ++i) { //isPresent==false
			if (m_character[i]->getName() == c->getName())
				isPresent = true;
		}

		if (!isPresent) 
		{
			if (m_size == m_capacity)
			{
				size_t newCapacity = 2 * m_capacity;
				 Character** newTemp{};
				newTemp = new Character * [newCapacity];

				//copy address old to new 
				for (size_t i = 0; i < m_size; ++i) {
					newTemp[i] = m_character[i];
				}
				delete[] m_character;

				m_character = newTemp;
				m_capacity = newCapacity;
			}

			m_character[m_size] = c->clone();
			++m_size;
		}
	}


	void Team::removeMember(const std::string& c) {

		size_t index{};
		bool isFound = false;

		for (size_t i = 0; i < m_size && !isFound; ++i) {
			if (m_character[i]->getName() == c) {
				index = i;
				isFound = true;
			}
		}

		if (isFound) {
			delete m_character[index];
			for (size_t i = index; i < m_size - 1; ++i) {
				m_character[i] = m_character[i + 1];
			}

			m_character[m_size - 1] = nullptr;
			--m_size;

		}


	}


	Character* Team:: operator[](size_t idx) const {
		if (idx < m_size) {
			 return m_character[idx];
			 
		}
		return nullptr;
	}


	void Team::showMembers() const {
		
		if (m_name!="") {
			cout << "[Team] " << m_name << endl;
			for (size_t i = 0; i < m_size; ++i) {
				cout << "    "<< i + 1 << ": " << (*m_character[i]) << endl;
			}
		}
		else {
			cout << "No team." << endl;
		}
	}

}