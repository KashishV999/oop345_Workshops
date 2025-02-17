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


#ifndef SENECA_WORKSTATION_H
#define SENECA_WORKSTATION_H
#include <vector>
#include <deque>
#include "Station.h"
#include "CustomerOrder.h"
namespace seneca {

	//TODO: global variables
	
		extern std::deque<CustomerOrder> g_pending; //first station
		
		extern std::deque<CustomerOrder>g_completed; //last station
	
		extern std::deque<CustomerOrder> g_incomplete; //last station

	//Workstation is a Station
	//every Workstation fills one item in a Customer Order
	class Workstation: public Station
	{
		//TODO:instance variable
		std::deque<CustomerOrder> m_order{};
		Workstation* m_pNextStation{};

		public:

			//delete copy and move
			Workstation(const Workstation& other) = delete;
			Workstation& operator=(const Workstation& other) = delete;
			Workstation(Workstation&& other) noexcept = delete;
			Workstation& operator=(Workstation&& other) = delete;

			//Constructor
			Workstation(const std::string Wrecord) : Station(Wrecord) {}
			void fill(std::ostream& os);
			bool attemptToMoveOrder();
			void setNextStation(Workstation* station=nullptr);
			Workstation* getNextStation() const;
			void display(std::ostream& os) const;
			Workstation& operator+=(CustomerOrder&& newOrder);
	
	};
}

#endif
