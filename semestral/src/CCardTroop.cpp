//
// Created by simon on 15.4.22.
//

#include "CCardTroop.h"

void CCardTroop::print_card(int y, int x) {

}

bool CCardTroop::change_life(int life) {
	m_life += life;

	return life <= 0;
}

void CCardTroop::restore() {
	m_life = m_life_init;
}
