#ifndef SENECA_COLLECTION_H
#define SENECA_COLLECTION_H
#include <iostream>
#include "Pair.h"
namespace seneca {

	template<typename T , size_t CAPACITY>
	class Collection {
		T array[CAPACITY]{};
		size_t m_size{};
		static T element;	//Class member //initialize separately
	public:
		Collection() = default;
		size_t size() const;
		void display(std::ostream& os=std::cout)const;
		virtual bool add(const T& item);
		T operator[] (size_t index)const;
		virtual ~Collection() = default;
	};

	//Class memmber defination
	template <typename T , size_t CAPACITY>
	T Collection<T, CAPACITY>::element{};


	//specialized defination of element
	template<>
	Pair Collection<Pair, 100>::element("No Key", "No value");

	//size()
	template<typename T, size_t CAPACITY>
	size_t Collection<T, CAPACITY>::size() const {
		return m_size;
	}


	//display()
	template<typename T, size_t CAPACITY>
	void Collection<T, CAPACITY>::display(std::ostream& os) const {
		std::cout << "----------------------" << std::endl;
		std::cout << "| Collection Content |" << std::endl;
		std::cout << "----------------------" << std::endl;
		for (size_t i = 0; i < m_size; i++) {
			os << array[i] << std::endl;
		}
		std::cout << "----------------------" << std::endl;
	}

	//operator[]
	template <typename T , size_t CAPACITY>
	T Collection<T, CAPACITY>:: operator[](size_t index) const {
		if (index < m_size) {
			return array[index];
		}
		return element;
	}

	//add()
	template <typename T , size_t CAPACITY>
	bool Collection<T, CAPACITY>::add(const T& item) {
		if (m_size < CAPACITY) {
			array[m_size] = item;
			m_size++;
			return true;
		}
		return false;
	}



}

#endif