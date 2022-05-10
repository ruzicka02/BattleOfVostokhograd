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
	draw
};

inline std::string ability_str(EAbility val) {
	switch (val) {
		case null:
			return "No ability";
		case steal:
			return "Steal a card";
		case draw:
			return "Draw a card";
		default:
			return "Unexpected value";
	}
}

#endif //SEMESTRAL_EABILITY_H
