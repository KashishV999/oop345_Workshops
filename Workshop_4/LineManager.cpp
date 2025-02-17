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
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include "LineManager.h"
#include "Workstation.h"
#include "Utilities.h"
using namespace std;

namespace seneca {
	  
	
	LineManager::LineManager(const std::string& fileName, const std::vector<Workstation*>& stations) {
		ifstream file(fileName);
	

		if (!file) {
			throw std::string("Unable to open [") + fileName + "] file";
		}

		string theRecord{};
		

		//STRINGS
		std::vector<std::string> activeWorkS{};
		std::vector<std::string> nextWork{};

		

		while (!file.eof()) {
			bool moreWS = false;
			size_t posS = 0u;
			
			//theRecord 
			//WORKSTATION|NEXT_WORKSTATION
			getline(file, theRecord);
		
			Utilities util;
			util.setDelimiter('|');
	

			

			activeWorkS.push_back(util.extractToken(theRecord, posS, moreWS));
			
			if (moreWS == true) {

				nextWork.push_back(util.extractToken(theRecord, posS, moreWS));
			}
			else {
				nextWork.push_back(""); //empty string
			}
		

		}
		file.close();


		//Replace with STL ALGORITHMS
	/*	for (size_t i = 0u; i < activeWorkS.size(); ++i) {
			for (auto& station : stations) {
				if (activeWorkS[i] == station->getItemName()) {
					m_activeLine.push_back(station);
				}
			}
		}*/


		std::for_each(activeWorkS.begin(), activeWorkS.end(), [&](auto &elem)
			{
				auto it = std::find_if(stations.begin(), stations.end(), [&](const auto& station) {
					return elem == station->getItemName();
					});
				if (it != stations.end()) {
					m_activeLine.push_back(*it);
				}

			});



		/*for (size_t i = 0u; i < m_activeLine.size(); ++i) {
			
			if (nextWork[i] != "") {
				for (auto& station : m_activeLine) {
					if (nextWork[i] == station->getItemName()) {
						m_activeLine[i]->setNextStation(station);
						break;
					}
				}

			}
			else {
				m_activeLine[i]->setNextStation();
			}
		}*/


		auto nextWorkIter = nextWork.begin();

		std::for_each(m_activeLine.begin(), m_activeLine.end(),
			[&](auto& station) {
				if (!(*nextWorkIter).empty()) {
					auto it = std::find_if(m_activeLine.begin(), m_activeLine.end(),
						[&](const auto& s) {
							return *nextWorkIter == s->getItemName();
						});

					if (it != m_activeLine.end()) {
						station->setNextStation(*it);
					}
				}
				else {
					station->setNextStation();
				}
				++nextWorkIter; // Move to the next element in nextWork
			});



		//first station find
		/*size_t index = 0u;
		
		for (size_t i = 0u; i < activeWorkS.size(); ++i) {
			bool isFound = true;
			for (size_t j = 0u; j < nextWork.size(); ++j) {
				if (activeWorkS[i] == nextWork[j]) {
					isFound = false;
					break;
				}
			}

			if (isFound == true) {
				index = i;
				break;
			}

		}
		m_firstStation = m_activeLine[index];*/


		auto it = std::find_if(activeWorkS.begin(), activeWorkS.end(), [&](const auto& station) {
			return std::none_of(nextWork.begin(), nextWork.end(), [&](const auto& next) {
				return station == next;
				});
			});

		if (it != activeWorkS.end()) {
			size_t index = std::distance(activeWorkS.begin(), it); // Get the index of the first station
			m_firstStation = m_activeLine[index];
		}




		m_cntCustomerOrder = g_pending.size();

	}



	void LineManager::reorderStations() {
		std::vector<Workstation*> reorderedStations{};
		Workstation* currentStation = m_firstStation;

		// Traverse the stations starting from the first station
		while (currentStation != nullptr) {
			reorderedStations.push_back(currentStation);  // Add to reordered list
	
			currentStation = currentStation->getNextStation();  // Move to next station
		}

		// Replace m_activeLine with reordered stations
		m_activeLine = reorderedStations;
	}




	//one iteration of operations on all of the workstations
	bool LineManager:: run(std::ostream& os) {

		static int cnt = 0;
		++cnt;
		os << "Line Manager Iteration: " << cnt << "\n";


		if (!g_pending.empty()) {
			   *m_firstStation += std::move(g_pending.front());
			g_pending.pop_front();
		}


	
		// Step 2: Execute one fill operation for each workstation on the line
		for (Workstation* station : m_activeLine) {
			station->fill(os); // Perform the one fill operation
		}

		for (Workstation* station : m_activeLine) {
			station->attemptToMoveOrder();
		}



	
		if (g_completed.size() + g_incomplete.size() == m_cntCustomerOrder) {
			return true;
		}

		return false;

	}


	void LineManager::display(std::ostream& os) const {
		for (size_t i = 0; i < m_activeLine.size(); ++i) {
			//Workstation::display
			m_activeLine[i]->display(os);
		}
	}




}
