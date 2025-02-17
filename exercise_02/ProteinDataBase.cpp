#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<fstream>
#include <string>

#include "ProteinDataBase.h"

using namespace std;

namespace seneca {
	//Destructor
	ProteinDatabase::~ProteinDatabase() {

		delete[] arrayID;   // Deallocates arrayID
		delete[] arrayAmino; // Deallocates arrayAmino

	}

	//Copy constructor
	ProteinDatabase::ProteinDatabase(const ProteinDatabase& other) {
		*this = other;
	}

	//Copy Assignment 
	ProteinDatabase& ProteinDatabase::operator=(const ProteinDatabase& other) {
		//self assignment
		if (this != &other) {
			//cleanup
			delete[] arrayID;
			delete[] arrayAmino;

			//shallow copying
			numSequence = other.numSequence;

			//deep copy
			if (numSequence != 0) {
				arrayID = new string[numSequence];
				arrayAmino = new string[numSequence];
				for (size_t i = 0; i < numSequence; i++) {
					arrayID[i] = other.arrayID[i];
					arrayAmino[i] = other.arrayAmino[i];
				}
			}

			else {
				arrayID = nullptr;
				arrayAmino = nullptr;
			}

		}
		return *this;
	}

	ProteinDatabase::ProteinDatabase(ProteinDatabase&& other) noexcept {
		*this = move(other);
	}


	ProteinDatabase& ProteinDatabase:: operator=(ProteinDatabase&& other) noexcept {
		//self assignment
		if (this != &other) {
			//clean-up


			delete[] arrayID;
			delete[] arrayAmino;

			//shallow copying
			numSequence = other.numSequence;
			//deep copy
			//if (numSequence != 0u) {
				// copy address to current object
			arrayAmino = other.arrayAmino;
			arrayID = other.arrayID;

			// the parameter doesn't have the resource anymore
			other.arrayAmino = nullptr;
			other.arrayID = nullptr;
			other.numSequence = 0;

			//}
		}

		return *this;
	}


	//getters
	size_t ProteinDatabase::size() const {
		return numSequence;
	}

	string ProteinDatabase:: operator[](size_t index) const {
		string sequence{};
		if ((index >= 0 && index < numSequence)) {

			sequence = arrayAmino[index];

		}

		return sequence;
	}

	string ProteinDatabase::getUID(size_t index) const {
		string ID{};
		if (index >= 0 && index < numSequence) {
			ID = arrayID[index];
		}
		else {
			ID = "None";
		}
		return ID;
	}




	ProteinDatabase::ProteinDatabase(const string filename) {



		//reads the file to count the number of protein sequences present in the file.
		ifstream file(filename);

		string line{};
		if (file) {

			string line{};
			while (getline(file, line)) {

				if (line[0] == '>') {
					numSequence++;
				}
			}

			//just to check
			cout << "------------------------------------------" << endl;
			cout << "Num of Sequence: " << numSequence << endl;
			cout << "------------------------------------------" << endl;

			arrayID = new string[numSequence];
			arrayAmino = new string[numSequence];


			//to reset the file to the beginning
			file.clear();
			file.seekg(ios::beg); //resets the file to the beginning

			//re-reads the file and loads the protein sequences (i.e., string of characters not sequence names)
			//  and IDs into the arrays.
	//		file.close();
	//		file.open(filename);

			//if (file)
			{
				char c{};
				int count = -1;
				while (file) {
					file.get(c);
					//check whether the file is getting the character or not
					// if get does not get nay charcater it leaves the unmodified value
					if (file)
					{
						if (c == '>') {
							count++;
							string extra{};
							getline(file, extra, '|');
							getline(file, arrayID[count], '|');
							file.ignore(1000, '\n');

						}
						else {


							if (count < numSequence) {

								arrayAmino[count] += c; // Add the character
								string remainingLine;
								getline(file, remainingLine, '\n');
								arrayAmino[count] += remainingLine; // Append the rest of the line
							}


						}
					}

				}
			}
		}
		else {
			cout << "Error opening the file" << endl;
		}
	}
}


