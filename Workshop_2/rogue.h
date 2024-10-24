/*
Name: Kashish Verma
Id: 151579232
Email: kverma45@myseneca.ca
Date: 20 october 2024
*/

#ifndef SENECA_ROGUE_H
#define SENECA_ROGUE_H
#include <iostream>
#include "abilities.h"
#include "characterTpl.h"
namespace seneca {
	template <typename T, typename FirstAbility_t, typename SecondAbility_t>
	class Rogue :public  CharacterTpl<T>{
		int m_baseAttack{};
		int m_baseDefense{};
		FirstAbility_t m_firstAbility{};
		SecondAbility_t m_secondAbility{};
		Dagger m_weapon;
	public:
		
		Rogue(const char* name, int healthMax, int baseAttack, int baseDefense) 
			:CharacterTpl<T>(name, healthMax), m_baseAttack(baseAttack), m_baseDefense(baseDefense)
		{ 
			//
		}
		int getAttackAmnt() const 
		{ 
			double weaponDamage = static_cast<double>(m_weapon.m_damage);
			return static_cast<int>(m_baseAttack + (2 * weaponDamage));
		}
		int getDefenseAmnt() const
		{
			return m_baseDefense;
		}
		Character* clone() const
		{
			Rogue<T, FirstAbility_t, SecondAbility_t>* copyInstance = new  Rogue<T, FirstAbility_t, SecondAbility_t>(*this);
			return copyInstance;
		}

		void attack(Character* enemy) 
		{
			std::cout << Character::getName() << " is attacking " << enemy->getName() << "." << std::endl;

			m_firstAbility.useAbility(this);
			m_secondAbility.useAbility(this);
			int damage = this->getAttackAmnt();
			m_firstAbility.transformDamageDealt(damage);
			m_secondAbility.transformDamageDealt(damage);

			std::cout << "    Rogue deals " << damage << " melee damage!" << std::endl;

			enemy->takeDamage(damage);
		}

		void takeDamage(int dmg) { 
			std::cout << Character::getName() << "is attacked for " << dmg << " damage." << std::endl;
			std::cout << "    Rogue has a defense of " << m_baseDefense << ". Reducing damage received."<<std::endl;
			dmg -= m_baseDefense;

			if (dmg > 0) {
				m_firstAbility.transformDamageReceived(dmg);
				m_secondAbility.transformDamageReceived(dmg);
			}
			else {
				dmg = 0;
			}

			CharacterTpl<T>::takeDamage(dmg);
		}


	};
}

#endif

