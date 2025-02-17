#include <iostream>
#include <iomanip>
#include "toy.h"
using namespace std;
namespace seneca {
	void Toy::update(int numItems) {
		m_num = numItems;
	}

	Toy::Toy(const std::string& toy) {
		//ID:NAME:NUM:PRICE
		//throw "Not implemented yet"; 
		
		int first = toy.find_first_of(':');
		int second = toy.find(':', first + 1);
		int third = toy.find(':', second + 1);

		m_id = stoi(toy.substr(0, first));
		
		

		m_name = toy.substr(first + 1, second - first - 1);
		int start_spaces = m_name.find_first_not_of(' ');
		int end_spaces = m_name.find_last_not_of(' ');
		m_name.erase(end_spaces+1);
		m_name.erase(0, start_spaces);

		m_num = stoi(toy.substr(second + 1, third - second - 1));

		m_Originalprice = stod(toy.substr(third + 1));
		

	}
	//Toy ID: NAME QTY items @ PRICE/item  subtotal: SUBTOTAL  tax: TAX  total: TOTAL_PRICE<endl>
	ostream& operator << (ostream& os, const Toy& other) {
		
		cout << "Toy " << setw(8) << right << setfill('0') << other.m_id << ": ";
		cout << right << setw(24) << setfill('.') << other.m_name << " ";
		cout << right << setw(2) << setfill(' ') << other.m_num << " items @ ";
		cout << right << setw(6) << setfill(' ');
		cout.setf(ios::fixed);
		cout.precision(2);
		cout << other.m_Originalprice << "/item  subtotal: ";

		double subtotal = other.m_Originalprice * other.m_num;
		cout << setw(7) << right << subtotal;
		double tax = other.HST * subtotal;

		cout << "  tax: " << setw(6)<< setfill(' ')<< tax;
		cout << "  total: " << right << setw(7) << setfill(' ') << subtotal + tax<<endl;


		return os;
	}


}
