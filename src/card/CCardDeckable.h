//
// Created by simon on 19.5.22.
//

#ifndef SEMESTRAL_CCARDDECKABLE_H
#define SEMESTRAL_CCARDDECKABLE_H

#include <sstream>

#include "CCard.h"

class CCardDeckable : public CCard {
public:
	CCardDeckable(std::string mName, std::string mDesc, int mCost, int mDamage, int mProtection, int mCash, EAbility mSpecial)
		: CCard(std::move(mName), std::move(mDesc), mCost, mDamage, mProtection, mCash, mSpecial) {}

	CCardDeckable( const CCardDeckable & rhs ) = default;
	virtual ~CCardDeckable() = default;
	CCardDeckable& operator=( const CCardDeckable & ) = default;

	/// Static method that creates a new card based on information in the given string.
	/// @return Shared pointer to the newly created card.
	static std::shared_ptr<CCardDeckable> load_card (const std::string& line);
};


#endif //SEMESTRAL_CCARDDECKABLE_H
