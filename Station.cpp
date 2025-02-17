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

#include<iostream>
#include <string>
#include<iomanip>
#include "Utilities.h"
#include "Station.h"

using namespace std;
namespace seneca {
	//initialize class varaiables
	size_t Station::m_widthField = 0;
	size_t Station::id_generator = 0;

	Station::Station(const std::string& record) {
		++id_generator;
		m_id = id_generator;
		
		size_t posS = 0;
		bool m_more = true;

		//extractToken is not static, so you need to create a seneca::Utilities object to call it.
		Utilities util;

		m_name = util.extractToken(record, posS, m_more);
		
		if (m_more == true) {

			m_serNo = stoul(util.extractToken(record, posS, m_more));
			m_num = stoul(util.extractToken(record, posS, m_more));

			if (m_widthField < util.getFieldWidth()) {
				m_widthField = util.getFieldWidth();
			}

			m_desc = util.extractToken(record, posS, m_more);
		}
		
	}

	const std::string& Station:: getItemName() const {
		return m_name;
	}

	size_t Station::getNextSerialNumber() {
		
		return m_serNo++;
	}

	size_t Station::getQuantity() const {
		return m_num;
	}

	void Station::updateQuantity() {
		if (m_num > 0) {
			--m_num;
		}
	}

	void Station::display(std::ostream& os, bool full) const {
		os << setw(3) << setfill('0')<< right<<  m_id << " | ";
		cout << setfill(' ');
		os << setw(m_widthField) << left<< m_name << " | ";
		os << setw(6) << setfill('0')<< right<< m_serNo << " | ";
		
		if (full == true) {
			os << setfill(' ');
			//os << " ";
			os << setw(4) << m_num << " | ";
			os << m_desc;
		}
		os << "\n";
	}

}
