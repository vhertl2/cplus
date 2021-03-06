// ProjektHertl.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
using namespace std;
#include "Obraz.h"
#include "Kernel.h"

// #define DEBUG


int main()
{
	const char* filename = "lena.bmp";
	//const char* filename = "cameraman.bmp";
	Obraz O(filename), P(512,512);
	O.show();

	Kernel Identity(1), EdgeDetection1(2), EdgeDetection2(3), EdgeDetection3(4), Sharpen(5), GaussianBlur(6), BoxBlur(7);

	P = O;
	Obraz(P, Identity);
	P.show();

	P = O;
	Obraz(P, EdgeDetection1);
	P.show();

	P = O;
	Obraz(P, EdgeDetection2);
	P.show();

	P = O;
	Obraz(P, EdgeDetection3);
	P.show();

	P = O;
	Obraz(P, Sharpen);
	P.show();

	P = O;
	Obraz(P, GaussianBlur);
	P.show();

	P = O;
	Obraz(P, BoxBlur);
	P.show();
		P = -O;
	P.show();	

	try {
		P = O.bwimage(150);
	}
	catch (Vyjimka& v) {
		cout << endl << "Byla odchycena vyjimka: " << v.Message() << endl;
	}
	P.show();
	
	try {
		P = O(10, 10, 50, 50);
	}
	catch (Vyjimka& v) {
		cout << endl << "Byla odchycena vyjimka: " << v.Message() << endl;
	}
	P.show();
	
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			try {
				P[i][j] = 250;
			}
			catch (Vyjimka& v) {
				cout << endl << "Byla odchycena vyjimka: " << v.Message() << endl;
			}
		}
	}

	P.show();

	try {
	cout << endl << "Hodnota pixelu na pozadovanych souradnicich je:" << P[5][5] << endl;
	}
	catch (Vyjimka& v) {
		cout << endl << "Byla odchycena vyjimka: " << v.Message() << endl;
	}
	return 0;
}


