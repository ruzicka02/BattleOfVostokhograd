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
	void print_card( int y, int x ) override;
	bool change_life( int life ) override;
	void restore() override;
};


#endif //SEMESTRAL_CCARDGENERAL_H
