
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include <iomanip>
#include "TimedTask.h"
using namespace std;

namespace seneca {
	void TimedTask::startClock() {
		start_time = std::chrono::steady_clock::now();
	}

	void TimedTask::stopClock() {
		end_time = std::chrono::steady_clock::now();
	}

	void TimedTask::addTask(const char* name) {
		static int count = 0;
		task_obj[count].m_name = name;
		task_obj[count].m_units = "nanoseconds";
		task_obj[count].m_duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
		count++;

	}

	std::ostream& operator<<(std::ostream& os, const TimedTask& t)
	{
		os << "Execution Times:" << endl;
		os << "--------------------------" << endl;
		for (Task eachtask : t.task_obj) {
			
			if (eachtask.m_name!="") {
				os << setw(21) << left << eachtask.m_name;

				os << setw(13) << right << eachtask.m_duration.count();
				os << " " << eachtask.m_units << endl;
			}
	
			
		}

		os << "--------------------------" << endl;

		return os;
	}

}