#pragma once
#include "stdafx.h"
#include <string>
using namespace std;

class Vyjimka
{
	int n_error;
	//string s_error;
public:
	Vyjimka(int error);
	string Message(void);
	~Vyjimka();
};

