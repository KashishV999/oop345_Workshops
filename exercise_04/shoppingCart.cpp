#include <iostream>
#include "shoppingCart.h"
using namespace std;


namespace seneca
{

	ShoppingCart::ShoppingCart(const std::string& name, int age, const Toy* toys[], size_t count) {
		m_name = name;
		m_age = age;
		m_count = count;

		m_toys = new const Toy * [m_count];

		for (size_t i = 0; i < m_count; ++i) {
			m_toys[i] = new Toy(*toys[i]);
		}
	}

	//TODO
	ostream& operator<<(ostream& os, const ShoppingCart& other) {

		static int CALL_CNT = 0;

		os << "--------------------------" << endl;
		os << "Order " << CALL_CNT+1 << ": ";


		if (other.m_toys == nullptr) {
			os << "This shopping cart is invalid." << endl;
			os << "--------------------------" << endl;
		}

		else{
			os << "Shopping for "<<other.m_name<<" " <<other.m_age<<" years old ("<< other.m_count<<" toys)" << endl;
			os << "--------------------------" << endl;
			if (other.m_count) {
				int cnt = other.m_count;
				for (size_t i = 0; i < cnt ; ++i) {

					
						os << (*other.m_toys[i]);
					
				}
			}

			else {
				os << "--------------------------" << endl;
				os << "Empty shopping cart!" << endl;
				
			}

			os << "--------------------------" << endl;
			++CALL_CNT;
			return os;
		}

	




		CALL_CNT++;


		return os;
	}

	//Destructor
	ShoppingCart::~ShoppingCart() {
		for (size_t i = 0; i < m_count; ++i) {
			delete m_toys[i];
		}

		delete[] m_toys;
	}

	//Copy Constructor
	ShoppingCart::ShoppingCart(const ShoppingCart& other) {
		*this = other;
	}

	//Copy Assignment
	ShoppingCart& ShoppingCart:: operator=(const ShoppingCart& other) {
		//self-assignment
		if (this != &other) {
			//clean-up
			for (size_t i = 0; i < m_count; ++i) {
				delete m_toys[i];
			}

			delete[] m_toys;

			//shallow copy
			m_name = other.m_name;
			m_age = other.m_age;
			m_count = other.m_count;

			//deep copy

			m_toys = new const Toy * [m_count];

			for (size_t i = 0; i < m_count; ++i) {
				m_toys[i] = new Toy(*other.m_toys[i]);
			}

		}


		return *this;
	}



	//Move constructor
	ShoppingCart::ShoppingCart(ShoppingCart&& other) noexcept {
		*this = move(other);
	}

	//move assignment
	ShoppingCart& ShoppingCart::operator=(ShoppingCart&& other) noexcept {

		//self-assignment
		if (this != &other) {
			//clean-up
			for (size_t i = 0; i < m_count; ++i) {
				delete m_toys[i];
			}

			delete[] m_toys;

			//shallow copy
			m_name = other.m_name;
			m_age = other.m_age;
			m_count = other.m_count;

			//CORRECT WAY:
			//Transfer the whole pointer to the array without copying individual elements.
			//copy address
			m_toys = other.m_toys;
			//Set other.m_toys to nullptr to indicate that other no longer owns any resources.
			other.m_toys = nullptr;

			
			
			
			//No need to do this
			////because the whole pointer to the array has already been transferred.
			/*for (size_t i = 0; i < m_count; i++) {
				m_toys[i] = other.m_toys[i];
			}*/
			

			//By nullifying individual elements in other.m_toys[i], 
			// you're also nullifying the pointers in m_toys[i] because they are now pointing to the same array.
		/*	for (size_t i = 0; i < m_count; i++) {
				other.m_toys[i]=nullptr;
			}*/
			
			other.m_count = 0;
			other.m_name = "";
			other.m_age = 0;



			return *this;
		}




	}
}