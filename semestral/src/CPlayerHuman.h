//
// Created by simon on 18.4.22.
//

#ifndef SEMESTRAL_CPLAYERHUMAN_H
#define SEMESTRAL_CPLAYERHUMAN_H

#include "CPlayer.h"

class CPlayerHuman : public CPlayer {
protected:
public:
	void play() override;

	void discard_cards (int amount) override;
};


#endif //SEMESTRAL_CPLAYERHUMAN_H
