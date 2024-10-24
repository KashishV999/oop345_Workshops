/*
Name: Kashish Verma
Id: 151579232
Email: kverma45@myseneca.ca
Date: 29 September 2024
*/


#ifndef SENECA_DICTIONARY_H
#define SENECA_DICTIONARY_H
#include <string>
namespace seneca {

	//word,pos,definition
	enum class PartOfSpeech
	{
		Unknown,
		Noun,
		Pronoun,
		Adjective,
		Adverb,
		Verb,
		Preposition,
		Conjunction,
		Interjection,
	
	};
	struct Word
	{
		std::string m_word{};
		std::string m_definition{};
		PartOfSpeech m_pos = PartOfSpeech::Unknown;
	};

	class Dictionary {
		Word* words{};
		size_t m_size{};
	public:
		Dictionary() = default;
		Dictionary(const char* filename);
		//Rule of 5
		~Dictionary(); //destructor
		Dictionary(const Dictionary& other);
		Dictionary& operator=(const Dictionary& other);
		Dictionary(Dictionary&& other) noexcept;
		Dictionary& operator=(Dictionary&& other) noexcept;
		void searchWord(const char* word);
	
	};
	// Plain Enumerations
	std::ostream& operator<<(std::ostream& os, const PartOfSpeech& pos);

}

#endif
