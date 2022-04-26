//
// Created by simon on 15.4.22.
//

#ifndef SEMESTRAL_CCARDTROOP_H
#define SEMESTRAL_CCARDTROOP_H

#include "CCard.h"

class CCardTroop : public CCard {
protected:
	int m_life;
	int m_life_init;
public:
	CCardTroop(std::string mName, std::string mDesc, int mCost, int mDamage, int mProtection, int mCash, int mLife)
	: CCard(std::move(mName), std::move(mDesc), mCost, mDamage, mProtection, mCash), m_life(mLife), m_life_init(mLife) {}

	void print_card( int y, int x ) override;
	bool change_life( int life ) override;
	void restore() override;
};


#endif //SEMESTRAL_CCARDTROOP_H
