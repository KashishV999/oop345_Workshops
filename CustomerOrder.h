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


#ifndef SENECA_CUSTOMERORDER_H
#define SENECA_CUSTOMERORDER_H
#include <string>
#include "Station.h"
namespace seneca {

	struct Item
	{
		std::string m_itemName;
		size_t m_serialNumber{ 0 };
		bool m_isFilled{ false };

		//constructor
		Item(const std::string& src) : m_itemName(src) {};
	};


	class CustomerOrder
	{
		std::string m_name{};
		std::string m_product{};
		size_t m_cntItem{};
		Item** m_lstItem{}; //  Manage.

		//class variable
		static size_t m_widthField;

	public:
		CustomerOrder() = default;
		//reference to an unmodifiable string
		CustomerOrder(const std::string& line);

		//NO COPY
		CustomerOrder& operator=(const CustomerOrder& other) = delete;
		CustomerOrder(const CustomerOrder& other) { throw "No Copy Allowed Broooo"; }

		//Move: should "promise"
		CustomerOrder(CustomerOrder&& other) noexcept;
		CustomerOrder& operator=(CustomerOrder&& other) noexcept;

		//Destructor
		~CustomerOrder();

		bool isOrderFilled() const ;
		bool isItemFilled(const std::string& itemName) const;
		void fillItem(Station& station, std::ostream& os);
		void display(std::ostream& os) const;


	};



}

#endif
