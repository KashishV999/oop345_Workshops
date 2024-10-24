#ifndef SENECA_PROTEINDATABASE_H
#define  SENECA_PROTEINDATABASE_H
#include <string>

namespace seneca {
	class ProteinDatabase
	{
		std::string* arrayID{};  // array will store the Unique IDs of the proteins 
		std::string* arrayAmino{};  //array will store the sequence of amino acids
		size_t numSequence{};
		


	public:

	

		ProteinDatabase() {
			int a;
		};

		ProteinDatabase(const std::string filename);


		//Rule of 5
		~ProteinDatabase(); //Destructor
		ProteinDatabase(const ProteinDatabase& other); //copy constructor
		ProteinDatabase& operator=(const ProteinDatabase& other); //copy assignment
		ProteinDatabase(ProteinDatabase&& other) noexcept; //move constructor
		ProteinDatabase& operator=(ProteinDatabase&& other) noexcept; //move assignment

		//getter
		size_t size() const;
		std::string operator[] (size_t) const;
		std::string getUID(size_t) const;

	};
}

#endif

