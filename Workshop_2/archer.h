/*
Name: Kashish Verma
Id: 151579232
Email: kverma45@myseneca.ca
Date: 20 october 2024
*/


#ifndef SENECA_ARCHER_H
#define SENECA_ARCHER_H
#include <iostream>
#include "health.h"
namespace seneca {
	template <typename Weapon_t>
	class Archer : public CharacterTpl<SuperHealth> {
		int m_baseDefense{};
		int m_baseAttack{};
		Weapon_t m_weapon;

	public:
		Archer(const char* name, int healthMax, int baseAttack, int baseDefense, Weapon_t weapon)
			:CharacterTpl<SuperHealth>(name, healthMax), m_baseDefense(baseDefense), m_baseAttack(baseAttack), m_weapon(weapon)
		{ 
			//
		}
	
		
		int getAttackAmnt() const 
		{ 
			return static_cast<int>(1.3 * m_baseAttack);
		}

		int getDefenseAmnt() const 
		{ 
			return static_cast<int>(1.2 * m_baseDefense);
		}

		Character* clone() const
		{ 
			Archer<Weapon_t>* copyInstance = new  Archer<Weapon_t>(*this);
			return copyInstance;
		}

		void attack(Character* enemy) 
		{
			std::cout << Character::getName() << " is attacking " << enemy->getName() << "." << std::endl;
			int damage = this->getAttackAmnt();
			std::cout << "    Archer deals " << damage << " ranged damage!" << std::endl;
			enemy->takeDamage(damage);
		}

		void takeDamage(int dmg) 
		{ 
			std::cout << Character::getName() << " is attacked for " << dmg << " damage." << std::endl;
			std::cout << "    Archer has a defense of " << this->getDefenseAmnt() << ". Reducing damage received." << std::endl;
			int defense = this->getDefenseAmnt();
			dmg -= defense;
			if (dmg < 0) {
				dmg = 0;
			}
		
			CharacterTpl<SuperHealth>::takeDamage(dmg);
		}

	};
}


#endif

