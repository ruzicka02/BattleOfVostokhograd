//
// Created by simon on 15.4.22.
//

#ifndef SEMESTRAL_CCARD_H
#define SEMESTRAL_CCARD_H

#include <memory>
#include <string>

class CCard {
protected:
	// general properties
	std::string m_name;
	std::string m_desc;
	int m_cost;

	// abilities
	int m_damage;
	int m_protection;
	int m_cash;

	// todo... special abilities with enum
public:
	CCard(std::string mName, std::string mDesc, int mCost, int mDamage, int mProtection, int mCash)
		: m_name(std::move(mName)), m_desc(std::move(mDesc)),  m_cost(mCost), m_damage(mDamage), m_protection(mProtection), m_cash(mCash) {}

	CCard() = default;
	CCard( const CCard & ) = default;
	virtual ~CCard() = default;
	CCard& operator=( const CCard & ) = default;

	/// Prints image of card to terminal on given position.
	virtual void print_card( int, int ) = 0;

	/// Card attacks the referenced card of an enemy.
	void attack( std::shared_ptr<CCard> );

	/// Card protects/heals the referenced friendly card.
	void protect( std::shared_ptr<CCard> );

	/// Card recieves the given amount of damage.
	/// @return True if card's life went below 0, false otherwise.
	virtual bool receive_damage( int ) = 0;

	int cash() const { return m_cash; }
	int cost() const { return m_cost; }
};


#endif //SEMESTRAL_CCARD_H
