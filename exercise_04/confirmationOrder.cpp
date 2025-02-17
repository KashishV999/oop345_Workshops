#include <iostream>
#include "confirmationOrder.h"
using namespace std;
namespace seneca{

	//Constructor
	ConfirmationOrder::ConfirmationOrder()
	{
		c_toys = new const Toy * [m_capacity];
	/*	for (size_t i = 0; i < m_size; i++) {
			c_toys[i] = nullptr;
		}*/


	}

	//Destructor
	ConfirmationOrder::~ConfirmationOrder() {

		//if (c_toys != nullptr) {
			delete[] c_toys;  // Safely delete the array
		//	c_toys = nullptr;  // Set the pointer to nullptr after deletion to avoid double free
		//}
	
	}


	//Copy Constructor
	ConfirmationOrder::ConfirmationOrder(const ConfirmationOrder& other)
	{
		*this = other;
	}

	//Copy Assignment
	ConfirmationOrder& ConfirmationOrder::operator=(const ConfirmationOrder& other)
	{
		//check self assignment
		if (this != &other) {
			//clean-up

			delete[] c_toys;
			
			//shallow copy
			m_size = other.m_size;
			m_capacity = other.m_capacity;

			//deep copy
			c_toys = new const Toy * [m_size];

			//TODO DO NOT DO THISSSSSSSSSSSSSSSSS
			//c_toys = other.c_toys;  // both the current object and other are sharing the same memory
			//If one object modifies or deletes the array, the other object will have an invalid pointer,
			//  which can lead to crashes or undefined behavior.
			for (size_t i = 0; i < m_size; ++i) {
				c_toys[i] = other.c_toys[i]; // Copy pointers 
			}

			
		}

		return *this;
	}

	//Move Constructor
	ConfirmationOrder::ConfirmationOrder(ConfirmationOrder&& other) noexcept
	{
		*this = move(other);
	}

	//Move Assignment
	ConfirmationOrder& ConfirmationOrder::operator=(ConfirmationOrder&& other) noexcept
	{
		//self-assignment
		if (this != &other) 
		{

		
			//clean-up
			delete[] c_toys;
			//c_toys = nullptr;

			//shallow copy
			m_size = other.m_size;
			m_capacity = other.m_capacity;

			//copy address
			c_toys = other.c_toys;

			other.c_toys = nullptr;
			other.m_size = 0;
			other.m_capacity = 0;

		}
		return *this;
	}

	ConfirmationOrder& ConfirmationOrder::operator+=(const Toy& toy)
	{
		bool isPresent = false;
		//int count = 0;
		for (size_t i = 0; i < m_size && !isPresent; ++i) {  //!isPresent==false
			if (c_toys[i] == &toy) {
				isPresent = true;
				//count += 1;
				//break;
			}
		}

		if (!isPresent) {  //!isPresent==false
			
			if (m_size == m_capacity) {
				size_t newCapacity = 2 * m_capacity;
				const Toy** tempToy{};
				tempToy = new const Toy * [newCapacity];

				for (size_t i = 0; i < m_size; ++i) {
					tempToy[i] = c_toys[i];
				}

				delete[] c_toys;
				


				c_toys = tempToy;
				m_capacity = newCapacity;
			}

			c_toys[m_size] = &toy;
			m_size++;


		}
		return *this;

	}

	ConfirmationOrder& ConfirmationOrder::operator-=(const Toy& toy)
	{
		size_t index{};
		bool isFound = false;
		for (size_t i = 0; i < m_size && !isFound; ++i) {
			if (c_toys[i] == &toy) {
				
				index = i;
				isFound = true;
			}
		}

		//shift all elements to left after that index
		if (isFound) 
		{
			for (size_t i = index; i < m_size-1; ++i) {
				c_toys[i] = c_toys[i + 1];
			}
			c_toys[m_size - 1] = nullptr;
			--m_size;

		}

		return *this;
	}




	std::ostream& operator<<(std::ostream& os, const ConfirmationOrder& other)
	{
		os << "--------------------------" << endl;
		os << "Confirmations to Send" ;
		os << " (" << other.m_size << " toys)"<<endl;
		os << "--------------------------" << endl;

		if (other.m_size==0) {
			os << "There are no confirmations to send!" << endl;
		}
		else {
			for (size_t i = 0; i < other.m_size; ++i) {
				os << *other.c_toys[i];
			}
		}
		os << "--------------------------" << endl;
		return os;
	}

}