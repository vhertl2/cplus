#include "stdafx.h"
#include "Vyjimka.h"


Vyjimka::Vyjimka(int error) {
	n_error = error;
};


string Vyjimka::Message(void) {
	switch (n_error) {
	case 1: return string("Jedna nebo vice zadanych souradnic k orezu lezi mimo obrazek");
	case 2: return string("Byla zadana hodnota souradnice x2 < x1 nebo y2 < y1");
	case 3: return string("Pozadovana hodnota pixelu nelze zobrazit, pixel lezi mimo obrazek");
	case 4: return string("Hodnota intenzity pixelu pro prahovani musi byt cele cislo v intervalu 0-255");
	default: return string("Jina Chyba");
	}
}


Vyjimka::~Vyjimka() {}