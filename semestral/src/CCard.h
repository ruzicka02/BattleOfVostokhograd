//
// Created by simon on 15.4.22.
//

#ifndef SEMESTRAL_CCARD_H
#define SEMESTRAL_CCARD_H


class CCard {
protected:
	// general properties
	int m_cost;

	// abilities
	int m_damage;
	int m_protection;
	int m_cash;

	// todo... special abilities with enum
public:
	CCard() = default;
	CCard( const CCard & ) = default;
	virtual ~CCard() = default;
	CCard& operator=( const CCard & );

	// translation between game logic and csv files
	void load_card( ostream& );
	void save_card( istream& );

	/// Prints image of card to terminal on given position
	virtual void print_card( int, int ) = 0;

	// game operations
	void attack( CCard & );
	void protect( CCard & );

	/// Card recieves the given amount of damage
	/// @return True if cards life went below 0, false otherwise
	virtual bool receive_damage( int ) = 0;

	int cash() { return m_cash; }
	int cost() { return m_cost; }

};


#endif //SEMESTRAL_CCARD_H
