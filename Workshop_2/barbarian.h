/*
Name: Kashish Verma
Id: 151579232
Email: kverma45@myseneca.ca
Date: 20 october 2024
*/

#ifndef SENECA_BARBARIAN_H
#define SENECA_BARBARIAN_H
#include <iostream>
#include "characterTpl.h"
#include "abilities.h"
#include "weapons.h"
namespace seneca {
	template<typename T, typename Ability_t, typename Weapon_t>
	class Barbarian : public CharacterTpl<T>
	{
		int m_baseAttack{};
		int m_baseDefense{};
		Ability_t m_ability;
		Weapon_t m_weapon[2]{};

	public:
	
		
		Barbarian(const char* name, int healthMax, int baseAttack, int baseDefense, Weapon_t primaryWeapon, Weapon_t secondaryWeapon);
		int getAttackAmnt() const;
		int getDefenseAmnt() const;
		void takeDamage(int dmg);
		Character* clone() const;
		void attack(Character* enemy);
	};
	
	//Constructor
	template <typename T, typename Ability_t, typename Weapon_t>
	Barbarian<T, Ability_t, Weapon_t>::Barbarian(const char* name, int healthMax, int baseAttack, int baseDefense, Weapon_t primaryWeapon, Weapon_t secondaryWeapon) 
	:CharacterTpl<T>(name, healthMax), m_baseAttack(baseAttack), m_baseDefense(baseDefense)
	{
		
		m_weapon[0] = primaryWeapon;
		m_weapon[1] = secondaryWeapon;
	}

	//getAttackAmnt
	template <typename T, typename Ability_t, typename Weapon_t>
	int Barbarian<T, Ability_t, Weapon_t>::getAttackAmnt() const {
	
		return static_cast<int>((m_baseAttack + ((static_cast<double> (m_weapon[0])) / 2) + ((static_cast<double> (m_weapon[1])) / 2)));
	}

	//getDefenseAmnt
	template <typename T, typename Ability_t, typename Weapon_t>
	int Barbarian<T, Ability_t, Weapon_t>::getDefenseAmnt() const {
		return m_baseDefense;
	}


	//Clone
	template <typename T, typename Ability_t, typename Weapon_t>
	Character* Barbarian<T, Ability_t, Weapon_t>::clone() const {
	
		Barbarian<T, Ability_t, Weapon_t>* copyInstance = new  Barbarian<T, Ability_t, Weapon_t>(*this);
		return copyInstance;


	}

	//attack
	template <typename T, typename Ability_t, typename Weapon_t>
	void Barbarian<T, Ability_t, Weapon_t>::attack(Character* enemy) {
		std::cout << Character::getName() << " is attacking " << enemy->getName() << "." << std::endl;
		m_ability.useAbility(this);
		int damage = this->getAttackAmnt();
		m_ability.transformDamageDealt(damage);
		std::cout << "    Barbarian deals " << damage << " melee damage!" <<  std::endl;
		enemy->takeDamage(damage);
	}

	template <typename T, typename Ability_t, typename Weapon_t>
	void Barbarian<T, Ability_t, Weapon_t>::takeDamage(int dmg) {
		std::cout << Character::getName() << " is attacked for " << dmg << " damage." << std::endl;
		std::cout << "    Barbarian has a defense of " << m_baseDefense << ". Reducing damage received." << std::endl;

		dmg -= m_baseDefense;

		if (dmg > 0) {
			this->m_ability.transformDamageReceived(dmg);

		}
		else {
			dmg = 0;
		}
			CharacterTpl<T>::takeDamage(dmg);	
	}

}

#endif

