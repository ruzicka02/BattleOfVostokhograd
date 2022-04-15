//
// Created by simon on 15.4.22.
//

#ifndef SEMESTRAL_CCARDWARCRY_H
#define SEMESTRAL_CCARDWARCRY_H

#include "CCard.h"

class CCardWarcry : public CCard {
protected:

public:
	void print_card( int, int ) override;
	bool receive_damage( int ) override { return false; }
};


#endif //SEMESTRAL_CCARDWARCRY_H
