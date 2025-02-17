#ifndef SENECA_SHOPPINGCART_H
#define SENECA_SHOPPINGCART_H
#include <iostream>
#include "toy.h"
namespace seneca {
	//Composition
	class ShoppingCart {
		const Toy** m_toys{};
		std::string m_name{};
		size_t m_age{};
		size_t m_count{};
		

	public:
		ShoppingCart(const std::string& name, int age, const Toy* toys[], size_t count);

		friend std::ostream& operator<<(std::ostream& os, const ShoppingCart& other);

		//Composition
		//Rule of 5

		//Destructor
		~ShoppingCart();

		//Copy Constructor
		ShoppingCart(const ShoppingCart& other);

		//Copy Assignment
		ShoppingCart& operator=(const ShoppingCart& other);

		//Move constructor
		ShoppingCart(ShoppingCart&& other) noexcept;

		//Move assignment
		ShoppingCart& operator=(ShoppingCart&& other) noexcept;


		


	};

}


#endif
