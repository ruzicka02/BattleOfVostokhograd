//
// Created by simon on 15.4.22.
//

#ifndef SEMESTRAL_CCARDGENERAL_H
#define SEMESTRAL_CCARDGENERAL_H

#include "CCard.h"

// fixme
// Info ke kontrolnimu bodu semestralni prace - tato trida bude potrebovat prepracovani, protoze dedi z CCard, ale
// zaroven se pouziva ve tride CPlayer "naprimo" (bez pouziti polymorfickeho vztahu). Pravdepodobne reseni bude pridani
// nove tridy CCardRegular, ze ktere budou nasledne dedit tridy CCardTroop a CCardWarcry (polymorfismus se tedy nebude
// nachazet na potomcich CCard, ale CCardRegular). Alternativou by bylo tridu kompletne zrusit, jemne prepracovat mechaniky
// hry a nektere parametry dat primo do tridy CPlayer, cimz by tato trida byla zbytecna.

/// Derived class from CCard representing a general of one player. It has its own health tracker and in case of death,
/// the game is supposed to terminate (this is not part of the class logic and is managed outside).
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

	std::vector<bool> attributes() override;

	bool change_life( int life ) override;
	void restore() override;
};


#endif //SEMESTRAL_CCARDGENERAL_H
