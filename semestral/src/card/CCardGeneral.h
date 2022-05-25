//
// Created by simon on 15.4.22.
//

#ifndef SEMESTRAL_CCARDGENERAL_H
#define SEMESTRAL_CCARDGENERAL_H

#include "CCard.h"

/// Derived class from CCard representing a general of one player. It has its own health tracker and in case of death,
/// the game is supposed to terminate (this is not part of the class logic and is managed outside).
class CCardGeneral : public CCard {
protected:
	int m_life;
	int m_life_init;

	bool m_played;
public:
	CCardGeneral(std::string mName, std::string mDesc, int mLife, int mCost, int mDamage, int mProtection, int mCash, EAbility mSpecial)
	: 	CCard(std::move(mName), std::move(mDesc), mCost, mDamage, mProtection, mCash, mSpecial),
		m_life(mLife), m_life_init(mLife), m_played(false) {}

	void print_card( int y, int x ) override;
	void print_card_wide( int y, int x ) override;
	std::string save_card() override;

	std::vector<int> attributes() override;

	bool change_life( int life ) override;
	void restore() override;

	[[nodiscard]] bool played() const override { return m_played; }
	void set_played(bool played) override { m_played = played; }

	std::pair<int, int> life() override {
		return {m_life, m_life_init};
	}

	/// Static method that creates a new CCardGeneral based on information in the given string.
	/// @return Shared pointer to the newly created card. Returns nullptr on invalid input.
	static std::shared_ptr<CCardGeneral> load_card (const std::string& line);

	int score() override {
		return 15 * (m_life_init - m_life); // determined purely by missing life (with stronger coefficient)
	}
};


#endif //SEMESTRAL_CCARDGENERAL_H
