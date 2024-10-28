#ifndef SENECA_MAILSERVER_H
#define SENECA_MAILSERVER_H
#include <string>
#include "plugin.h"
#include "message.h"
namespace seneca {
	using Observer_pfn = void(*)(const Message&);

	class MailServer
	{
		std::string m_userName{};
		std::string m_userAddres{};

		//Composition
		Message* m_inbox{}; 
		size_t m_cnt{}; //No of messages in inbox
		size_t m_capacity = 1; //Capacity of messages in a inbox

		//void(*oneNewMailArrived)(const Message&) {};
		Observer_pfn oneNewMailArrived{};

		//Aggregation
		Plugin* m_plugins[2]{};

	public:
		MailServer(const char* name, const char* address);

		//Rule of 5
		//Copy Constructor
		MailServer(const MailServer& other);
		//Copy Assignment
		MailServer& operator=(const MailServer& other);
		//Move Constructor
		MailServer(MailServer&& other) noexcept;
		//Move Assignment
		MailServer& operator=(MailServer&& other) noexcept;
		//Destructor
		~MailServer();

		void receiveMail(Message msg);

		void addPlugin(Plugin* thePlugin);
		void setObserver(void(*observer)(const Message&));
		Message& operator[](size_t idx);
		size_t getInboxSize();
		void showInbox();

	};
}
#endif


