#ifndef SENECA_SET_H
#define SENECA_SET_H
#include <cmath>
#include <cstdlib>
#include "Collection.h"
namespace seneca {
	constexpr size_t CAPACITY = 100;
	template <typename T>
	class Set : public Collection<T, CAPACITY> {
	public:
		//overriden add
		bool add(const T& item);

	};
	
	template <typename T>
	bool Set<T>::add(const T& item) {
		Set<T>& currentInstance = (*this);
		for (size_t i = 0; i < currentInstance.size(); ++i) {
			if (currentInstance[i] == item) {
				return false;
			}
		}
		return Collection<T, CAPACITY>::add(item);
	}

	//TODO: CHECK OUT AGAIN
	//specialized add
	template<>
	bool Set<double>::add(const double& item) {
		Set<double>& currentInstance = (*this);
		for (size_t i = 0; i < currentInstance.size(); ++i) {
			if ((std::abs(currentInstance[i] - item)) <= 0.01) {
				return false;
			}
		}
		
		return Collection<double, CAPACITY>::add(item);
	}


}

#endif
