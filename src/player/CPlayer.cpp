//
// Created by simon on 17.4.22.
//

#include "CPlayerAI.h"
#include "CPlayerBogo.h"
#include "CPlayerHuman.h"
#include "../CDisplay.h"

using namespace std;

void CPlayer::draw_cards(size_t amount) {
	if (amount > m_drawing.count() + m_discard.count())
		amount = m_drawing.count() + m_discard.count();

	for ( size_t i = 0; i < amount; i++ ) {
		if (! m_drawing.count()) { // refill the drawing pile from discard pile
			m_discard.shuffle_cards();
			while ( m_discard.count() ) {
				m_drawing.insert(m_discard.pop_top());
			}
		}

		shared_ptr<CCardDeckable> card = m_drawing.pop_top();
		m_hand.insert(card);
	}

}

void CPlayer::discard_all() {
	while ( m_hand.count() )
		m_discard.insert(m_hand.pop_top());
}

void CPlayer::discard_card(std::shared_ptr <CCardDeckable> target) {
	m_hand.remove(target);
	m_discard.insert(target);
}


void CPlayer::kill_card(std::shared_ptr <CCard> target) {
	// do nothing in case general is dead (game will terminate soon)
	if ( target == m_general )
		return;

	// we now know that the card is not general... is deckable (THIS IS NOT POLYMORPHISM AND I KNOW IT)
	auto target_deck = dynamic_pointer_cast<CCardDeckable>(target);
	target_deck->restore();
	m_table.remove(target_deck);
	m_discard.insert(target_deck);
}

void CPlayer::destroy_card(std::shared_ptr <CCardDeckable> target) {
	m_table.remove(target);
}

void CPlayer::steal_card(std::shared_ptr <CCardDeckable> target) {
	if ( ! m_opponent.lock() ) // opponent not set/deallocated
		return;

	m_opponent.lock()->destroy_card(target);

	m_table.insert(target);
	target->set_played(true);
}

void CPlayer::deploy_card(std::shared_ptr<CCardDeckable> target) {
	m_hand.remove(target);
	m_table.insert(target);
}

void CPlayer::play_card(std::shared_ptr<CCard> card, bool hand) {

	// Can be deployed (troop), can attack, can protect, has special ability
	vector<int> attr = card->attributes();

	auto card_deck = dynamic_pointer_cast<CCardDeckable>(card);
	if (card_deck) {
		// deploy the card from the hand
		if ( attr[0] && hand ) {
			deploy_card(card_deck);
			m_display->context_bar("Troop has been deployed." );
			m_display->refresh_board(shared_from_this(), m_opponent.lock(), m_shop);
			m_display->pause();
		}

		// must be warcry in hand... discard the card from hand
		if ( ! attr[0] && hand ) {
			discard_card(card_deck);
		}
	}

	// attack
	if ( attr[1] ) {
		vector<shared_ptr<CCard>> choice;
		for ( const auto& table_card : m_opponent.lock()->get_table() ) {
			choice.push_back(table_card);
		}
		choice.push_back(m_opponent.lock()->get_general());

		m_display->context_bar("Select an opponents card to attack. DMG = " + to_string(attr[1]) );
		auto selected = pick_card(choice, 1);

		card->attack(m_opponent.lock(), selected);
	}

	// protect
	if ( attr[2] ) {
		vector<shared_ptr<CCard>> choice;
		for ( const auto& table_card : m_table.cards() ) {
			choice.push_back(table_card);
		}
		choice.push_back(m_general);

		m_display->context_bar("Select a friendly card to protect/heal. HEAL = " + to_string(attr[2]) );
		auto selected = pick_card(choice, 2);

		card->protect(shared_from_this(), selected);
	}

	// special
	if ( attr[3] ) {
		EAbility ability = card->special_get();

		if ( ability == steal ) {
			m_display->context_bar("Select an opponents card to steal." );
			vector<shared_ptr<CCard>> choice;
			for ( const auto& table_card : m_opponent.lock()->get_table() ) {
				choice.push_back(table_card);
			}

			if ( ! choice.empty() ) {
				auto selected = pick_card(choice, 3);
				card->special(shared_from_this(), dynamic_pointer_cast<CCardDeckable>(selected));
				// we know this card is deckable... taken from opponents table
			}

		} else {
			m_display->context_bar(ability_to_print_str(ability));
			card->special(shared_from_this()); // using the default nullptr value as a selected card
		}

		m_display->refresh_board(shared_from_this(), m_opponent.lock(), m_shop);
		m_display->pause();
	}

	// cash
	if ( card->cash() > 0 ) {
		m_cash += card->cash();
		m_display->context_bar("Cash added to your stockpile.");
		m_display->refresh_board(shared_from_this(), m_opponent.lock(), m_shop);
		m_display->pause();
	}

	card->set_played(true);
}

bool CPlayer::save_player(ostream &file) {
	bool ok;
	file << save_player_type() << '\n' << m_general->save_card() << "\n\n";
	ok = m_drawing.save_deck(file);
	file << "\n";
	if ( ! ok )
		return false;

	ok = m_hand.save_deck(file);
	file << "\n";
	if ( ! ok )
		return false;

	ok = m_table.save_deck(file);
	file << "\n";
	if ( ! ok )
		return false;

	ok = m_discard.save_deck(file);

	return ok;
}

CPlayer::CPlayer(istream &file, CDisplay *display, CShop *shop)
		: m_cards_to_discard(0), m_cash(0), m_general(nullptr), m_shop(shop), m_display(display) {

	if ( ! file.good() )
		throw invalid_argument("Loading CPlayer from file failed immediately");

	string line;
	getline(file, line);
	m_general = CCardGeneral::load_card(line);
	getline(file, line); // empty newline

	if ( ! m_general || ! file.good() )
		throw invalid_argument("Loading CPlayer from file failed on loading CCardGeneral");

	m_drawing.load_deck(file, false);
	m_hand.load_deck(file, false);
	m_table.load_deck(file, false);
	m_discard.load_deck(file, false);

	if ( ! file.good() )
		throw invalid_argument("Loading CPlayer from file failed");
}

std::shared_ptr<CPlayer> CPlayer::load_player(istream &file, CDisplay *display, CShop *shop) {
	string player_type;
	getline(file, player_type);

	if (player_type == "AI")
		return make_shared<CPlayerAI>(file, display, shop);
	else if (player_type == "Bogo")
		return make_shared<CPlayerBogo>(file, display, shop);
	else if (player_type == "Human")
		return make_shared<CPlayerHuman>(file, display, shop);
	else
		return nullptr;
}
