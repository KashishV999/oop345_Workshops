
#ifndef SENECA_TIMEDTASK_H
#define SENECA_TIMEDTASK_H
#include <string>
#include <chrono>

namespace seneca {
	struct Task {
		std::string m_name{};
		std::string m_units{};
		std::chrono::steady_clock::duration m_duration;
		

	};

	class TimedTask {
		Task task_obj[10]{};
		int  num_record{};
		std::chrono::steady_clock::time_point start_time{};
		std::chrono::steady_clock::time_point end_time{};

	public:
		TimedTask() = default;
		void startClock();
		void stopClock();
		void addTask(const char* name);
		friend std::ostream& operator<<(std::ostream& os, const TimedTask& t);
	};
}

#endif

