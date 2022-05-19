//
// Created by simon on 15.4.22.
//

#include "CCard.h"
#include "CCardWarcry.h"
#include "CCardTroop.h"
#include "../player/CPlayer.h"

#include <memory>
#include <string>
#include <sstream>

using namespace std;

void CCard::attack( shared_ptr<CPlayer> player, shared_ptr<CCard> target ) const {
	bool killed = target->change_life(-1 * m_damage);

	if (killed)
		player->kill_card(target);
}

void CCard::protect( shared_ptr<CPlayer> player, std::shared_ptr<CCard> target ) const {
	target->change_life(m_protection);
}

void CCard::special( shared_ptr<CPlayer> player, std::shared_ptr <CCard> target) const {
	switch (m_special) {
		case null:
			break;
		case steal:
			player->steal_card(target);
			break;
		case draw:
			player->draw_cards(1);
			break;
		case discard:
			player->opponent_discard(1);
			break;
		case sacrifice:
			player->sacrifice_selection();
			break;
	}
}

// ---------------------------------------------------------------------------------------------------------------------

shared_ptr<CCard> CCard::load_card(string line) {
	istringstream line_stream = istringstream( line );
	string val;
	vector<string> row;

	while(getline(line_stream, val, ','))
		row.push_back(val);

	if ( row.size() <= 7 )
		return nullptr;

	shared_ptr<CCard> card = nullptr;

	// card values
	string name = row.at(0),
		desc = row.at(1),
		type = row.at(2),
		special_str = row.at(7);
	int cost = stoi(row.at(3)),
		damage = stoi(row.at(4)),
		heal = stoi(row.at(5)),
		cash = stoi(row.at(6)),
		life = stoi(row.at(8));

	EAbility special = str_to_ability(special_str);

	// create card based on the given type
	if ( type == "g" )
		card = make_shared<CCardGeneral>(name, desc, life, cost, damage, heal, cash, special);
	else if ( type == "t" )
		card = make_shared<CCardTroop>(name, desc, life, cost, damage, heal, cash, special);
	else
		card = make_shared<CCardWarcry>(name, desc, cost, damage, heal, cash, special);

	return card;
}
