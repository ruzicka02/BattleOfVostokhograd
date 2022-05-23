//
// Created by simon on 24.4.22.
//

#ifndef SEMESTRAL_EABILITY_H
#define SEMESTRAL_EABILITY_H

/// Enumeration of various special abilities that can be used in CCard.
enum EAbility {
	/// Card has no special ability
	null,

	/// Player can steal one of opponents cards on the table
	steal,

	/// Player can draw one extra card from his drawing deck
	draw,

	/// Opponent player discards one card from hand in his next turn
	discard,

	/// Player can sacrifice (=destroy) card in his own discard pile
	sacrifice
};

inline std::string ability_to_print_str(EAbility val) {
	switch (val) {
		case null:
			return "No ability";
		case steal:
			return "Steal a card";
		case draw:
			return "Draw a card";
		case discard:
			return "Opponent discards a card";
		case sacrifice:
			return "Sacrifice a card";
		default:
			return "Unexpected value";
	}
}

inline std::string ability_to_str(EAbility val) {
	switch (val) {
		case steal:
			return "steal";
		case draw:
			return "draw";
		case discard:
			return "discard";
		case sacrifice:
			return "sacrifice";
		default:
			return "null";
	}
}

inline EAbility str_to_ability(const std::string& val) {
	EAbility special = null;

	if ( val == "steal" )
		special = steal;
	else if ( val == "draw" )
		special = draw;
	else if ( val == "discard" )
		special = discard;
	else if ( val == "sacrifice" )
		special = sacrifice;

	return special;
}

#endif //SEMESTRAL_EABILITY_H
