/*
Name: Kashish Verma
Id: 151579232
Email: kverma45@myseneca.ca
Date: 20 october 2024
*/

#ifndef SENECA_CHARACTERTPL_H
#define SENECA_CHARACTERTPL_H
#include<iostream>
#include <string>
#include "character.h"
namespace seneca {
	template <typename T>
	class CharacterTpl : public Character
	{
		int m_healthMax{};
		//T can be: int, double,  InfinitHealth,  SuperHealth
		T m_health{};

	public:

		CharacterTpl(const std::string& name, int healthMax);
		void takeDamage(int dmg) override;
		int getHealth() const override;
		int getHealthMax() const override;
		void setHealth(int health) override;
		void setHealthMax(int health) override;

	};

	//Constructor
	template<typename T>
	CharacterTpl<T>::CharacterTpl(const std::string& name, int healthMax) : Character(name.c_str()) {


		setHealthMax(healthMax);
	}

	//Override: takeDamage 
	template <typename T>
	void CharacterTpl<T>::takeDamage(int dmg) {
		m_health -= dmg; //health decrease based on damage done
		if (m_health < 0) {
			m_health = 0;
		}

		CharacterTpl<T>& currentInstance = *this;
		if (m_health) { //m_health > 0
			std::cout << "    " << currentInstance.getName() << " took " << dmg << " damage, " << m_health << " health remaining." << std::endl;
		}
		else {
			std::cout << "    " << currentInstance.getName() << " has been defeated!" << std::endl;
		}
	}

	//getHealth
	template <typename T>
	int CharacterTpl<T>::getHealth() const
	{
		return static_cast<int>(m_health);
	}

	//getHealthMax
	template <typename T>
	int CharacterTpl<T>::getHealthMax()const {
		return m_healthMax;
	}

	//setHealth
	template<typename T>
	void CharacterTpl<T>::setHealth(int health) {
		m_health = health;
	}

	//setHealthMax
	template <typename T>
	void CharacterTpl<T>::setHealthMax(int health) {
		m_healthMax = health;
		m_health = health;

	}

}

#endif


