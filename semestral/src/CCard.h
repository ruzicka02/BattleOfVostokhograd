//
// Created by simon on 15.4.22.
//

#ifndef SEMESTRAL_CCARD_H
#define SEMESTRAL_CCARD_H

#include <memory>
#include <string>
#include <vector>

#include "EAbility.h"

// forward declaration because of card playing methods
class CPlayer;

/// Abstract class that represents a single playing card with its unique set of attributes. Does not contain the life
/// attribute even though it has method interface for it, as it is only necessary for some of the derived classes. It
/// provides methods necessary for printing the cards to the terminal as it is considered more elegant than providing
/// all the card information outside of the class.
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
	CCard(std::string mName, std::string mDesc, int mCost, int mDamage, int mProtection, int mCash, EAbility mSpecial)
			: m_name(std::move(mName)), m_desc(std::move(mDesc)),  m_cost(mCost), m_damage(mDamage), m_protection(mProtection), m_cash(mCash), m_special(mSpecial) {}

	CCard( const CCard & rhs ) = default;
	virtual ~CCard() = default;
	CCard& operator=( const CCard & ) = default;

	/// Prints image of card to terminal on given coordinates.
	/// @param[in] y The y vertical coordinate (distance from top).
	/// @param[in] x The x horizontal coordinate (distance from left).
	virtual void print_card( int y, int x ) = 0;

	/// Prints image of card to terminal on given coordinates using wide characters (emojis). Not supported on some devices.
	/// @param[in] y The y vertical coordinate (distance from top).
	/// @param[in] x The x horizontal coordinate (distance from left).
	virtual void print_card_wide( int y, int x ) = 0;

	/// Returns the string with all the card information, used in game saving
	virtual std::string save_card() = 0;

	/// Static method that creates a new card based on information in the given string.
	/// @return Shared pointer to the newly created card.
	static std::shared_ptr<CCard> load_card (std::string line);

	/// Attacks the referenced card of an enemy. In case the card is destroyed, it leaves the battlefield.
	/// @param[in] player Targeted player (opponent).
	/// @param[in] target Card targeted by the ability. Can be left empty in case no card is targeted.
	void attack( std::shared_ptr<CPlayer> player, std::shared_ptr<CCard> target ) const;

	/// Protects (restores life to) the referenced card.
	/// @param[in] player Player that is playing the card.
	/// @param[in] target Card targeted by the ability.
	void protect( std::shared_ptr<CPlayer> player, std::shared_ptr<CCard> target ) const;

	/// Card plays its special ability.
	/// @param[in] player Player that is playing the card.
	/// @param[in] target Card targeted by the ability. Can be left empty in case no card is targeted.
	void special( std::shared_ptr<CPlayer> player, std::shared_ptr<CCard> target = nullptr ) const;

	/// Card adds or subtracts the given amount of life points. Used for both attacking and protecting a card.
	/// Dummy implementation for non-permanent cards as they do not have life stats.
	/// @param[in] life Positive value when life is added and negative when life is subtracted.
	/// @return True if card's life went below 0, false otherwise.
	virtual bool change_life( int life ) = 0;

	/// Restores the life points of the card to its original value.
	virtual void restore() = 0;

	/// Returns appropriate (non-zero) attributes of a card, that can be played afterwards. Order of the operations
	/// is following: `Can be deployed (troop), can attack, can protect, has special ability`.
	virtual std::vector<int> attributes() = 0;

	/// Returns the amount of cash that player receives when card is played.
	[[nodiscard]] int cash() const { return m_cash; }

	/// Returns the cost of the card in the shop.
	[[nodiscard]] int cost() const { return m_cost; }

	/// Returns the name of the card (used especially with generals).
	[[nodiscard]] const std::string& name() const { return m_name; }

	/// Returns the special ability of the card.
	[[nodiscard]] EAbility special_get() const { return m_special; }

	/// Returns whether card was already played. Dummy implementation for non deployable cards.
	virtual bool played() const = 0;

	/// Changes state whether card was played or not. Dummy implementation for non deployable cards.
	virtual void set_played(bool) = 0;
};


#endif //SEMESTRAL_CCARD_H
