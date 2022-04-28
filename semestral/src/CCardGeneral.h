//
// Created by simon on 15.4.22.
//

#ifndef SEMESTRAL_CCARDGENERAL_H
#define SEMESTRAL_CCARDGENERAL_H

#include "CCard.h"

class CCardGeneral : public CCard {
protected:
	int m_life;
	int m_life_init;
public:
	CCardGeneral(std::string mName, std::string mDesc, int mLife, int mCost, int mDamage, int mProtection, int mCash, EAbility mSpecial)
	: CCard(std::move(mName), std::move(mDesc), mCost, mDamage, mProtection, mCash, mSpecial), m_life(mLife), m_life_init(mLife) {}

	void print_card( int y, int x ) override;
	void print_card_wide( int y, int x ) override;
	std::string save_card() override;
	bool change_life( int life ) override;
	void restore() override;
};


#endif //SEMESTRAL_CCARDGENERAL_H
