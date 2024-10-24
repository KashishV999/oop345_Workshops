#ifndef SENECA_FOODORDER_H
#define SENECA_FOODORDER_H
#include<iostream>
namespace seneca {
	//two global variables
	extern double g_taxrate; //declaration
	extern double g_dailydiscount; //declaration

	class FoodOrder {
		char m_name[10]{};
		char* m_description{};
		double m_price{};
		bool m_special;

	public:
		FoodOrder()=default; //constructor
		//Rule of three
		~FoodOrder(); //destructor
		FoodOrder(const FoodOrder& other); //copy constructor
		FoodOrder& operator=(const FoodOrder& other); //copy assignment

		void display()const; //display
		std::istream& read(std::istream& in);

	};

}

#endif
