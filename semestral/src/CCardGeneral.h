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
	void print_card( int, int ) override;
	bool receive_damage( int ) override;
};


#endif //SEMESTRAL_CCARDGENERAL_H
