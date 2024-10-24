#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <cstring>
#include<iomanip>
#include "FoodOrder.h"
using namespace std;
namespace seneca {
	double g_taxrate = 0.0;
	double g_dailydiscount = 0.0;

	//Rule of Three Implementation
	FoodOrder::~FoodOrder() {
		delete[] m_description;
		m_description = nullptr;
	}

	FoodOrder::FoodOrder(const FoodOrder& other) {
		*this = other;
			
		
		
	}

	FoodOrder& FoodOrder:: operator=(const FoodOrder& other) {
		//self assignment
		if (this != &other )
		{
			
			//cleanup
			delete[] m_description;
			
			//shallow copying
			m_price = other.m_price;
			m_special = other.m_special;
			strcpy(m_name, other.m_name);

			//deep copy
			if (other.m_description) {
				m_description = new char[strlen(other.m_description) + 1];
				strcpy(m_description, other.m_description);
			}
			else {
				m_description = nullptr;
			}

			

		}
		return *this;
	}



	istream& FoodOrder::read(istream& in) {
		if (in) {
			
			string name;
			string description;
			char special{};
			
				getline(in, name, ',');
				getline(in, description, ',');

				// Read the integer
				in >> m_price;

				// Ignore the comma after the price
				in.ignore();

				in >> special;
				in.ignore();
				
				//store
				strncpy(m_name, name.c_str(), 10);
				m_name[9] = '\0';
				//will not puy not null terminator
				
				m_description = new char[description.length() + 1];
				strcpy(m_description, description.c_str());

				if (special == 'Y') {
					m_special = true;
				}
				else if (special == 'N') {
					m_special = false;
				}



		}

		return in;
	}



	void FoodOrder:: display()const {
		static int counter = 0;
		if (m_name[0]!='\0') {
			cout << setw(2) << left << counter +1 << ". " << setw(10) << left << m_name<<"|";
			cout << setw(25) << left << m_description << "|";

			cout << setw(12) << left;
			cout.setf(ios::fixed);
			cout.precision(2);
			
			double priceWithTax = m_price + (g_taxrate * m_price);
			cout << priceWithTax<< "|";
		
			if (m_special == 1) {
				cout << setw(13) << priceWithTax - g_dailydiscount;
			}

			cout << endl;
		}
		else {
			cout << setw(2) << left << counter+1 << ". " << "No Order" << endl;
		}
		counter++;
	}

}