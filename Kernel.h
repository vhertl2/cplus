#pragma once
#include "stdafx.h"
#include <iostream>

using namespace std;
class Kernel
{
	int kw, kh; //vyska a sirka jadra
	double normFac; //normovací faktor pro kernel
	int kt; //typ jadra
	double** ker; //dynamicke 2D pole hodnot pixelu
	const char* kernelName;
public:
	Kernel(int kernelType);
	double* operator[](int i) const;
	int getKernelWidth();
	int getKernelHeight();
	const char* getKernelName();
	~Kernel();
};

