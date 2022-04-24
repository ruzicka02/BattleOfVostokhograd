//
// Created by simon on 15.4.22.
//

#include "CCardGeneral.h"

void CCardGeneral::print_card( int y, int x ) {

}

bool CCardGeneral::change_life( int life ) {
	m_life += life;

	return life <= 0;
}

void CCardGeneral::restore() {
	m_life = m_life_init;
}
