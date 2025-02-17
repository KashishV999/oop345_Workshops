#include <iostream>
#include <iomanip>
#include "mailServer.h"

using namespace std;
namespace seneca {
	MailServer::MailServer(const char* name, const char* address)
	{
		m_userName = name;
		m_userAddres = address;

		m_inbox = new Message[m_capacity];
	}

	void MailServer::receiveMail(Message msg)
	{
		if (msg.m_toAddress == m_userAddres) {
			//Resize and Add
			if (m_cnt == m_capacity) {
				size_t newCapacity = 2 * m_capacity;
				Message* new_inbox = new Message[newCapacity];

				//Copy address
				for (size_t i = 0; i < m_cnt; ++i) {
					new_inbox[i] = m_inbox[i];
				}
				delete[] m_inbox;
				m_inbox = new_inbox;
				m_capacity = newCapacity;

			}

			m_inbox[m_cnt] = msg;


		//	m_plugins[0]->operator()(m_inbox[m_cnt]);
		//m_plugins[1]->operator()(m_inbox[m_cnt]);

		
			for (size_t i = 0; i < 2; ++i) {
				if(m_plugins[i]!=nullptr)
					m_plugins[i]->operator()(m_inbox[m_cnt]);
			}

			if (oneNewMailArrived) {
				oneNewMailArrived(m_inbox[m_cnt]);
			}

			++m_cnt;
		}

		else {
			std::string msgA = "EXCEPTION: Message intended for ";
			msgA += "[";
			if (msg.m_toAddress != "") {
				msgA += msg.m_toAddress;
			}

			msgA += "]";
			//const char* msgAdd = msgA.c_str();
			//throw const char*
			throw  msgA;
		}
	}



	//Rule of 5 
	//Copy Constructor
	MailServer::MailServer(const MailServer& other) {
		*this = other;
	}

	//Move constructor
	MailServer::MailServer(MailServer&& other) noexcept {
		*this = move(other);
	}

	//TODO
	//Copy Assignment 
	MailServer& MailServer:: operator=(const MailServer& other) {
		//Self Assignment
		if (this != &other) {
			//clean-up
			delete[] m_inbox;
		
			//shallow copy
			m_userName = other.m_userName;
			m_userAddres = other.m_userAddres;
			m_cnt = other.m_cnt;
			m_capacity = other.m_capacity;
			//oneNewMailArrived = other.oneNewMailArrived;

			//deep copy
			
			//Composition  --> creates a new copy of the object and works on it independently
			if (m_cnt > 0u) {
				//m_inbox = new Message[m_cnt];
				m_inbox = new Message[m_capacity];
				for (auto i = 0u; i < m_cnt; ++i) {
					m_inbox[i] = other.m_inbox[i];
				}
			}
			else {
				m_inbox = nullptr;
			}

			//Aggregation
			//Just copy address of pointers
			for (size_t i = 0; i < 2; ++i) {
				m_plugins[i] = other.m_plugins[i];
			}

		}

		return *this;
	}


	//Move Assignment
	MailServer& MailServer::operator=(MailServer&& other) noexcept {
		//check Self-assignment
		if (this != &other) {
			//clean-up
			delete[] m_inbox;

			//shallow copy
			m_userName = other.m_userName;
			m_userAddres = other.m_userAddres;
			m_cnt = other.m_cnt;
			m_capacity = other.m_capacity;
			//oneNewMailArrived = other.oneNewMailArrived;

			//Copy Address
			m_inbox = other.m_inbox;

			for (size_t i = 0; i < 2; ++i) {
				m_plugins[i] = other.m_plugins[i];
			}

		//TODO DO NOT DELETE IT JUST CHANGE TO NULLPTR
			//delete[] other.m_inbox;
			other.m_inbox = nullptr;
			other.m_cnt = 0;
			other.m_capacity = 0;
			//You cannot delete plugin cause thats in aggregation


		}
		return *this;
	}


	MailServer::~MailServer() {
		delete[]m_inbox;
		m_inbox = nullptr;
	}



	void MailServer::addPlugin(Plugin* thePlugin)
	{
		int firstAvailable = -1;
		for (size_t i = 0; i < 2; ++i) {
			if (m_plugins[i] == nullptr) {
				firstAvailable = i;
				break;
			}
		}

		m_plugins[firstAvailable] = thePlugin;

	}

	void MailServer::setObserver(void(*observer)(const Message&)) {
		oneNewMailArrived = observer;
	}

	size_t MailServer::getInboxSize() {
		return m_cnt;
	}

	void MailServer::showInbox() {
 		for (size_t i = 0; i < m_cnt; ++i) {
			cout << right << setw(20) << m_inbox[i].m_fromName;
			cout << "  ";
			cout << left << setw(40) << m_inbox[i].m_fromAddress;
			cout << "  ";
			size_t firstSpace = m_inbox[i].m_date.find(' ');

			cout << left << setw(15) << m_inbox[i].m_date.substr(0, firstSpace);
			cout << "  ";
			cout << m_inbox[i].m_subject << "\n";
		}
	}


	Message& MailServer::operator[](size_t idx) {
		if (idx >= m_cnt) {
			throw out_of_range("Index " + std::to_string(idx) + " is out of bounds.");
		}
		return m_inbox[idx];
	}

}