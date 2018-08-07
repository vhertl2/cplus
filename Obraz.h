#pragma once
#include "stdafx.h"
#include <iostream>
#include "CImg-2.2.1\CImg.h"
#include "Kernel.h"
#include "Vyjimka.h"
using namespace cimg_library;
using namespace std;




class Obraz
{
	int** pi; //dynamicke 2D pole hodnot pixelu
	int width, height; //vyska a sirka obrazku
	double** k; //dynamicke 2D pole konvolucniho jadra
	int kw, kh; //vyska a sirka jadra
	const char* kernelName; //Nazev jadra
	const char* pictureName; //Nazev obrazku
public:
	Obraz(const char *filename); //konstruktor pro nacteni obrazku .bmp ze souboru
	Obraz(int width, int height); //konstruktor pro vytvoreni prazdneho pole pro obrazek se specifikovanou sirkou a vyskou
	Obraz(Obraz &x, Kernel &K); //konstruktor pro pouziti konvoluce
	Obraz(Obraz &x); //kopirovaci konstruktor
		
	int getWidth(); //vrati sirku jadra
	int getHeight(); //vrati vysku jadra
	void show(); //zobrazi obrazek (hodnoty pixelu matice pi) na display
	void printIntensities(); //vypise hodnoty pixelu matice pi
	
	Obraz threshold(int t); //provede prahovani obrazku se specifikovanym prahem 0-255
	Obraz bwimage(int t); // vytvori cernobily obrazek
	Obraz convolution(Obraz &x); // konvoluce
		Obraz operator-(); //vytvori inverzni obrazek
	Obraz operator()(int x1, int y1, int x2, int y2); //provede vyrez obrazku
	Obraz operator=(const Obraz &x); //vytvori kopii obrazu
	int* operator[](int i) const; //pristup k jednotlivym prvkum matice


	~Obraz();
};
