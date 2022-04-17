//
// Created by simon on 17.4.22.
//

#ifndef SEMESTRAL_CSHOP_H
#define SEMESTRAL_CSHOP_H

#include "CDeck.h"

class CShop : public CDeck {
protected:
	CDeck m_drawing;
public:
	CShop() = default;
	CShop( const CShop& ) = default;
	CShop& operator= ( const CShop& ) = default;
	~CShop() = default;

	// overrides the CDeck definitions, considers shop content and drawing deck immediately following
	virtual void load_deck( std::istream& );
	virtual void save_deck( std::ostream& );

	/// Removes the referenced card from the store and refills with another card from drawing pile.
	void sell_card( std::shared_ptr<CCard> );
};


#endif //SEMESTRAL_CSHOP_H
