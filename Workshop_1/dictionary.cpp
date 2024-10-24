/*
Name: Kashish Verma
Id: 151579232
Email: kverma45@myseneca.ca
Date: 29 September 2024
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <iomanip>
#include "dictionary.h"
#include "settings.h"
using namespace std;
namespace seneca {
	//constructor
	Dictionary::Dictionary(const char* filename)
	{
		ifstream file(filename);
		if (file) {
			m_size = 0;
			string line{};
			//count number of lines 
			while (getline(file,line)) {
				m_size++;
			}

			file.clear();
			file.seekg(ios::beg);

			words = new Word[m_size];
			size_t count = 0;
			
			while (count < m_size)
			{
				{
					// Reads a word from 'file' into 'words[count].m_word' up to a comma.
					getline(file, words[count].m_word, ',');

					// Reads a part of speech from 'file' into 'pSpeech' up to a comma.
					string pSpeech{};
					getline(file, pSpeech, ',');

					if (pSpeech == "n." || pSpeech == "n. pl.") {
						words[count].m_pos = PartOfSpeech::Noun;
					}
					else if (pSpeech == "adv.") {
						words[count].m_pos = PartOfSpeech::Adverb;
					}
					else if (pSpeech == "a.") {
						words[count].m_pos = PartOfSpeech::Adjective;
					}
					else if (pSpeech == "v." || pSpeech == "v. i." || pSpeech == "v. t." || pSpeech == "v. t. & i.") {
						words[count].m_pos = PartOfSpeech::Verb;
					}

					else if (pSpeech == "prep.") {
						words[count].m_pos = PartOfSpeech::Preposition;
					}

					else if (pSpeech == "pron.") {
						words[count].m_pos = PartOfSpeech::Pronoun;
					}
					else if (pSpeech == "conj.") {
						words[count].m_pos = PartOfSpeech::Conjunction;
					}
					else if (pSpeech == "interj.") {
						words[count].m_pos = PartOfSpeech::Interjection;
					}

					else {
						words[count].m_pos = PartOfSpeech::Unknown;
					}

					// Reads a defination from 'file' into ' words[count].m_definition' up to a endline.
					getline(file, words[count].m_definition, '\n');

					
				}
				++count;
				

			}

		}
		else {
			//current instance to empty state
			this->words= nullptr;
		}
	}
	Dictionary::~Dictionary()
	{
		delete[] words;
	}

	Dictionary::Dictionary(const Dictionary& other)
	{
		*this = other;
	}

	Dictionary& Dictionary::operator=(const Dictionary& other)
	{
		//check self assignment
		if (this != &other) {
			//cleanup
			delete[] words;
			//shallow copy
			m_size = other.m_size;
				//deep copy
				if (m_size != 0u) {
					words = new Word[m_size];
					for (size_t i = 0; i < m_size; i++) {
						words[i] = other.words[i];
					}
				}
		}
		return *this;
	}

	Dictionary::Dictionary(Dictionary&& other) noexcept
	{
		*this = std::move(other);
	}

	Dictionary& Dictionary::operator=(Dictionary&& other) noexcept
	{
		//check self assignment
		if (this != &other) {
			//cleanup
			delete[] words;
			//copy address;
			words = other.words;
			m_size = other.m_size;

			//empty the existing resource
			other.words = nullptr;
			other.m_size = 0;
		}
		return *this;
	}

	
	
	void Dictionary::searchWord(const char* word)
	{
		int count = 0;
		int flag = 1;
		for (size_t i = 0; i < m_size && flag==1; i++) {
			if (words[i].m_word == word) {
				count++;
				// Print the word on the first occurrence
				if (count == 1) {
					cout << words[i].m_word << " - ";
				}
				else {
					cout << setw(strlen(word)) << "" << " - ";
				}

				// Verbose output if enabled and part of speech is known
				if (g_settings.m_verbose && words[i].m_pos != PartOfSpeech::Unknown) {
					cout << "(" << words[i].m_pos << ") ";
				}

				cout << words[i].m_definition << endl;

				// Exit if show_all is false
				if (!g_settings.m_show_all) {
					flag = 0;
				}
			}
		}

		if (count == 0) {
			cout << "Word '" << word << "' was not found in the dictionary." << endl;
		}
	}



	// Outputs the string representation of the PartOfSpeech enum.
	std::ostream& operator<<(std::ostream& os, const PartOfSpeech& pos)
	{
		switch (pos) {
		case PartOfSpeech::Unknown:
			os << "unknown";
			break;

		case PartOfSpeech::Noun:
			os << "noun";
			break;

		case PartOfSpeech::Pronoun:
			os << "pronoun";
			break;

		case PartOfSpeech::Adjective:
			os << "adjective";
			break;

		case PartOfSpeech::Verb:
			os << "verb";
			break;

		case PartOfSpeech::Preposition:
			os << "preposition";
			break;

		case PartOfSpeech::Conjunction:
			os << "conjunction";
			break;

		case PartOfSpeech::Interjection:
			os << "interjection";
			break;

		default:
			os << "unknown";
			break;
		}

		return os;
	}

}