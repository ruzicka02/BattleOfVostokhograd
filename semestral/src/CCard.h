//
// Created by simon on 15.4.22.
//

#ifndef SEMESTRAL_CCARD_H
#define SEMESTRAL_CCARD_H

#include <memory>
#include <string>

#include "EAbility.h"

// forward declaration because of card playing methods
class CPlayer;

/// Abstract class that represents a single playing card.
class CCard {
protected:
	// general properties
	std::string 	m_name;
	std::string 	m_desc;
	int 			m_cost;

	// abilities
	int 			m_damage;
	int 			m_protection;
	int 			m_cash;
	EAbility 		m_special;

public:
	CCard(std::string mName, std::string mDesc, int mCost, int mDamage, int mProtection, int mCash)
		: m_name(std::move(mName)), m_desc(std::move(mDesc)),  m_cost(mCost), m_damage(mDamage), m_protection(mProtection), m_cash(mCash) {}

	CCard() = default;
	CCard( const CCard & ) = default;
	virtual ~CCard() = default;
	CCard& operator=( const CCard & ) = default;

	/// Prints image of card to terminal on given coordinates.
	/// @param[in] y The y vertical coordinate (distance from top).
	/// @param[in] x The x horizontal coordinate (distance from left).
	virtual void print_card( int y, int x ) = 0;

	/// Attacks the referenced card of an enemy.
	void attack( CPlayer& player, std::shared_ptr<CCard> target );

	/// Protects (restores life to) the referenced card.
	void protect( CPlayer& player, std::shared_ptr<CCard> target );

	/// Card plays its special ability.
	/// @param[in] player Effected player of the ability.
	/// @param[in] target Card targeted by the ability. Default value is nullptr in case no card is targeted.
	void special( CPlayer& player, std::shared_ptr<CCard> target = nullptr );

	/// Card adds or subtracts the given amount of life points. Used for both attacking and protecting a card.
	/// Dummy implementation for non-permanent cards as they do not have life stats.
	/// @param[in] life Positive value when life is added and negative when life is subtracted.
	/// @return True if card's life went below 0, false otherwise.
	virtual bool change_life( int life ) = 0;

	/// Restores the life points of the card to its original value.
	virtual void restore() = 0;

	/// Returns the amount of cash that player receives when card is played.
	int cash() const { return m_cash; }

	/// Returns the cost of the card in the shop.
	int cost() const { return m_cost; }
};


#endif //SEMESTRAL_CCARD_H
