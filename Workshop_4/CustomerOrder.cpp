/*
Name: Kashish Verma
email: kverma45@myseneca.ca
Student ID: 151579232
date: 1 December 2024

I declare that this submission is the result of my own work
and I only copied the code that my professor provided to complete
my workshops and assignments. This submitted piece of work has not been
shared with any other student or 3rd party content provider.
*/


#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "CustomerOrder.h"
#include "Utilities.h"
using namespace std;
namespace seneca {

	//class variable instantion
	size_t CustomerOrder::m_widthField = 0u;


	//Constructor
	CustomerOrder::CustomerOrder(const std::string& line) {

		Utilities util;
		size_t posStart = 0u;
		bool m_moreCust = true;
		m_name = util.extractToken(line, posStart, m_moreCust);
		m_product = util.extractToken(line, posStart, m_moreCust);
		
		std::vector<string> itemName{};
		while (m_moreCust==true) {
			itemName.push_back(util.extractToken(line, posStart, m_moreCust));
			
		}

		m_cntItem = itemName.size();

		m_lstItem = new Item* [m_cntItem];
		for (size_t i = 0; i < m_cntItem; ++i) {
			m_lstItem[i] = new Item(itemName[i]);
		}

		if (m_widthField < util.getFieldWidth()) {
			m_widthField = util.getFieldWidth();
		}

	}


	//Move Constructor
	CustomerOrder::CustomerOrder(CustomerOrder&& other) noexcept {
		*this = std::move(other);
	}

	//Move Assignment
	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& other) noexcept {
		//check self-assignmnet
		if (this != &other) {
			//clean-up
			for (size_t i = 0; i < m_cntItem; ++i) {
				delete m_lstItem[i];
			}
			delete[] m_lstItem;

			//shallow copy
			m_name = other.m_name;
			m_product = other.m_product;
			m_cntItem = other.m_cntItem;

			//move resource
			m_lstItem = other.m_lstItem;
			other.m_lstItem = nullptr;
			other.m_name = "";
			other.m_product = "";
			other.m_cntItem = 0;
		}

		return *this;
	}

	CustomerOrder::~CustomerOrder() {
		for (size_t i = 0; i < m_cntItem; ++i) {
			delete m_lstItem[i];
		}
		delete[] m_lstItem;
	}

	void CustomerOrder::fillItem(Station& station, std::ostream& os) {
		
		for (size_t i = 0; i < m_cntItem; ++i) {
			//station handles the item that the customer orders has
			if ((station.getItemName()==m_lstItem[i]->m_itemName) && (m_lstItem[i]->m_isFilled==false)) {

				//station has enough stock of items
				if (station.getQuantity() > 0u) {
					station.updateQuantity();
					m_lstItem[i]->m_isFilled = true;
					m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
					os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << "\n";
					break;
					

				}

				//station has NO items left EMPTY
				else {
					os<<"    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << "\n";
				}
				//os<< m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]"<<"\n";

				//fills only one item in order by that name :
				//order can have 3 items of Bed but it will only fill one Bed
				//break;
			}


			//MY COMMENT
			//os << "NOT FILLED -Order Items did not match station name \n";
		}
	}

	bool CustomerOrder::isItemFilled(const std::string& itemName) const {
		bool isFilled = true;
		for (size_t i = 0; i < m_cntItem; ++i) {
			if (itemName == m_lstItem[i]->m_itemName && m_lstItem[i]->m_isFilled==false) {
				isFilled = false;
				break;
			}
		}
		return isFilled;
	}

	bool CustomerOrder:: isOrderFilled() const {
		bool isFilled = true;
		for (size_t i = 0; i < m_cntItem; ++i) {
			if (m_lstItem[i]->m_isFilled == false) {
				isFilled = false;
				break;
			}
		}
		return isFilled;
	}


	void CustomerOrder:: display(std::ostream& os) const {
		os << m_name << " - " << m_product << "\n";
		for (size_t i = 0; i < m_cntItem; ++i) {
			os<<   "[" << setw(6) << right << setfill('0')<< m_lstItem[i]->m_serialNumber << "]";
			cout << setfill(' ');
			os << " " << setw(m_widthField)<< left<<  m_lstItem[i]->m_itemName;
			os << " - ";
			if (this->isItemFilled(m_lstItem[i]->m_itemName) == true) {
				
				os << "FILLED";
			}
			else {
				os << "TO BE FILLED";
			}
			os << "\n";
		}
	}




}
