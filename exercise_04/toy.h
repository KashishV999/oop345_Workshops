#ifndef SENECA_TOY_H
#define SENECA_TOY_H
#include <string>
namespace seneca {
	class Toy {
		size_t m_id{};
		std::string m_name{};
		int m_num{};
		double m_Originalprice{};
		//we cannot use constexpr in front of an an attribute in a class because it is evaluated at compile-time 
		//while member attributes are evaluated at run-time while creation of a class
		const double HST = 0.13;

	public:
		Toy() = default;
		Toy(const std::string& toy); //Constructor
		void update(int numItems);
		friend std::ostream& operator << (std::ostream& os, const Toy& other);

	};
}


#endif