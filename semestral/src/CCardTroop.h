//
// Created by simon on 15.4.22.
//

#ifndef SEMESTRAL_CCARDTROOP_H
#define SEMESTRAL_CCARDTROOP_H

#include "CCard.h"

/// Derived class from CCard representing a player's deployable troop. It has its own health tracker and in case of death,
/// it is returned back to player's discard pile with its health restored.
class CCardTroop : public CCard {
protected:
	int m_life;
	int m_life_init;
public:
	CCardTroop(std::string mName, std::string mDesc, int mLife, int mCost, int mDamage, int mProtection, int mCash, EAbility mSpecial)
	: CCard(std::move(mName), std::move(mDesc), mCost, mDamage, mProtection, mCash, mSpecial), m_life(mLife), m_life_init(mLife) {}

	void print_card( int y, int x ) override;
	void print_card_wide( int y, int x ) override;
	std::string save_card() override;

	std::vector<int> attributes() override;

	bool change_life( int life ) override;
	void restore() override;
};


#endif //SEMESTRAL_CCARDTROOP_H
