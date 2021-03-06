//
// Created by simon on 19.5.22.
//

#include "CCardDeckable.h"
#include "CCardWarcry.h"
#include "CCardTroop.h"

using namespace std;

shared_ptr<CCardDeckable> CCardDeckable::load_card(const string& line) {
	istringstream line_stream = istringstream( line );
	string val;
	vector<string> row;

	while(getline(line_stream, val, ','))
		row.push_back(val);

	if ( row.size() <= 7 )
		return nullptr;

	shared_ptr<CCardDeckable> card = nullptr;

	// card values
	string	name = row.at(0),
			desc = row.at(1),
			type = row.at(2),
			special_str = row.at(7);

	int cost = 0, damage = 0, heal = 0, cash = 0, life_init = 0, life = 0;
	try {
		cost = stoi(row.at(3));
		damage = stoi(row.at(4));
		heal = stoi(row.at(5));
		cash = stoi(row.at(6));

		if ( row.size() >= 9 ) {
			life_init = stoi(row.at(8));
			life = life_init;
		}

		if ( row.size() >= 10 )
			life = stoi(row.at(9));

	} catch (...) {
		// problematic numeric conversion, number out of range of 32bit int
		return nullptr;
	}

	EAbility special = str_to_ability(special_str);


	// create card based on the given type
	if ( type == "t" ) {
		card = make_shared<CCardTroop>(name, desc, life_init, cost, damage, heal, cash, special);
		card->change_life(life - life_init);
	}
	else if ( type == "w" ) {
		card = make_shared<CCardWarcry>(name, desc, cost, damage, heal, cash, special);
	}
	else {
		card = nullptr;
	}

	return card;
}