//
// Created by simon on 18.4.22.
//

#ifndef SEMESTRAL_CPLAYERHUMAN_H
#define SEMESTRAL_CPLAYERHUMAN_H

#include "CPlayer.h"

class CPlayerHuman : public CPlayer {
protected:
public:
	CPlayerHuman( std::shared_ptr<CCardGeneral> gen, CDisplay* display, const CDeck& deck )
			: CPlayer(std::move(gen), display, deck) {}

	void play() override;

	void discard_cards (int amount) override;
};


#endif //SEMESTRAL_CPLAYERHUMAN_H
