//
// Created by simon on 15.4.22.
//

#ifndef SEMESTRAL_CCARDWARCRY_H
#define SEMESTRAL_CCARDWARCRY_H

#include "CCard.h"

class CCardWarcry : public CCard {
protected:

public:
	CCardWarcry(std::string mName, std::string mDesc, int mCost, int mDamage, int mProtection, int mCash, EAbility mSpecial)
	: CCard(std::move(mName), std::move(mDesc), mCost, mDamage, mProtection, mCash, mSpecial) {}


	void print_card( int y, int x ) override;
	void print_card_wide( int y, int x ) override;
	std::string save_card() override;
	bool change_life( int ) override { return false; }
	void restore() override {}
};


#endif //SEMESTRAL_CCARDWARCRY_H
