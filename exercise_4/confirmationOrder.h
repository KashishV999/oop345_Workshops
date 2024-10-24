#ifndef SENECA_CONFIRMATIONORDER_H
#define SENECA_CONFIRMATIONORDER_H
#include "toy.h"
namespace seneca {
	//AGGREGAGTION
	class ConfirmationOrder {
		const Toy** c_toys{};  //dynamic memory alloaction
		size_t m_size{};
		size_t m_capacity = 1;
		//const Toy* c_toys[] //static memeory allocation

	public:
		ConfirmationOrder& operator+=(const Toy& toy);
		ConfirmationOrder& operator-=(const Toy& toy) ;

		friend std::ostream& operator<<(std::ostream& os, const ConfirmationOrder& other);

		ConfirmationOrder();
		~ConfirmationOrder();
		ConfirmationOrder(const ConfirmationOrder& other);
		ConfirmationOrder& operator=(const ConfirmationOrder& other);
		ConfirmationOrder(ConfirmationOrder&& other) noexcept;
		ConfirmationOrder& operator= (ConfirmationOrder&& other) noexcept;
	};
}


#endif
