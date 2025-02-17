/*
Name: Kashish Verma
email: kverma45@myseneca.ca
Student ID: 151579232
date: 7 December 2024

I declare that this submission is the result of my own work
and I only copied the code that my professor provided to complete
my workshops and assignments. This submitted piece of work has not been
shared with any other student or 3rd party content provider.
*/


#include <iostream>
#include "Workstation.h"

using namespace std;
namespace seneca
{


	std::deque<CustomerOrder> g_pending;
	std::deque<CustomerOrder>g_completed{};
	std::deque<CustomerOrder> g_incomplete{};


	void Workstation::fill(std::ostream& os) {
		//fillItem(Station& station, std::ostream& os)
		if (m_order.size() > 0) {
			m_order.front().fillItem(*this, os);
		}
	}

	void Workstation::setNextStation(Workstation* station) {
		m_pNextStation = station;
	}

	Workstation* Workstation::getNextStation() const {
		return m_pNextStation;
	}

	void Workstation::display(std::ostream& os) const {
		os << this->getItemName() << " --> ";
		if (this->getNextStation() == nullptr) {
			os << " End of Line.";
		}
		else {
			//os << m_pNextStation->getItemName();
			os << (this->getNextStation())->getItemName();
		}
		os << "\n";

	}


	Workstation& Workstation::operator+=(CustomerOrder&& newOrder) {
		m_order.push_back(std::move(newOrder));
		return *this;
	}



	bool Workstation::attemptToMoveOrder() // Function definition
	{
		bool hasMove = false; // Initialize a return flag


		
		if (!m_order.empty()) // Check if m_order is not empty
		{
			// Check quantity or if the front order's item is filled
			if (this->getQuantity() == 0u || m_order.front().isItemFilled(this->getItemName()))
			{
				// Move the order to the next station if it exists
				if (this->getNextStation() != nullptr)
				{
					*(m_pNextStation) += std::move(m_order.front());
				}
				else // If no next station, check if order is completed
				{
					if (m_order.front().isOrderFilled())
					{
						g_completed.push_back(std::move(m_order.front())); // Add to completed list
					}
					else
					{
						g_incomplete.push_back(std::move(m_order.front())); // Add to incomplete list
					}
				}
				m_order.pop_front(); // Remove the order from the current station
				hasMove = true;      // Update the flag
			}
		}
		return hasMove; // Return whether an order was moved
	}







}